#include <iostream>
#include <fstream>
#include "CharList.hpp"
#include "Map.hpp"

int main () {
	CharList BaseList;
	std::fstream in;
	
	in.open("in.txt",std::ios::in);

	if (in.good()) {
		while (!in.eof()) {
			BaseList.add (in.get());
		}
		// Input and sorting checking
		/*
		BaseList.count();
		BaseList.sort();
		BaseList.count();
		*/
		BaseList.sort();
	} else {
		std::cout<<"Bad";
	}
	
	in.close();
	std::cin.ignore();
}
