#include <iostream>
#include <string>
#include "ShannonFanoNode.hpp"

int main () {
	CharList* BaseList = new CharList;
	ShannonFanoNode* root;
	Map<char, BinaryHolder>* dictionary;
	std::string text;
	//in.open ("in.txt",std::ios::in);

	std::cout<<"Unencoded: ";
	while (text.empty()) {
	std::getline (std::cin, text);
	}
	std::cout<<'\n';

	unsigned int i = 0;


	while (i < text.length()) { // inputting
		BaseList->add (text[i++]);
	}

	std::cout<<"Symbol|Weight|Code\n";

	try { // generating the map and the tree for encoding and decoding accordingly
		BaseList->sort();
		root = new ShannonFanoNode (BaseList);
		dictionary = root->generateMap (true);
	} catch (std::exception a) {
		std::cout<<a.what();
		std::cin.ignore();
	}

	long infoSum = 0, infoCoded = 0;

	std::cout<<"\nEncoded:\n";

	i = 0;

	while (i < text.length()) { // encoding
		BinaryHolder* element = dictionary->findByKey (text[i++]);
		std::cout<<element->binary_;
		infoSum+=8;
		infoCoded+=element->length_;
	}

	ShannonFanoNode* current = root;

	std::cout<<"\n\nTo decode:";

	text.clear();

	while (text.empty()) {
		std::getline (std::cin, text);
	}

	i = 0;

	while (i < text.length()) { // decoding

		if (text[i++] == '0') current=current->getLeft();
		else current=current->getRight();

		if (!current->getLeft()) {
			std::cout<<current->getInfo()->getFirstSymbol();
			current=root;
		}
	}

	std::cout<<"\n\nUnencoded: "<<infoSum<<"\nEncoded: "<<infoCoded<<'\n';
	std::cout<<"Compression: "<< (static_cast<float> (infoCoded) / static_cast<float> (infoSum) * 100) <<'%';

	std::cin.ignore();
}
