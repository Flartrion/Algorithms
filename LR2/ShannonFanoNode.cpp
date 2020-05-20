#include "ShannonFanoNode.hpp"


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

void ShannonFanoNode::traverse (ShannonFanoNode* node, int curHeight, char* code, Map<char, BinaryHolder>* output) {
	if (node->left_&&node->right_) {
		code[curHeight-1]='0';
		traverse (node->left_,curHeight+1,code,output);
		code[curHeight-1]='1';
		traverse (node->right_,curHeight+1,code,output);
	} else {
		BinaryHolder* temp = new BinaryHolder;
		temp->binary_ = new char[curHeight];

		for (int i = 0; i<curHeight-1; i++) {
			//std::cout<<code[i];
			temp->binary_[i]=code[i];
		}
		temp->binary_[curHeight-1]='\0';
		//std::cout<<'\n';

		temp->length_=curHeight-1;
		output->insert ( (* (node->info_)) [0]->s_,*temp);
	}
}

Map<char,BinaryHolder>* ShannonFanoNode::generateMap() {
	int totalHeight = 0;
	totalHeight = height (this, 0);
	char* binaryCode = new char[totalHeight];
	Map<char, BinaryHolder>* output = new Map<char, BinaryHolder>;

	traverse (this,1,binaryCode,output);

	return output;
	//std::cout<<'\n'<<totalHeight<<'\n';
	//std::cin.ignore();
}

ShannonFanoNode* ShannonFanoNode::getLeft()
{
	return left_;
}

ShannonFanoNode* ShannonFanoNode::getRight()
{
	return right_;
}

CharList* ShannonFanoNode::getInfo()
{
	return info_;
}
