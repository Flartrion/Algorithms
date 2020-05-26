#pragma once
#include "CharList.hpp"
#include "Map.hpp"
#include <iomanip>

struct BinaryHolder {
	int length_=0;
	char* binary_=0;

	~BinaryHolder();
};

class ShannonFanoNode {
protected:
	CharList* info_=0;
	ShannonFanoNode* left_=0, *right_=0;

	int height (ShannonFanoNode* node, int curHeight);

	void traverse(ShannonFanoNode* node, int curHeight, char* code, Map<char, BinaryHolder>* output, bool displayTable);
public:
	ShannonFanoNode();
	ShannonFanoNode (CharList*);
	~ShannonFanoNode();

	ShannonFanoNode* getLeft();
	
	ShannonFanoNode* getRight();
	
	CharList* getInfo();
	
	void setInfo (CharList*);

	void beginSplitting();

	Map<char, BinaryHolder>* generateMap(bool displayTable);
};
