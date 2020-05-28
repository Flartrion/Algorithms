#pragma once
#include <iostream>
template <class A, class B> struct MapNode {
	A key_;
	B info_;
	bool color_;  // And thus, 0 means black. Leaves are nullptrs, which seems reasonable enough.
	MapNode *right_, *left_, *parent_;
	
	MapNode () : color_ (0), right_ (0), left_ (0), parent_ (0) {  // Set pointers to null to keep it nice and safe.
	}
	
	MapNode* uncle ();
	MapNode* grandfather ();
	MapNode* successor ();
};

template <class K, class T> class Map {
private:
	MapNode<K, T>* find (K key);
	
	void deletion (MapNode<K, T>*);
	void rotateRight (MapNode<K, T>*);
	void rotateLeft (MapNode<K, T>*);
	void removeFixUp (MapNode<K, T>*);
	void insertFixUp (MapNode<K, T>*);
	
public:
	MapNode<K, T>* root_;
	bool contains (K key);
	T* findByKey (K key);
	void insert (K key, T& info);
	void remove (K key);
	Map ();
	~Map ();
};

// all the funcs.

template <class K, class T> Map<K, T>::Map () {  // Nothing much to do.
	root_ = 0;
}

template <class K, class T> void Map<K, T>::deletion (MapNode<K, T>* current) {
	if (current->left_) deletion (current->left_);
	
	if (current->right_) deletion (current->right_);
	
	delete current;
}

template <class K, class T> Map<K, T>::~Map () {
	if (root_) {
		deletion (root_);
	}
}

template <class K, class T> MapNode<K, T>* Map<K, T>::find (K key) {
	if (root_) {
		MapNode<K, T>* temp = root_;
		
		while (temp) {
			if (key == temp->key_)
				return temp;
			else if (key > temp->key_)
				temp = temp->right_;
			else
				temp = temp->left_;
		}
	}
	
	return 0;
}

template <class K, class T> T* Map<K, T>::findByKey (K key) {
	if (root_) {
		MapNode<K, T>* element = find (key);
		
		if (element) {
			return &element->info_;
		}
	}
	
	return 0;
}

template <class K, class T> bool Map<K, T>::contains (K key) {
	if (root_) {
		MapNode<K, T>* temp = root_;
		
		while (temp) {
			if (key == temp->key_)
				return true;
			else if (key > temp->key_)
				temp = temp->right_;
			else
				temp = temp->left_;
		}
	}
	
	return false;
}
// Up above are basic tree funcs. Below are RBT-specific funcs.
//

template <class K, class T> MapNode<K, T>* MapNode<K, T>::grandfather () {
	if (parent_) {
		return parent_->parent_;
	} else
		return 0;
}

template <class K, class T> MapNode<K, T>* MapNode<K, T>::uncle () {
	if (grandfather ())
		return grandfather ()->right_ == parent_ ? grandfather ()->left_ : grandfather ()->right_;
	else
		return 0;
}

template <class K, class T> MapNode<K, T>* MapNode<K, T>::successor () {
	MapNode* current = this;
	
	while (current) {
		if (current->right_) {
			return current->right_;
		} else if (current->parent_) {
			if (current->parent_->right_ == current) {
				current = current->parent_;
			} else {
				return current->parent_;
			}
		} else {
			current = 0;
		}
	}
	
	return 0;
}

template <class K, class T> void Map<K, T>::rotateLeft (MapNode<K, T>* pivot) {
	if (pivot) {
		if (pivot->right_) {
			MapNode<K, T>* pivot2 = pivot->right_;
			pivot2->parent_ = pivot->parent_;
			
			if (pivot->parent_) {
				(pivot->parent_->left_ == pivot ? pivot->parent_->left_ : pivot->parent_->right_) = pivot2; // hellish thing just redirects pivot's parent's left
				// or right to pivot 2, all in one line.
			} else {
				root_ = pivot2;
			}
			
			pivot->parent_ = pivot2;
			
			if (pivot2->left_) pivot2->left_->parent_ = pivot;
			
			pivot->right_ = pivot2->left_;
			pivot2->left_ = pivot;
			return;
		}
	}
}

template <class K, class T> void Map<K, T>::rotateRight (MapNode<K, T>* pivot) {
	if (pivot) {
		if (pivot->left_) {
			MapNode<K, T>* pivot2 = pivot->left_;
			pivot2->parent_ = pivot->parent_;
			
			if (pivot->parent_) {
				(pivot->parent_->left_ == pivot ? pivot->parent_->left_ : pivot->parent_->right_) = pivot2; // hellish thing just redirects pivot's parent's left
				// or right to pivot 2, all in one line.
			} else {
				root_ = pivot2;
			}
			
			pivot->parent_ = pivot2;
			
			if (pivot2->right_) pivot2->right_->parent_ = pivot;
			
			pivot->left_ = pivot2->right_;
			pivot2->right_ = pivot;
			return;
		}
	}
}

template <class K, class T> void Map<K, T>::remove (K key) {
	MapNode<K, T>*toBeDeld = find (key), *rpl = 0, *rplcd = 0; // replacement, replacement-child
	
	if (toBeDeld) {
		if (!toBeDeld->right_ && !toBeDeld->left_) {
			rpl = toBeDeld;
		} else {
			rpl = toBeDeld->successor ();
		}
		
		rplcd = (rpl->left_ ? rpl->left_ : rpl->right_);
		
		if (rplcd) rplcd->parent_ = rpl->parent_;
		
		if (!rpl->parent_) {
			root_ = rplcd;
		} else {
			if (rpl == rpl->parent_->left_) {
				rpl->parent_->left_ = rplcd;
			} else {
				rpl->parent_->right_ = rplcd;
			}
		}
		
		if (rpl != toBeDeld) {
			toBeDeld->key_ = rpl->key_;
			toBeDeld->info_ = rpl->info_;
		}
		
		if (rpl->color_ == 0) removeFixUp (rpl);
	}
}

template <class K, class T> void Map<K, T>::removeFixUp (MapNode<K, T>* curNode) {
	MapNode<K, T>* sibling;
	bool tempLeftColor = 0, tempRightColor = 0;
	
	while (curNode != root_ && curNode->color_ == 0) {
		if (curNode == curNode->parent_->left_) {
			sibling = curNode->parent_->right_;
			
			if (sibling->color_ == 1) {
				sibling->color_ = 0;
				rotateLeft (curNode->parent_);
				sibling = curNode->parent_->right_;
			}
			
			tempLeftColor = (sibling->left_ ? sibling->left_->color_ : 0);
			tempRightColor = (sibling->right_ ? sibling->right_->color_ : 0);
			
			if (tempLeftColor == 0 && tempRightColor == 0) {
				sibling->color_ = 1;
				curNode = curNode->parent_;
			} else {
				if (tempRightColor == 0) {
					if (sibling->left_) sibling->left_->color_ = 0;
					
					sibling->color_ = 1;
					rotateRight (sibling);
					sibling = curNode->parent_->right_;
				}
				
				sibling->color_ = curNode->parent_->color_;
				curNode->parent_->color_ = 0;
				
				if (sibling->right_) sibling->right_->color_ = 0;
				
				rotateLeft (curNode->parent_);
				curNode = root_;
			}
		} else {
			sibling = curNode->parent_->left_;
			
			if (sibling->color_ == 1) {
				sibling->color_ = 0;
				rotateRight (curNode->parent_);
				sibling = curNode->parent_->left_;
			}
			
			tempLeftColor = (sibling->left_ ? sibling->left_->color_ : 0);
			tempRightColor = (sibling->right_ ? sibling->right_->color_ : 0);
			
			if (tempLeftColor == 0 && tempRightColor == 0) {
				sibling->color_ = 1;
				curNode = curNode->parent_;
			} else {
				if (tempLeftColor == 0) {
					if (sibling->right_) sibling->right_->color_ = 0;
					
					sibling->color_ = 1;
					rotateLeft (sibling);
					sibling = curNode->parent_->left_;
				}
				
				sibling->color_ = curNode->parent_->color_;
				curNode->parent_->color_ = 0;
				
				if (sibling->left_) sibling->left_->color_ = 0;
				
				rotateRight (curNode->parent_);
				curNode = root_;
			}
		}
	}
	
	curNode->color_ = 0;
}

template <class K, class T> void Map<K, T>::insert (K key, T& info) {
	if (root_) {
		MapNode<K, T>* curNode = root_;
		
		while (true) {
			if (curNode->key_ == key)
				return;
			else {
				if (key > curNode->key_) {
					if (curNode->right_)
						curNode = curNode->right_;
					else {
						curNode->right_ = new MapNode<K, T>;
						curNode->right_->key_ = key;
						curNode->right_->info_ = info;
						curNode->right_->color_ = 1;
						curNode->right_->parent_ = curNode;
						curNode = curNode->right_;
						break;
					}
				} else {
					if (curNode->left_)
						curNode = curNode->left_;
					else {
						curNode->left_ = new MapNode<K, T>;
						curNode->left_->key_ = key;
						curNode->left_->info_ = info;
						curNode->left_->color_ = 1;
						curNode->left_->parent_ = curNode;
						curNode = curNode->left_;
						break;
					}
				}
			}
		}
		
		insertFixUp (curNode);
	} else {
		root_ = new MapNode<K, T>;
		root_->info_ = info;
		root_->key_ = key;
	}
}

template <class K, class T> void Map<K, T>::insertFixUp (MapNode<K, T>* curNode) {
	if (curNode) {
		while (curNode != root_) {
			if (curNode->parent_->color_ == 0 && curNode->color_ == 1)  // Parent is black, current element is red, everything is all right - immediate exit.
				return;
			else if (curNode->uncle ()) {
				if (curNode->uncle ()->color_ == 1) {  // Uncle and parent are red.
					curNode->parent_->color_ = 0;
					curNode->uncle ()->color_ = 0;
					
					if (curNode->grandfather () != root_) {
						curNode->grandfather ()->color_ = 1;
						curNode = curNode->grandfather ();
					}  // Simple recolor and move upward. Exit when temp is the root.
					else
						return;
				} else {                                                        // Uncle exists and is black. Below are all 4 possibilities.
					if (curNode->uncle () == curNode->grandfather ()->left_) {  // Uncle is on the left.
						if (curNode != curNode->parent_->right_) {              // But new node is on the left, either
							rotateRight (curNode->parent_);                     // And now it's not.
							curNode = curNode->right_;
						}
						
						curNode->parent_->color_ = 0;
						curNode->grandfather ()->color_ = 1;
						rotateLeft (curNode->grandfather ());
						curNode = curNode->parent_;
					} else {                                       // Uncle is on the right
						if (curNode != curNode->parent_->left_) {  // But new node is on the right, either
							rotateLeft (curNode->parent_);         // And now it's not.
							curNode = curNode->left_;
						}
						
						curNode->parent_->color_ = 0;
						curNode->grandfather ()->color_ = 1;
						rotateRight (curNode->grandfather ());
						curNode = curNode->parent_;
					}
				}
			} else {
				if (curNode->grandfather ()) {                      // All the same as in black uncle. But without uncle. But only if there is a grandfather.
					if (curNode->grandfather ()->left_ == 0) {      // Leaf is on the left.
						if (curNode != curNode->parent_->right_) {  // But new node is on the left, either
							rotateRight (curNode->parent_);         // And now it's not.
							curNode = curNode->right_;
						}
						
						curNode->parent_->color_ = 0;
						curNode->grandfather ()->color_ = 1;
						rotateLeft (curNode->grandfather ());
						curNode = curNode->parent_;
					} else {                                       // Leaf is on the right
						if (curNode != curNode->parent_->left_) {  // But new node is on the right, either
							rotateLeft (curNode->parent_);         // And now it's not.
							curNode = curNode->left_;
						}
						
						curNode->parent_->color_ = 0;
						curNode->grandfather ()->color_ = 1;
						rotateRight (curNode->grandfather ());
						curNode = curNode->parent_;
					}
				} else {  // And that means there's no grandfather at all, only parent
					curNode = curNode->parent_;
				}
			}
		}
	}
}
