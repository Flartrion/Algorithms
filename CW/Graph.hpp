#pragma once
#include "NodeList.hpp"
#include <stdexcept>

class Graph {
protected:
	class IteratorByWidth;
	
	NodeList* nodes_ = 0; // A name list to fill and forget until the time cometh.
	int** matrice_ = 0; // That's where all the routes will be stored.
	int** availableConductivity_ = 0;
	
	int start_ = -1, terminator_ = -1; // S and T, kept as their id's in node list.
	
	
	/*!
	 * \brief Creates square matrices in size of nodes_ length in matrice_ and availableConductivity_ fields.
	 */
	void matriceInit();
public:
	Graph();
	~Graph();
	
	/*!
	 * \brief Input stuff from "in.txt"
	 * \param Name of the file to input from.
	 */
	void input (std::string inFile);
	
	/*!
	 * \brief Just here to output matrice in console for checking and such.
	 */
	void checkMatrice();
	
	/*!
	 * \brief Will use availableConductivity_ to create an iterator.
	 */
	IteratorByWidth* initEdmondsKarpIterator();
	
	/*!
	 * \brief Displays cities in appearance order.
	 * Actually just passes control to NodeList inside.
	 */
	void displayNodes();
	
	/*!
	 * \brief Will find the maximal flow using Edmonds-Karp algorithm.
	 * \return Maximal flow.
	 */
	int solve();
};

class Graph::IteratorByWidth {
protected:
	int** routes_ = 0;
	
	int length_ = 0; // This one here is variable that defines sizes of everything else.
	
	int* queue_ = 0; // Isn't worth implementing an actual queue data structure. This will do nicely.
	bool* visited_ = 0; // To evade troubles with cycling and such.
	int* prev_ = 0; // To trace chosen path back to start.
	int current_ = -1; // Respresents current place in matrix. So as not to hit same edges twice.
	int queueCurrent_ = 0; // Position in queue.
	int queueLength_ = 1; // As it states.
public:

	/*!
	 * \brief Shouldn't be used at all (come on, setters/getters are unhandy), so is declared to just throw an exception.
	 */
	IteratorByWidth() {
		throw std::runtime_error ("Graph::IteratorByWidth - Incorrect initialization!");
	};
	
	/*!
	 * \brief Actual default constructor.
	 * \param length
	 * Pass here nodes_->getLength().
	 * \param edges
	 * Pass here whatever matrice of the two you want. It's a part of Graph class for a reason.
	 * \param start
	 * Pass here start. From here it will trace any routes.
	 */
	IteratorByWidth (int length, int** edges, int start);
	~IteratorByWidth();
	
	/*!
	 * \brief Takes a step in matrice_
	 * \return Returns id of the current node it found and -1 otherwise.
	 */
	int step();
	
	/*!
	 * \brief Part of Edmonds-Karp algorithm.
	 * \return prev_ copy
	 * Will return a copy of prev_ for anything that invoked that method to calculate way back from current position (which was returned by step(), presumably).
	 */
	int* getCurrentRoutes();
};
