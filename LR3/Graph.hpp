#pragma once
#include "CityList.hpp"
struct Edge {
	int a = -1, b = -1, cost = 0;
};

class Graph {
protected:
	CityList* cities_ = 0; // A name list to fill and forget until the time cometh.
	int** matrice_ = 0; // That's where all the routes will be stored.
	
	Edge* edgeList_ = 0; // Will collect edges. Reusable, thus is being held here.
	int edgeListLength_ = 0; // Number of edges.
	int lastSolutionFrom_ = -1; // Optimization purpose. So as not to calculate ways again if starting point doesn't change.
	int *prev_ = 0; // Holds previous node for every shortest path to every node.
	int *distance_ = 0; // Holds shortest pathes to every node.
	
	/*!
	 * \brief Translates the matrice into the list of it's singular edges
	 */
	void fillEdgeList();
	
	/*!
	 * \brief Solves system from the city of it's param
	 * \param from
	 */
	void solveBellmanFord (int from);
public:
	Graph();
	~Graph();
	
	/*!
	 * \brief Input stuff from "in.txt"
	 * \param Name of the file to input from.
	 */
	void input(std::string inFile);
	
	/*!
	 * \brief Just here to output in console matrice for checking and such.
	 */
	void checkMatrice();
	
	/*!
	 * \brief Displays cities in appearance order.
	 * Actually just passes control to CityList inside.
	 */
	void displayCities();
	
	/*!
	 * \brief Traces way back from "to" to "from".
	 * \param from
	 * \param to
	 */
	void solve (int from, int to);
};
