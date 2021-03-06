#include "Graph.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <limits>

Graph::Graph() {

}


Graph::~Graph() {
	if (matrice_) {
		for (int i = 0; i < nodes_->getLength(); i++) {
			delete[] matrice_[i];
			delete[] availableConductivity_[i];
		}
		
		delete[] matrice_;
		delete[] availableConductivity_;
	}
	
	delete nodes_;
}


void Graph::input (std::string inFile) {
	std::fstream in (inFile, std::ios::in);
	char tempName;
	char afterChar;
	
	int stage = 0; // Goes from 0 to 2 as there are 3 fields in the presumed input file.
	int position[2]; // Just here to hold node1 and node2.
	int number; // Is here to hold conductivity.
	
	if (in.good()) {
		nodes_ = new NodeList;
		
		while (!in.eof()) { // Just counting number of cities and filling the list of them.
			if (stage < 2) {
				in >> tempName;
				afterChar = in.get();
				
				if (afterChar == ' ') {
					nodes_->addUnique (tempName);
					
					if (tempName == 'S' && start_ < 0) {
						start_ = nodes_->find ('S');
					}
					
					if (tempName == 'T' && terminator_ < 0) {
						terminator_ = nodes_->find ('T');
					}
					
					stage++;
				} else {
					throw std::invalid_argument ("Graph::input - Provided file is incorrect: unrecognized sybmol after node name!");
					break;
				}
			} else {
				while (in.get() != '\n' && !in.eof()) { // There still might be errors missed
				
				} // But I'll ignore that. For now.
				
				stage = 0;
			}
		}
		
		in.close();
		
		if (terminator_ < 0 || start_ < 0)
			throw std::invalid_argument ("Graph::input - Provided file is incorrect: flow network has no source and|or drain!");
		else {
		
			// Matrices initial setup begin!
			matriceInit();
			// Matrices initial setup end!
			
			in.open (inFile, std::ios::in);
			
			while (!in.eof()) { // Now filling in the matrice.
				if (stage < 2) { // Which nodes those are?
					in >> tempName;
					afterChar = in.get();
					
					if (afterChar == ' ') {
						position[stage] = nodes_->find (tempName);
						stage++;
					} else {
						throw std::invalid_argument ("Graph::input - Provided file is incorrect: unrecognized sybmol after node name!");
						break;
					}
				} else { // And now to read the number and input it into the matrice.
					in >> number;
					afterChar = in.get();
					
					if (in.peek() == '\n') {
						throw std::invalid_argument ("Graph::input - Provided file is incorrect: encountered an empty line!");
						break;
					} else {
						if (number >= 0 && (afterChar == '\n' || afterChar == -1)) {
							matrice_[position[0]][position[1]] = number;
							
							if (matrice_[position[1]][position[0]] && matrice_[position[1]][position[0]] != number)
								throw std::invalid_argument ("Graph::input - Provided file is incorrect: two-way edge is asymmetrical!");
								
							stage = 0;
						} else {
							if (number < 0)
								throw std::invalid_argument ("Graph::input - Provided file is incorrect: found negative number!");
							else
								throw std::invalid_argument ("Graph::input - Provided file is incorrect: unrecognized symbol after number!");
								
							break;
						}
					}
				}
			}
			
			in.close();
			
			for (int i = 0; i < nodes_->getLength(); i++)
				for (int j = 0; j < nodes_->getLength(); j++)
					availableConductivity_[i][j] = matrice_[i][j];
		}
	} else {
		throw std::invalid_argument ("Graph::input - Provided file wasn't found!");
	}
}


void Graph::checkMatrice() {
	for (int i = 0; i < nodes_->getLength(); i++) {
		for (int j = 0; j < nodes_->getLength(); j++) {
			if (matrice_[i][j] == INT_MAX) std::cout << "S ";
			else std::cout << matrice_[i][j] << ' ';
		}
		
		std::cout << "\n";
	}
}


void Graph::displayNodes() {
	nodes_->display();
}


void Graph::matriceInit() {
	if (matrice_ || availableConductivity_) {
		for (int i = 0; i < nodes_->getLength(); i++) {
			delete[] matrice_[i];
			delete[] availableConductivity_[i];
		}
		
		delete [] matrice_;
		delete [] availableConductivity_;
	}
	
	matrice_ = new int*[nodes_->getLength()];
	availableConductivity_ = new int*[nodes_->getLength()];
	
	for (int i = 0; i < nodes_->getLength(); i++) {
		matrice_[i] = new int[nodes_->getLength()];
		availableConductivity_[i] = new int[nodes_->getLength()];
	}
	
	for (int i = 0; i < nodes_->getLength(); i++)
		for (int j = 0; j < nodes_->getLength(); j++)
			matrice_[i][j] = 0;
			
	for (int i = 0; i < nodes_->getLength(); i++)
		matrice_[i][i] = 0;
}


Graph::IteratorByWidth* Graph::initEdmondsKarpIterator() {
	return new Graph::IteratorByWidth (nodes_->getLength(), availableConductivity_, start_);
}


int Graph::solve() {
	int flowSum = 0;
	IteratorByWidth* stepper;
	bool changeFlag = true;
	int *parents;
	
	while (changeFlag) {
		int terminatorPos = -2;
		
		stepper = initEdmondsKarpIterator();
		
		while (terminatorPos != terminator_ && terminatorPos != -1) {
			terminatorPos = stepper->step();
		}
		
		if (terminatorPos == terminator_) {
			changeFlag = true;
			int minFlow = INT_MAX;
			int currentPos = terminatorPos;
			parents = stepper->getCurrentRoutes();
			
			while (parents[currentPos] != -1) {
				if (availableConductivity_[parents[currentPos]][currentPos] < minFlow)
					minFlow = availableConductivity_[parents[currentPos]][currentPos];
					
				currentPos = parents[currentPos];
			}
			
			flowSum += minFlow;
			currentPos = terminatorPos;
			
			while (parents[currentPos] != -1) {
				availableConductivity_[parents[currentPos]][currentPos] -= minFlow;
				
				if (availableConductivity_[currentPos][parents[currentPos]])
					availableConductivity_[currentPos][parents[currentPos]] -= minFlow;
					
				currentPos = parents[currentPos];
			}
			
			delete[] parents;
		} else changeFlag = false;
		
		delete stepper;
	}
	
	return flowSum;
}
