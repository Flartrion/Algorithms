#include <stdexcept>
#include <iostream>
#include "Graph.hpp"

Graph::IteratorByWidth::IteratorByWidth (int length, int** routes, int start) {
	routes_ = routes;
	queue_ = new int[length];
	prev_ = new int[length];
	visited_ = new bool[length];
	
	length_ = length;
	
	for (int i = 0; i < length; i++) {
		queue_[i] = prev_[i] = -1;
		visited_[i] = false;
	}
	
	visited_[start] = true;
	queue_[0] = start;
}


Graph::IteratorByWidth::~IteratorByWidth () {
	if (length_) {
		delete[] queue_;
		delete[] prev_;
		delete[] visited_;
	}
}


int* Graph::IteratorByWidth::getCurrentRoutes() {
	int *returnArray = new int[length_];
	
	for (int i = 0; i < length_; i++)
		returnArray[i] = prev_[i];
		
	return returnArray;
}

int Graph::IteratorByWidth::step() {
	current_++;
	
	if (current_ == length_) {
		queueCurrent_++;
		current_ = 0;
	}
	
	while (current_ < length_ && queue_[queueCurrent_] != -1 && queueLength_ < length_) {
		if (routes_[queue_[queueCurrent_]][current_] == 0)
			current_++;
		else {
			if (visited_[current_]) current_++;
			else {
				visited_[current_] = true;
				queue_[queueLength_++] = current_;
				prev_[current_] = queue_[queueCurrent_];
				return current_;
			}
		}
		
		if (current_ == length_) {
			queueCurrent_++;
			current_ = 0;
		}
	}
	
	return -1;
}
