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

		std::cout<<"Unencoded:\n";

		while (true) { // inputting
			k = in.get();

			if (!in.eof()) {
				std::cout<<k;
				BaseList->add (k);
			} else break;
		}

		in.close();

		std::cout<<"\n\nSymbol|Weight|Code\n";

		try { // generating the map and the tree for encoding and decoding accordingly
			BaseList->sort();
			root = new ShannonFanoNode (BaseList);
			dictionary = root->generateMap(true);
		} catch (std::exception a) {
			std::cout<<a.what();
			std::cin.ignore();
		}

		in.open ("in.txt",std::ios::in);
		std::fstream out ("out.txt",std::ios::out);
		long infoSum = 0, infoCoded = 0;

		std::cout<<"\nEncoded:\n";

		while (true) { // encoding
			k = in.get();

			if (!in.eof()) {
				BinaryHolder* element = dictionary->findByKey (k);
				out<<element->binary_;
				std::cout<<element->binary_;
				infoSum+=8;
				infoCoded+=element->length_;

			} else break;
		}

		out.close();
		in.close();
		in.open ("out.txt",std::ios::in);
		out.open ("out2.txt",std::ios::out);
		ShannonFanoNode* current = root;

		std::cout<<"\n\nDecoded back:\n";

		while (true) { // decoding
			k = in.get();

			if (!in.eof()) {

				if (k=='0') current=current->getLeft();
				else current=current->getRight();

				if (!current->getLeft()) {
					out<< current->getInfo()->getFirstSymbol();
					std::cout<<current->getInfo()->getFirstSymbol();
					current=root;
				}
			} else break;
		}

		std::cout<<"\n\nUnencoded: "<<infoSum<<"\nEncoded: "<<infoCoded<<'\n';
		std::cout<<"Compression: "<< (static_cast<float> (infoCoded) / static_cast<float> (infoSum) * 100) <<'%';

		std::cin.ignore();
	} else {
		std::cout<<"Bad";
	}

}
