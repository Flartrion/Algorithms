#include <string>
#pragma once

/*!
 * \brief Basically a list with few extra steps.
 * Includes handy stuff like finding position by name, comparison, unique adding and such.
 */
class CityList {
protected:
	/*!
	 * \brief A thing to hold city names. A primitive list element, basically.
	 */
	class City {
	protected:
		std::string name_;
		City* next_, *prev_;
		
	public:
		City();
		City (std::string name);
		~City();
		
		City& setNext (City* next_);
		City& setPrev (City* prev_);
		std::string getName();
		City* getNext();
		City* getPrev();
		
		bool compare (std::string otherName);
	};
	
	City* first_ = 0, *last_ = 0, *current_ = 0;
	int length_ = 0, currentPos_ = 0;
	
	void goNext();
	void goFirst();
	void goLast();
	void goPrev();
	
	/*!
	* \brief Adds to the end of the list an element with the name of param
	* \param name
	*/
	void pushBack (std::string name);
public:
	CityList();
	~CityList();
	
	/*!
	* \brief Adds new element if it's unique
	* \param name
	*/
	void addUnique (std::string name);
	
	/*!
	* \brief Searches position of the city by the name in argument
	* \param name
	* \return position if exists, -1 if not.
	*/
	int find (std::string name);
	
	/*!
	 * \brief Gives the name of the city at the certain adress of the list
	 * \param where
	 * 0 to length-1
	 * \return Name of the city
	 */
	std::string at (int where);
	
	/*!
	 * \brief Displays a table of id and names of cities.
	 */
	void display();
	
	int getLength();
};
