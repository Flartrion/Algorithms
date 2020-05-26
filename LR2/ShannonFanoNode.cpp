#include "ShannonFanoNode.hpp"
#include <iomanip>


BinaryHolder::~BinaryHolder() {
	if (binary_) delete[] binary_;
}


ShannonFanoNode::ShannonFanoNode() {
}

ShannonFanoNode::~ShannonFanoNode() {
}

ShannonFanoNode::ShannonFanoNode (CharList* info) {
	info_ = info;

	if (info_->getLength() >1) {
		CharList* toRight = info_->equalSplit();
		left_ = new ShannonFanoNode (info_);
		right_ = new ShannonFanoNode (toRight);
		info_ = 0;
	}
}

void ShannonFanoNode::setInfo (CharList* info) {
	info_ = info;
}

void ShannonFanoNode::beginSplitting() {
	if (info_->getLength() >1) {
		CharList* toRight = info_->equalSplit();
		left_ = new ShannonFanoNode (info_);
		right_ = new ShannonFanoNode (toRight);
		info_ = 0;
	}
}

int ShannonFanoNode::height (ShannonFanoNode* node, int curHeight) {
	int leftHeight = 0, rightHeight = 0;

	if (node->left_&&node->right_) {
		leftHeight = height (node->left_,curHeight+1);
		rightHeight = height (node->right_,curHeight+1);

		return (leftHeight>rightHeight?leftHeight:rightHeight);
	} else {
		//std::cout<< (* (node->info_)) [0]->s_<<" "<<(* (node->info_)) [0]->weight_<<" "<<curHeight<<"\n";
		return curHeight;
	}
}

void ShannonFanoNode::traverse (ShannonFanoNode* node, int curHeight, char* code, Map<char, BinaryHolder>* output, bool displayTable) {
	char* charToDisplay;

	if (node->left_&&node->right_) {
		code[curHeight-1]='0';
		traverse (node->left_, curHeight+1, code, output, displayTable);
		code[curHeight-1]='1';
		traverse (node->right_, curHeight+1, code, output, displayTable);
	} else {
		BinaryHolder* newMapInfoHolder = new BinaryHolder;
		newMapInfoHolder->binary_ = new char[curHeight];

		charToDisplay = new char[4];
		charToDisplay[0] = '\"';
		charToDisplay[1] = node->info_->getFirstSymbol();
		charToDisplay[2] = '\"';
		charToDisplay[3] = '\0';

		for (int i = 0; i<curHeight-1; i++) {
			//std::cout<<code[i];
			newMapInfoHolder->binary_[i]=code[i];
		}

		newMapInfoHolder->binary_[curHeight-1]='\0';
		//std::cout<<'\n';
		newMapInfoHolder->length_=curHeight-1;

		if (charToDisplay[1]==10) {
			delete charToDisplay;
			charToDisplay = new char[5];
			charToDisplay[0] = '\"';
			charToDisplay[1] = 'n';
			charToDisplay[2] = 'l';
			charToDisplay[3] = '\"';
			charToDisplay[4] = '\0';
		}

		if (displayTable) {
			std::cout<<std::setw (6) <<std::left<<charToDisplay<<'|'<<
			         std::setw (6) <<std::left<<node->info_->getFirstWeight() <<'|'<<
			         std::setw (20) <<std::left<<newMapInfoHolder->binary_<<'\n';
		}

		output->insert ( (* (node->info_)) [0]->s_,*newMapInfoHolder);
	}
}

Map<char,BinaryHolder>* ShannonFanoNode::generateMap(bool displayTable) {
	int totalHeight = 0;
	totalHeight = height (this, 0);
	char* binaryCode = new char[totalHeight];
	Map<char, BinaryHolder>* output = new Map<char, BinaryHolder>;

	traverse (this, 1, binaryCode, output, displayTable);

	return output;
	//std::cout<<'\n'<<totalHeight<<'\n';
	//std::cin.ignore();
}

ShannonFanoNode* ShannonFanoNode::getLeft() {
	return left_;
}

ShannonFanoNode* ShannonFanoNode::getRight() {
	return right_;
}

CharList* ShannonFanoNode::getInfo() {
	return info_;
}
