#pragma once
class CharListEl {
public:
	CharListEl();
	~CharListEl();
	char s_ = 0;
	int weight_ = 0;
	CharListEl* next_ = 0;

	bool operator> (CharListEl other);

	bool operator< (CharListEl other);
};

class CharList {
protected:
	CharListEl *first_ = 0, *last_ = 0, *current_ = 0;
	int currentPlace_ = 0, length_ = 0;

	void goFirst ();

	void goNext ();

	void quicksort (CharListEl**, int, int);

	void recount();

public:
	CharList();
	~CharList();
	
	CharList* split (int where);  // Makes targeted element new head of returned list, thus splitting them.

	void sort();
	
	int getLength();
	
	int totalWeight();

	CharList* equalSplit(); // Splits list evenly by counting weights.

	CharListEl* operator[] (int where); // Returns single element of the list. A-la array.

	void add (char s);  // Find targeted symbol and create new element or add to which is already here.

	void count(); // Just for self-control
};
