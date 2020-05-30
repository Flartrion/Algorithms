#include "NodeList.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>

NodeList::NodeList() {
}

NodeList::~NodeList() {
	if (first_) {
		goFirst();
		Node* temp = current_;
		
		while (current_) {
			goNext();
			delete temp;
			temp = current_;
		}
	}
}

NodeList::Node::Node() : next_ (0), prev_ (0) {
}

NodeList::Node::Node (char name) : next_ (0), prev_ (0) {
	name_ = name;
}

NodeList::Node::~Node() {
}



NodeList::Node& NodeList::Node::setNext (Node* next_) {
	this->next_ = next_;
	return *this;
}
NodeList::Node& NodeList::Node::setPrev (Node* prev_) {
	this->prev_ = prev_;
	return *this;
}
NodeList::Node* NodeList::Node::getNext() {
	return next_;
}
NodeList::Node* NodeList::Node::getPrev() {
	return prev_;
}
char NodeList::Node::getName() {
	return name_;
}

bool NodeList::Node::compare (char otherNode) {
	if (name_ != otherNode) return false;
	else return true;
}



void NodeList::goFirst() {
	currentPos_ = 0;
	current_ = first_;
}



void NodeList::goLast() {
	currentPos_ = length_ - 1;
	current_ = last_;
}



void NodeList::goNext() {
	currentPos_++;
	current_ = current_->getNext();
}



void NodeList::goPrev() {
	currentPos_--;
	current_ = current_->getPrev();
}



void NodeList::pushBack (char name) {
	if (first_) {
		last_->setNext (new Node (name));
		last_->getNext()->setPrev (last_);
		last_ = last_->getNext();
	} else {
		first_ = new Node (name);
		last_ = first_;
		current_ = first_;
	}
	
	length_++;
}



void NodeList::addUnique (char name) {
	if (find (name) == -1) {
		pushBack (name);
	}
}



int NodeList::find (char name) {
	goFirst();
	while (current_) {
		if (!current_->compare (name)) goNext();
		else return currentPos_;
	}
	
	return -1;
}



char NodeList::at (int where) {
	if (where >= length_) throw std::out_of_range ("CityList::at - accessing nonexistent element");
	else if (!length_) throw std::out_of_range ("CityList::at - accessing empty list");
	else if (where < 0) throw std::invalid_argument("CityList::at - index less than 0");
	else {
		if (currentPos_ > where) {
			while (currentPos_ != where) goPrev();
		} else {
			while (currentPos_ != where) goNext();
		}
		
		return current_->getName();
		
	}
}



int NodeList::getLength() {
	return length_;
}



void NodeList::display() {
	std::cout << "ID|City name\n";
	
	for (int i = 0; i < length_; i++) {
		std::cout << std::left << std::setw (2) << i << "|" << std::left << at (i) << '\n';
	}
}
