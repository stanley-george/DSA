#include <iostream>
#include <vector>
#include <string>
#include <new>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <list>
#include <limits>
#include <ctime>
#include "Hash.h"
#include "Heap.h"
#include "Graph.h"

/********************************************************************

			     Graph()

********************************************************************/
Graph::Graph () {
	nVerticies = 0;
	nEdges = 0;
	try {
		_graph = new std::list<Vertex>;
		lookupTable = new hashTable (0);
	}
	catch (std::bad_alloc& ba) {
		std::cerr << "Error: " << ba.what() << std::endl;
		exit(1);
	}
}


/********************************************************************

			Graph::Vertex()

********************************************************************/
Graph::Vertex::Vertex (std::string id) {
	iD = id;
	dv = std::numeric_limits<int>::max();
	known = false;
	adj_list = new std::list<ENode>;
	prev = NULL;
}


/*******************************************************************

			   vertexExists()

********************************************************************/

bool Graph::vertexExists(const std::string& id) {
	/*if id is in lookupTable then vertex exists*/
	if(lookupTable-> contains(id))
		return true;
	return false;
}


/*******************************************************************

			checkvertexPointer()

********************************************************************/

void Graph::checkvertexPointer (Vertex *v /*std::string s*/) {
	/*Vertex *v = static_cast <Vertex *> (lookupTable->getPointer(s));*/
	if (v != NULL) {
		std::cout << std::endl;
		std::cout << "The vertex is at address " << v << std::endl;
		std::cout << "The id is: " << v-> iD << std::endl;
		std::cout << "The dv is: " << v-> dv << std::endl;
		std::cout << "The current status is: ";
		if (v-> known) {
			std::cout << "Known" << std::endl;
			std::cout << std::endl;

		}
		else {
			std::cout << "Unknown" << std::endl;
			std::cout << std::endl;
		}
	}
}




/*******************************************************************

			unknownVertex_Exists()

********************************************************************/
bool Graph::unknownVertex_Exists () {

	std::list<Vertex>::const_iterator it;
	/*loop through _graph and check if any unknown verticies exist*/
	for (it = _graph-> begin(); it != _graph-> end(); it++) {
		if (it-> known)
			return true;
	}
	return false;
}

/*******************************************************************

			initalizeHeap()

********************************************************************/
void Graph::initializeHeap() {
	try {	
		g_heap = new heap(_graph-> size());	
	}
	catch (std::bad_alloc& ba) {
		std::cerr << ba.what() << std::endl;
	}	
}



/*******************************************************************

			   Dijkstra()

********************************************************************/
int Graph::Dijkstra (std::string start/*, std::ofstream &outfile2*/) {

	Vertex *s = static_cast <Vertex *> (lookupTable-> getPointer(start));
	Vertex *v = new Vertex("");
	Vertex *w = new Vertex("");

	std::list<ENode>::iterator eit;

	s-> dv = 0;
	/*push s into priority queue*/

	g_heap-> insert(s-> iD, s-> dv, s);


	std::string *pId = NULL;
	int *pKey = NULL;


	while (g_heap-> deleteMin(pId, pKey, &v) != 1) {
		//outfile2 << "We just deleted the vertex with minimum dv..." << std::endl << std::endl;
		v-> known = true;
        //outfile2 << v-> iD << " is now known " << std::endl;
		/*for each adjacent vertex*/
		for (eit = v-> adj_list-> begin(); eit != v-> adj_list-> end(); eit++) {
			w = static_cast <Vertex *> (lookupTable-> getPointer(eit-> adj_iD));
           // outfile2 << "At vertex " << w-> iD << std::endl;
            int old_dv = w-> dv;
			if (v-> dv + eit-> edgeCost < w-> dv) {
				w-> dv = v-> dv + eit-> edgeCost;
				int new_dv = w-> dv;
				//outfile2 << "We just updated " << w-> iD << " from " << old_dv << " to " << w-> dv << std::endl;
				w-> prev = v;
				//outfile2 << "The pred of " << w-> iD << " is now " << w->prev->iD << std::endl;
				//checkvertexPointer (w);
				int already_in_heap = g_heap-> insert(w-> iD, w-> dv, w);
				if (already_in_heap == 2)
					g_heap-> setKey(w-> iD, new_dv);
			}
		}
	}
	return 0;
}

/*******************************************************************

			insert()

********************************************************************/

int Graph::insert (std::string& iD, std::string& adj_iD, int& cost) {

	if (!vertexExists (iD)) {
		Vertex *pVertex = new Vertex (iD);
		_graph-> push_back(*pVertex);
		std::list<Vertex>::iterator it = --(_graph-> end());
		/*lookupTable-> insert(iD, pVertex);*/
		lookupTable-> insert(iD, &(*it));
		nVerticies++;
	}

	if (!vertexExists (adj_iD)) {
		Vertex *pVertex = new Vertex (adj_iD);
		_graph-> push_back(*pVertex);
		std::list<Vertex>::iterator it = --(_graph-> end());
		/*lookupTable-> insert(adj_iD, pVertex);*/
		lookupTable-> insert(adj_iD, &(*it));
		nVerticies++;
	}

	ENode *pNode = new ENode (adj_iD, cost);
	Vertex *pVertex = static_cast <Vertex *> (lookupTable-> getPointer(iD));

	pVertex-> adj_list-> push_back(*pNode);
	nEdges++;
	return 0;
}



/*********************************************************************

			 printGraph()
			
*********************************************************************/
void Graph::printGraph() {
	std::list<Vertex>::const_iterator it;
	std::list<ENode>::const_iterator eit;
	for (it = _graph-> begin(); it != _graph-> end(); it++) {
		std::cout <<"Vertex: " <<  it-> iD << std::endl;
		for (eit = it-> adj_list-> begin(); eit != it-> adj_list-> end(); eit++) {
			std::cout << "\t" <<"Edge: " << eit-> adj_iD << " Cost: " << eit-> edgeCost << std::endl;
		}
	}
}



/*********************************************************************

			printGraph2()
			
*********************************************************************/
void Graph::printGraph2() {
	std::list<Vertex>::const_iterator it;
	for (it = _graph-> begin(); it != _graph-> end(); it++) {
		std::cout <<"Vertex: " <<  it-> iD << " dv is " << it-> dv;
		if (it-> prev != NULL)
			std::cout << " pred is " << it-> prev-> iD <<std::endl;
		else if (!it-> prev)
			std::cout << " pred is NULL " << std:: endl; 
	}
}



/*****************************************************************

       			        getPaths()

*****************************************************************/

void Graph::getPaths(Vertex *v, std::ofstream &outfile, std::list<std::string> &path, bool &b) {
	std::list<std::string>::const_iterator it;
	if (!(v-> prev)) {
		path.push_front(v-> iD);
		//path.push_front(" THE END ");
		//outfile << "  going to print path  "; 
		
		for (it = path.begin(); it != path.end(); it++) 
			outfile << *it;
		path.clear(); 
		b = false;
		return;
	}
	
	while (v->prev != NULL) {
		if (!b)
			break;
		//outfile << "  ***  "; 
		path.push_front(v-> iD);
		path.push_front(", ");
		v = v-> prev;
		getPaths(v, outfile, path, b);
	}	
}

/*******************************************************************

			printshortestPaths()

********************************************************************/

void Graph::printshortestPaths (std::ofstream &outfile) {

	std::list<Vertex>::const_iterator it;
	std::list<std::string> path;
	
	for (it = _graph-> begin(); it != _graph-> end(); it++) {
		outfile << it-> iD << ": ";
		if (!it-> known)
			outfile << "NO PATH" << std::endl;
		else {
			bool b = true;
			outfile << it-> dv << " [";
			path.push_front("]");
			getPaths (static_cast <Vertex *> (lookupTable-> getPointer(it-> iD)), outfile, path, b); 
			outfile << std::endl;
			//outfile << " finished this vertex --- moving to next vertex "<<std::endl;
		}   
	}
}
