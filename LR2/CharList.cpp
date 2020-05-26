#include <stdexcept>
#include <iostream>
#include "CharList.hpp"

CharListEl::~CharListEl() {
}

CharListEl::CharListEl() {
}

bool CharListEl::operator> (CharListEl other) {
	if (weight_ > other.weight_) return true;
	else return false;
}

bool CharListEl::operator< (CharListEl other) {
	if (weight_ < other.weight_) return true;
	else return false;
}

void CharList::goFirst () {
	currentPlace_ = 0;
	current_ = first_;
}

void CharList::goNext () {
	currentPlace_++;
	current_ = current_->next_;
}

CharList::CharList() {
}

CharList::~CharList() {
	if (first_) {
		goFirst();
		CharListEl* temp;

		while (current_) {
			temp = current_;
			goNext();
			delete temp;
		}
	}
}

void CharList::clear() {
	if (first_) {
		goFirst();
		CharListEl* temp;

		while (current_) {
			temp = current_;
			goNext();
			delete temp;
		}
	}

	first_ = last_ = current_ = 0; 
	currentPlace_ = length_ = 0;
}

CharListEl* CharList::operator[] (int where) {
	if (!first_) {
		throw std::out_of_range ("CharList[] - accessing empty list");
	} else if (where + 1 > length_) {
		throw std::out_of_range ("CharList[] - out of range");
	} else {
		if (currentPlace_ == where) {
			return current_;
		} else if (currentPlace_ > where) {
			goFirst ();
		}

		while (currentPlace_ != where)
			goNext ();

		return current_;
	}
}

CharListEl* CharList::at (int where) {
	if (!first_) {
		throw std::out_of_range ("CharList[] - accessing empty list");
	} else if (where + 1 > length_) {
		throw std::out_of_range ("CharList[] - out of range");
	} else {
		if (currentPlace_ == where) {
			return current_;
		} else if (currentPlace_ > where) {
			goFirst ();
		}

		while (currentPlace_ != where)
			goNext ();

		return current_;
	}
}

void CharList::add (char s) {
	if (first_) {
		goFirst ();

		while (current_) {
			if (current_->s_ != s) {
				goNext ();
			} else
				break;
		}

		if (current_) {
			current_->weight_++;
		} else {
			last_->next_ = new CharListEl;
			last_ = last_->next_;
			last_->s_ = s;
			last_->weight_ = 1;
			length_++;
		}
	} else {
		first_ = new CharListEl;
		first_->s_ = s;
		first_->weight_ = 1;
		last_ = first_;
		current_ = first_;
		length_++;
	}
}

void CharList::recount() {
	goFirst();
	currentPlace_=0;

	while (current_) goNext();

	length_=currentPlace_;
}

CharList* CharList::split (int where) {
	if (where > 0) {
		CharListEl* newLast = (*this) [where - 1];
		CharList* newList = new CharList;
		newList->first_ = newLast->next_;
		newList->last_ = last_;
		newList->goFirst ();
		last_ = newLast;
		last_->next_ = 0;
		recount();
		newList->recount();

		return newList;
	} else {
		throw std::runtime_error ("split() - received 0 or less");
	}
}

void CharList::count() {
	goFirst();

	while (current_) {
		std::cout<<current_->s_<<": "<<current_->weight_<<"\n";
		goNext();
	}
}

void CharList::quicksort (CharListEl** arrayToSort, int left, int right) {
	int i = left, j = right;
	CharListEl x = *arrayToSort[ (left + right) / 2];

	do {
		while (*arrayToSort[i] < x) i++;

		while (*arrayToSort[j] > x) j--;

		if (i <= j) {
			if (*arrayToSort[i] > *arrayToSort[j]) {
				CharListEl* temp = arrayToSort[i];
				arrayToSort[i]=arrayToSort[j];
				arrayToSort[j]=temp;
			}

			i++;
			j--;
		}
	} while (i <= j);

	if (i < right)
		quicksort (arrayToSort, i, right);

	if (left < j)
		quicksort (arrayToSort, left, j);
}

void CharList::sort() {
	CharListEl** arrayToSort = new CharListEl*[length_];
	goFirst();
	int i = 0;

	while (current_) {
		arrayToSort[i]=current_;
		i++;
		goNext();
	}

	quicksort (arrayToSort,0,length_-1);
	first_=arrayToSort[length_-1];
	goFirst();

	for (i=1; i<length_; i++) {
		current_->next_=arrayToSort[length_-1-i];
		goNext();
	}

	current_->next_=0;
	delete[] arrayToSort;
}

int CharList::totalWeight() {
	int weight=0;
	goFirst();

	while (current_) {
		weight+=current_->weight_;
		goNext();
	}

	return weight;
}


CharList* CharList::equalSplit() {
	int weightLeft=0, weightRight=totalWeight(), i=0;



	goFirst();

	while (weightLeft<weightRight&&current_) {
		weightRight-=current_->weight_;
		weightLeft+=current_->weight_;
		goNext();
		i++;
		//std::cout<<weightLeft<<" "<<weightRight<<" "<<i<<'\n';
	}

	return split (i);
}

int CharList::getLength() {
	return length_;
}

int CharList::getFirstWeight() {
	if (first_)
		return first_->weight_;
	else throw std::out_of_range ("getFirstWeight - no element");
}

char CharList::getFirstSymbol() {
	if (first_)
		return first_->s_;
	else throw std::out_of_range ("getFirstSymbol - no element");
}
