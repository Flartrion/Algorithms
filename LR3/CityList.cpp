#include "CityList.hpp"
#include "stdexcept"
#include <iostream>

CityList::CityList() {
}

CityList::~CityList() {
	if (first_) {
		goFirst();
		City* temp = current_;
		
		while (current_) {
			goNext();
			delete temp;
			temp = current_;
		}
	}
}

CityList::City::City() : next_ (0), prev_ (0) {
}

CityList::City::City (std::string name) : next_ (0), prev_ (0) {
	name_ = name;
}

CityList::City::~City() {
}

CityList::City& CityList::City::setNext (City* next_) {
	this->next_ = next_;
	return *this;
}
CityList::City& CityList::City::setPrev (City* prev_) {
	this->prev_ = prev_;
	return *this;
}
CityList::City* CityList::City::getNext() {
	return next_;
}
CityList::City* CityList::City::getPrev() {
	return prev_;
}
std::string CityList::City::getName() {
	return name_;
}



bool CityList::City::compare (std::string otherCity) {
	if (name_.compare (otherCity)) return false;
	else return true;
}



void CityList::goFirst() {
	currentPos_ = 0;
	current_ = first_;
}

void CityList::goLast() {
	currentPos_ = length_ - 1;
	current_ = last_;
}


void CityList::goNext() {
	currentPos_++;
	current_ = current_->getNext();
}

void CityList::goPrev() {
	currentPos_--;
	current_ = current_->getPrev();
}

void CityList::pushBack (std::string name) {
	if (first_) {
		last_->setNext (new City (name));
		last_->getNext()->setPrev (last_);
		last_ = last_->getNext();
	} else {
		first_ = new City (name);
		last_ = first_;
		current_ = first_;
	}
	
	length_++;
}

void CityList::addUnique (std::string name) {
	if (find (name) == -1) {
		pushBack (name);
	}
}

int CityList::find (std::string name) {
	goFirst();
	
	while (current_) {
		if (!current_->compare (name)) goNext();
		else return currentPos_;
	}
	
	return -1;
}

std::string CityList::at (int where) {
	if (where > length_) throw std::out_of_range ("CityList::at - accessing nonexistent element");
	
	if (!length_) throw std::out_of_range ("CityList:at - accessing empty list");
	
	if (currentPos_ > where) {
		while (currentPos_ != where) goPrev();
	} else {
		while (currentPos_ != where) goNext();
	}
	
	return current_->getName();
}

int CityList::getLength() {
	return length_;
}

void CityList::display() {
	for (int i = 0; i < length_; i++) {
		std::cout << i << "   " << at (i) << '\n';
	}
}
