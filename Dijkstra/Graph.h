#ifndef	_GRAPH_H
#define _GRAPH_H

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

/**********************************************************************

			GRAPH CLASS


**********************************************************************/

class Graph {
	private:

	class ENode {
		public:
		std::string adj_iD;
		int edgeCost;
		ENode (std::string id, int cost) : adj_iD(id), edgeCost(cost) {}
	};

	class Vertex {
		public:
		std::string iD;
		int dv;
		bool known;
		Vertex *prev;
		std::list <ENode> *adj_list;
		Vertex (std::string iD);
	};

	int nVerticies;
	int nEdges;

   	void getPaths(Vertex *v, std::ofstream &outfile, std::list<std::string> &path, bool &b);
	bool unknownVertex_Exists ();
	std::list <Vertex> *_graph;
	hashTable *lookupTable;
	heap *g_heap;

	public:
	Graph ();
	int insert (std::string& iD, std::string& adj_iD, int& cost);
	void initializeHeap();
	int Dijkstra (std::string s/*, std::ofstream &outfile2*/);
	bool vertexExists (const std::string& iD);
	void printshortestPaths (std::ofstream &outfile);
	void printGraph ();
	void printGraph2 ();
	void checkvertexPointer (Vertex *pV);
};

#endif
