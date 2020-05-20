#include <iostream>
#include <fstream>
#include "ShannonFanoNode.hpp"

int main () {
	CharList* BaseList = new CharList;
	ShannonFanoNode* root;
	Map<char, BinaryHolder>* dictionary;
	std::fstream in;

	in.open ("in.txt",std::ios::in);

	if (in.good()) {
		char k;

		while (true) { // inputting
			k = in.get();

			if (!in.eof())
				BaseList->add (k);
			else break;
		}

		in.close();

		try { // generating the map and the tree for encoding and decoding accordingly
			BaseList->sort();
			root = new ShannonFanoNode (BaseList);
			dictionary = root->generateMap();
		} catch (std::exception a) {
			std::cout<<a.what();
			std::cin.ignore();
		}

		in.open ("in.txt",std::ios::in);
		std::fstream out ("out.txt",std::ios::out);
		long infoSum = 0, infoCoded = 0;

		while (true) { // encoding
			k = in.get();

			if (!in.eof()) {
				BinaryHolder* element = dictionary->findByKey (k);
				out<<element->binary_;
				infoSum+=8;
				infoCoded+=element->length_;

			} else break;
		}
		
		std::cout<<"Unencoded: "<<infoSum<<"\nEncoded: "<<infoCoded<<'\n';
		std::cout<<"Space saved: "<<(100- (float) infoCoded/(float) infoSum * 100);
		
		out.close();
		in.close();
		in.open ("out.txt",std::ios::in);
		out.open ("out2.txt",std::ios::out);
		ShannonFanoNode* current = root;

		while (true) { // decoding
			k = in.get();

			if (!in.eof()) {
				if (k=='0') current=current->getLeft();
				else current=current->getRight();

				if (!current->getLeft()) {
					out<< (* (current->getInfo())) [0]->s_;
					current=root;
				}
			} else break;
		}
		std::cin.ignore();
	} else {
		std::cout<<"Bad";
	}

}
