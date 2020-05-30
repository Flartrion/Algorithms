#pragma once
#include <string>

/*!
 * \brief Basically a list with few extra steps.
 * Includes handy stuff like finding position by name, comparison, unique adding and such.
 */
class NodeList {
protected:
	/*!
	 * \brief A thing to hold city names. A primitive list element, basically.
	 */
	class Node;
	
	Node* first_ = 0, *last_ = 0, *current_ = 0;
	int length_ = 0, currentPos_ = 0;
	
	void goNext();
	void goFirst();
	void goLast();
	void goPrev();
	
	/*!
	* \brief Adds to the end of the list an element with the name of param
	* \param name
	*/
	void pushBack (char name);
public:
	NodeList();
	~NodeList();
	
	/*!
	* \brief Adds new element if it's unique
	* \param name
	*/
	void addUnique (char name);
	
	/*!
	* \brief Searches position of the city by the name in argument
	* \param name
	* \return position if exists, -1 if not.
	*/
	int find (char name);
	
	/*!
	 * \brief Gives the name of the city at the certain adress of the list.
	 * Actually just a remainder from LR3. Isn't needed anymore, but still.
	 * \param where
	 * 0 to length-1
	 * \return Name of the city
	 */
	char at (int where);
	
	/*!
	 * \brief Displays a table of id and names of cities.
	 */
	void display();
	
	int getLength();
};

class NodeList::Node {
protected:
	char name_;
	Node * next_, *prev_;
	
public:
	Node();
	Node (char name);
	~Node();
	
	Node & setNext (Node * next_);
	Node & setPrev (Node * prev_);
	char getName();
	Node * getNext();
	Node * getPrev();
	
	bool compare (char otherName);
};
