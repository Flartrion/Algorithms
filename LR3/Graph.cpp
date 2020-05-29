#include "Graph.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <limits>

Graph::Graph() {

}

Graph::~Graph() {
	if (cities_) {
		int number = cities_->getLength();
		delete cities_;
		
		for (int i = 0; i < number; i++) {
			delete[] matrice_[i];
		}
		
		delete[] matrice_;
		delete[] edgeList_;
		
		if (lastSolutionFrom_) {
			delete[] prev_;
			delete[] distance_;
		}
	}
}

void Graph::input(std::string inFile) {
	std::fstream in (inFile, std::ios::in);
	std::string tempName;
	std::string naString ("N/A"); // Just for comparison.
	naString.pop_back();
	int stage = 0; // Goes from 0 to 3 as there are 4 fields in the presumed input file.
	int pos[2]; // Just here to hold city1 and city2.
	int number; // Is here to hold travelling fee.
	
	if (in.good()) {
		cities_ = new CityList;
		
		while (!in.eof()) { // Just counting number of cities and filling the list of them.
			if (stage < 2) {
				while (tempName.back() != ';' && !in.eof()) {
					tempName.push_back (in.get());
				}
				
				if (in.eof()) throw std::invalid_argument ("Graph::input - Provided file is incorrect!");
				
				tempName.pop_back();
				cities_->addUnique (tempName);
				tempName.clear();
				stage++;
			} else {
				while (in.get() != '\n' && !in.eof()) { // There still might be errors missed
				
				} // But I'll ignore that. For now.
				
				stage = 0;
			}
		}
		
		in.close();
		
		matrice_ = new int*[cities_->getLength()];
		
		for (int i = 0; i < cities_->getLength(); i++)
			matrice_[i] = new int[cities_->getLength()];
			
		for (int i = 0; i < cities_->getLength(); i++)
			for (int j = 0; j < cities_->getLength(); j++)
				matrice_[i][j] = INT_MAX;
				
		for (int i = 0; i < cities_->getLength(); i++)
			matrice_[i][i] = 0;
			
		in.open (inFile, std::ios::in);
		
		while (!in.eof()) { // Now filling in the matrice.
			if (stage < 2) { // Which cities those are?
				while (tempName.back() != ';' && !in.eof() && tempName.back() != '\n') {
					tempName.push_back (in.get());
				}
				
				if (in.eof()) throw std::invalid_argument ("Graph::input - Provided file is incorrect!"); // Shouldn't happen after the first checking, but will leave it here anyway
				
				tempName.pop_back();
				pos[stage] = cities_->find (tempName);
				tempName.clear();
				stage++;
			} else if (stage == 2) {
				if (in.peek() == 'N' || (in.peek() >= 48 && in.peek() <= 58)) {
					if (in.peek() == 'N') {
						while (tempName.back() != ';' && !in.eof()) tempName.push_back (in.get());
						
						tempName.pop_back();
						
						if (!tempName.compare (naString)) throw std::invalid_argument ("Graph::input - Provided file is incorrect!");
						
						tempName.clear();
					} else {
						in >> number;
						in.get();
						matrice_[pos[0]][pos[1]] = number;
					}
				} else throw std::invalid_argument ("Graph::input - Provided file is incorrect!");
				
				stage++;
			} else {
				if (in.peek() == 'N' || (in.peek() >= 48 && in.peek() <= 58)) {
					if (in.peek() == 'N') {
						while (tempName.back() != '\n' && !in.eof()) tempName.push_back (in.get());
						
						tempName.pop_back();
						
						if (!tempName.compare (naString)) throw std::invalid_argument ("Graph::input - Provided file is incorrect!");
						
						tempName.clear();
					} else {
						in >> number;
						in.get();
						matrice_[pos[1]][pos[0]] = number;
					}
				} else throw std::invalid_argument ("Graph::input - Provided file is incorrect!");
				
				stage = 0;
			}
		}
		
		in.close();
		
		fillEdgeList();
	} else {
		throw std::invalid_argument ("Graph::input - Provided file is incorrect!");
	}
}

void Graph::checkMatrice() {
	for (int i = 0; i < cities_->getLength(); i++) {
		for (int j = 0; j < cities_->getLength(); j++) {
			if (matrice_[i][j] == INT_MAX) std::cout << "S ";
			else std::cout << matrice_[i][j] << ' ';
		}
		
		std::cout << "\n";
	}
}

void Graph::fillEdgeList() {
	for (int i = 0; i < cities_->getLength(); i++)
		for (int j = 0; j < cities_->getLength(); j++) {
			if (matrice_[i][j] != INT_MAX && matrice_[i][j] != 0) {
				edgeListLength_++;
			}
		}
		
	edgeList_ = new Edge[edgeListLength_];
	int curEl = 0;
	
	for (int i = 0; i < cities_->getLength(); i++)
		for (int j = 0; j < cities_->getLength(); j++) {
			if (matrice_[i][j] != INT_MAX && matrice_[i][j] != 0) {
				edgeList_[curEl].a = i;
				edgeList_[curEl].b = j;
				edgeList_[curEl].cost = matrice_[i][j];
				curEl++;
			}
		}
}

void Graph::solveFordBellman (int from) {
	if (from >= cities_->getLength() || from < 0) throw std::invalid_argument ("Graph::solveFordBellman - received incorrect argument");
	else {
		if (lastSolutionFrom_ != from) {
			if (!prev_) prev_ = new int[cities_->getLength()];
			
			if (!distance_) distance_ = new int[cities_->getLength()];
			
			for (int i = 0; i < cities_->getLength(); i++) {
				prev_[i] = -1;
				distance_[i] = INT_MAX;
			}
			
			distance_[from] = 0;
			
			for (int j = 0; j < edgeListLength_; j++)
				if (edgeList_[j].a == from) {
					distance_[edgeList_[j].b] = edgeList_[j].cost;
					prev_[edgeList_[j].b] = from;
				}
				
				
			while (true) {
				bool any = false;
				
				for (int j = 0; j < edgeListLength_; j++) {
					if (distance_[edgeList_[j].a] != INT_MAX)
						if (distance_[edgeList_[j].b] > distance_[edgeList_[j].a] + edgeList_[j].cost) {
							distance_[edgeList_[j].b] = distance_[edgeList_[j].a] + edgeList_[j].cost;
							prev_[edgeList_[j].b] = edgeList_[j].a;
							any = true;
						}
				}
				
				if (!any)  {
					//for (int i = 0; i < cities_->getLength(); i++) {
					//	std::cout << prev_[i] << ' ' << distance_[i] << '\n';
					//}
					
					break;
				}
			}
		}
	}
}

void Graph::solve (int from, int to) {

	if (to > cities_->getLength() || to < 0) throw std::invalid_argument ("Graph::solve - received incorrect argument");
	else {
		solveFordBellman (from);
		
		int way[cities_->getLength()];
		int i = 0, current = to;
		
		if (distance_[to] != INT_MAX) {
			way[0] = current;
			
			while (current != -1) {
				way[i] = current;
				current = prev_[current];
				i++;
			}
			
			i--;
			std::cout << "Cheapest flight: " << distance_[to] << ", with the path:\n";
			
			while (i >= 0) {
				std::cout << cities_->at (way[i]);
				
				if (i >= 1) {
					std::cout << " -> ";
				}
				
				i--;
			}
			
			std::cout << '\n';
		} else {
			std::cout << "\nNo such way exists!";
		}
	}
}

void Graph::displayCities() {
	cities_->display();
}
