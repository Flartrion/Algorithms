#pragma once
#include <iostream>
#include "List.hpp"
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
    int lastHeight_;
    List<T>* infoList_;
    List<K>* keyList_;
    void sortedTraverse (MapNode<K, T>*);
    void generateLists ();
    MapNode<K, T>* find (K);

    void deletion (MapNode<K, T>*);
    void rotateRight (MapNode<K, T>*);
    void rotateLeft (MapNode<K, T>*);
    void removeFixUp (MapNode<K, T>*);
    void insertFixUp (MapNode<K, T>*);

    void printTraverse (bool* brackets, MapNode<K, T>* curEl, int curHeight);
    int height (MapNode<K, T>*, int);

   public:
    MapNode<K, T>* root_;
    List<T>& get_values ();
    List<K>& get_keys ();
    bool contains (K);
    void insert (K, T);
    void remove (int);
    void printTree ();
    Map ();
    ~Map ();
};

// all the funcs.

template <class K, class T> Map<K, T>::Map () {  // Nothing much to do.
    root_= 0;
    lastHeight_= 0;
    infoList_= 0;
    keyList_= 0;
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
        MapNode<K, T>* temp= root_;

        while (temp) {
            if (key == temp->key_)
                return temp;
            else if (key > temp->key_)
                temp= temp->right_;
            else
                temp= temp->left_;
        }
    }

    return 0;
}

template <class K, class T> bool Map<K, T>::contains (K key) {
    if (root_) {
        MapNode<K, T>* temp= root_;

        while (temp) {
            if (key == temp->key_)
                return true;
            else if (key > temp->key_)
                temp= temp->right_;
            else
                temp= temp->left_;
        }
    }

    return false;
}

template <class K, class T> int Map<K, T>::height (MapNode<K, T>* root,
                                                   int curheight) {  // 1 to count from root
    if (root) {
        if (!root->right_ && !root->left_) {
            lastHeight_= curheight;
            return curheight;
        } else {
            int h1= 0, h2= 0;

            if (root->right_) h1= height (root->right_, curheight + 1);

            if (root->left_) h2= height (root->left_, curheight + 1);

            lastHeight_= (h1 > h2 ? h1 : h2);
            return (h1 > h2 ? h1 : h2);
        }
    } else {
        return 0;
        lastHeight_= 0;
    }
}

template <class K, class T> void Map<K, T>::generateLists () {
    if (keyList_) {
        delete keyList_;
        delete infoList_;
    }
    keyList_= new List<K>;
    infoList_= new List<T>;
    sortedTraverse (root_);
}

template <class K, class T> void Map<K, T>::sortedTraverse (MapNode<K, T>* curNode) {
    if (curNode->left_) sortedTraverse (curNode->left_);
    keyList_->push_back (curNode->key_);
    infoList_->push_back (curNode->info_);
    if (curNode->right_) sortedTraverse (curNode->right_);
}

template <class K, class T> List<K>& Map<K, T>::get_keys () {
    generateLists ();
    return *keyList_;
}

template <class K, class T> List<T>& Map<K, T>::get_values () {
    generateLists ();
    return *infoList_;
}

template <class K, class T> void Map<K, T>::printTree () {
    // 193:  ┴
    // 179:  │
    // 192: └
    // 194: ┬
    // 195:  ├
    // 196: ─
    // 254: square
    int totalHeight= height (root_, 1);
    bool* brackets= new bool[totalHeight];

    for (int i= 0; i < totalHeight; i++)
        brackets[i]= false;

    std::cout << '\n' << (char)192 << (char)196 << (root_->color_ ? 'R' : 'B') << ':' << root_->key_ << '\n';
    printTraverse (brackets, root_->right_, 1);
    printTraverse (brackets, root_->left_, 1);
    std::cin.ignore (1);
}

// Awful. Uses black magic to work. Still works, so whatever.
// Jokes aside - much simpler than it looks. Cycle (1) draws vertical lines to
// show tree's branching. Then it checks if the current element exists. If not -
// put a square with opening or closing ladder symbols. If yes - draw it and
// then check if it has any children. (looks like it's possible to adapt that to
// B-tree by expanding brackets' possible values. Should keep for reference.)
template <class K, class T> void Map<K, T>::printTraverse (bool* brackets, MapNode<K, T>* curEl, int curHeight) {
    for (int i= 0; i < curHeight; i++) {  // (1) here
        std::cout << ' ' << (brackets[i] ? (char)179 : ' ');
    }

    if (curEl) {
        if (brackets[curHeight]) {
            std::cout << ' ' << (char)192 << (curEl->color_ ? 'R' : 'B') << ':' << curEl->key_ << '\n';
            brackets[curHeight]= false;
        } else {
            std::cout << (char)192 << (char)194 << (curEl->color_ ? 'R' : 'B') << ':' << curEl->key_ << '\n';
            brackets[curHeight]= true;
        }

        if (curEl->right_ || curEl->left_) {
            printTraverse (brackets, curEl->right_, curHeight + 1);
            printTraverse (brackets, curEl->left_, curHeight + 1);
        }
    } else {
        if (brackets[curHeight]) {
            std::cout << ' ' << (char)192 << (char)254 << '\n';
            brackets[curHeight]= false;
        } else {
            std::cout << (char)192 << (char)194 << (char)254 << '\n';
            brackets[curHeight]= true;
        }
    }
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
    MapNode* current= this;
    while (current) {
        if (current->right_) {
            return current->right_;
        } else if (current->parent_) {
            if (current->parent_->right_ == current) {
                current= current->parent_;
            } else {
                return current->parent_;
            }
        } else {
            current= 0;
        }
    }
    return 0;
}

template <class K, class T> void Map<K, T>::rotateLeft (MapNode<K, T>* pivot) {
    if (pivot) {
        if (pivot->right_) {
            MapNode<K, T>* pivot2= pivot->right_;
            pivot2->parent_= pivot->parent_;

            if (pivot->parent_) {
                (pivot->parent_->left_ == pivot ? pivot->parent_->left_ : pivot->parent_->right_)= pivot2;  // hellish thing just redirects pivot's parent's left
                                                                                                            // or right to pivot 2, all in one line.
            } else {
                root_= pivot2;
            }

            pivot->parent_= pivot2;

            if (pivot2->left_) pivot2->left_->parent_= pivot;

            pivot->right_= pivot2->left_;
            pivot2->left_= pivot;
            return;
        }
    }
}

template <class K, class T> void Map<K, T>::rotateRight (MapNode<K, T>* pivot) {
    if (pivot) {
        if (pivot->left_) {
            MapNode<K, T>* pivot2= pivot->left_;
            pivot2->parent_= pivot->parent_;

            if (pivot->parent_) {
                (pivot->parent_->left_ == pivot ? pivot->parent_->left_ : pivot->parent_->right_)= pivot2;  // hellish thing just redirects pivot's parent's left
                                                                                                            // or right to pivot 2, all in one line.
            } else {
                root_= pivot2;
            }

            pivot->parent_= pivot2;

            if (pivot2->right_) pivot2->right_->parent_= pivot;

            pivot->left_= pivot2->right_;
            pivot2->right_= pivot;
            return;
        }
    }
}

template <class K, class T> void Map<K, T>::remove (int key) {
    MapNode<K, T>*toBeDeld= find (key), *rpl= 0, *rplcd= 0;  // replacement, replacement-child

    if (toBeDeld) {
        if (!toBeDeld->right_ && !toBeDeld->left_) {
            rpl= toBeDeld;
        } else {
            rpl= toBeDeld->successor ();
        }

        rplcd= (rpl->left_ ? rpl->left_ : rpl->right_);

        if (rplcd) rplcd->parent_= rpl->parent_;

        if (!rpl->parent_) {
            root_= rplcd;
        } else {
            if (rpl == rpl->parent_->left_) {
                rpl->parent_->left_= rplcd;
            } else {
                rpl->parent_->right_= rplcd;
            }
        }

        if (rpl != toBeDeld) {
            toBeDeld->key_= rpl->key_;
            toBeDeld->info_= rpl->info_;
        }

        if (rpl->color_ == 0) removeFixUp (rpl);
    }
}

template <class K, class T> void Map<K, T>::removeFixUp (MapNode<K, T>* curNode) {
    MapNode<K, T>* sibling;
    bool tempLeftColor= 0, tempRightColor= 0;
    while (curNode != root_ && curNode->color_ == 0) {
        if (curNode == curNode->parent_->left_) {
            sibling= curNode->parent_->right_;
            if (sibling->color_ == 1) {
                sibling->color_= 0;
                rotateLeft (curNode->parent_);
                sibling= curNode->parent_->right_;
            }

            tempLeftColor= (sibling->left_ ? sibling->left_->color_ : 0);
            tempRightColor= (sibling->right_ ? sibling->right_->color_ : 0);
            if (tempLeftColor == 0 && tempRightColor == 0) {
                sibling->color_= 1;
                curNode= curNode->parent_;
            } else {
                if (tempRightColor == 0) {
                    if (sibling->left_) sibling->left_->color_= 0;
                    sibling->color_= 1;
                    rotateRight (sibling);
                    sibling= curNode->parent_->right_;
                }
                sibling->color_= curNode->parent_->color_;
                curNode->parent_->color_= 0;
                if (sibling->right_) sibling->right_->color_= 0;
                rotateLeft (curNode->parent_);
                curNode= root_;
            }
        } else {
            sibling= curNode->parent_->left_;
            if (sibling->color_ == 1) {
                sibling->color_= 0;
                rotateRight (curNode->parent_);
                sibling= curNode->parent_->left_;
            }

            tempLeftColor= (sibling->left_ ? sibling->left_->color_ : 0);
            tempRightColor= (sibling->right_ ? sibling->right_->color_ : 0);
            if (tempLeftColor == 0 && tempRightColor == 0) {
                sibling->color_= 1;
                curNode= curNode->parent_;
            } else {
                if (tempLeftColor == 0) {
                    if (sibling->right_) sibling->right_->color_= 0;
                    sibling->color_= 1;
                    rotateLeft (sibling);
                    sibling= curNode->parent_->left_;
                }
                sibling->color_= curNode->parent_->color_;
                curNode->parent_->color_= 0;
                if (sibling->left_) sibling->left_->color_= 0;
                rotateRight (curNode->parent_);
                curNode= root_;
            }
        }
    }
    curNode->color_= 0;
}

template <class K, class T> void Map<K, T>::insert (K key, T info) {
    if (root_) {
        MapNode<K, T>* curNode= root_;

        while (true) {
            if (curNode->key_ == key)
                return;
            else {
                if (key > curNode->key_) {
                    if (curNode->right_)
                        curNode= curNode->right_;
                    else {
                        curNode->right_= new MapNode<K, T>;
                        curNode->right_->key_= key;
                        curNode->right_->info_= info;
                        curNode->right_->color_= 1;
                        curNode->right_->parent_= curNode;
                        curNode= curNode->right_;
                        break;
                    }
                } else {
                    if (curNode->left_)
                        curNode= curNode->left_;
                    else {
                        curNode->left_= new MapNode<K, T>;
                        curNode->left_->key_= key;
                        curNode->left_->info_= info;
                        curNode->left_->color_= 1;
                        curNode->left_->parent_= curNode;
                        curNode= curNode->left_;
                        break;
                    }
                }
            }
        }
        insertFixUp (curNode);
    } else {
        root_= new MapNode<K, T>;
        root_->info_= info;
        root_->key_= key;
    }
}

template <class K, class T> void Map<K, T>::insertFixUp (MapNode<K, T>* curNode) {
    if (curNode) {
        while (curNode != root_) {
            if (curNode->parent_->color_ == 0 && curNode->color_ == 1)  // Parent is black, current element is red, everything is all right - immediate exit.
                return;
            else if (curNode->uncle ()) {
                if (curNode->uncle ()->color_ == 1) {  // Uncle and parent are red.
                    curNode->parent_->color_= 0;
                    curNode->uncle ()->color_= 0;
                    if (curNode->grandfather () != root_) {
                        curNode->grandfather ()->color_= 1;
                        curNode= curNode->grandfather ();
                    }  // Simple recolor and move upward. Exit when temp is the root.
                    else
                        return;
                } else {                                                        // Uncle exists and is black. Below are all 4 possibilities.
                    if (curNode->uncle () == curNode->grandfather ()->left_) {  // Uncle is on the left.
                        if (curNode != curNode->parent_->right_) {              // But new node is on the left, either
                            rotateRight (curNode->parent_);                     // And now it's not.
                            curNode= curNode->right_;
                        }
                        curNode->parent_->color_= 0;
                        curNode->grandfather ()->color_= 1;
                        rotateLeft (curNode->grandfather ());
                        curNode= curNode->parent_;
                    } else {                                       // Uncle is on the right
                        if (curNode != curNode->parent_->left_) {  // But new node is on the right, either
                            rotateLeft (curNode->parent_);         // And now it's not.
                            curNode= curNode->left_;
                        }
                        curNode->parent_->color_= 0;
                        curNode->grandfather ()->color_= 1;
                        rotateRight (curNode->grandfather ());
                        curNode= curNode->parent_;
                    }
                }
            } else {
                if (curNode->grandfather ()) {                      // All the same as in black uncle. But without uncle. But only if there is a grandfather.
                    if (curNode->grandfather ()->left_ == 0) {      // Leaf is on the left.
                        if (curNode != curNode->parent_->right_) {  // But new node is on the left, either
                            rotateRight (curNode->parent_);         // And now it's not.
                            curNode= curNode->right_;
                        }
                        curNode->parent_->color_= 0;
                        curNode->grandfather ()->color_= 1;
                        rotateLeft (curNode->grandfather ());
                        curNode= curNode->parent_;
                    } else {                                       // Leaf is on the right
                        if (curNode != curNode->parent_->left_) {  // But new node is on the right, either
                            rotateLeft (curNode->parent_);         // And now it's not.
                            curNode= curNode->left_;
                        }
                        curNode->parent_->color_= 0;
                        curNode->grandfather ()->color_= 1;
                        rotateRight (curNode->grandfather ());
                        curNode= curNode->parent_;
                    }
                } else {  // And that means there's no grandfather at all, only parent
                    curNode= curNode->parent_;
                }
            }
        }
    }
}
