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

using namespace std;

/**********************************************************************

			MAIN FUNCTION


**********************************************************************/


void openinFile (std::ifstream& infile) {
	std::string filename;
	std::cin >> filename;
	infile.open(filename.c_str());
	if (!infile) {
		std::cerr << "ERROR: could not open " << filename << std::endl;
		exit (1);
	}
}

void openoutFile(std::ofstream& outfile) {
	std::string filename;
	std::cin >> filename;
	outfile.open(filename.c_str());
	if (!outfile) {
		std::cerr << "ERROR: could not open " << filename << std::endl;
		exit(1);
	}
}

void loadGraph (ifstream& infile, Graph& graph) {
	string v1, v2;
	int edgeCost;
	while (infile >> v1 >> v2 >> edgeCost) {
		graph.insert(v1, v2, edgeCost);
	}
}


void getStartVertex (Graph& graph, string& s) {
	bool goodInput = false;
	while (!goodInput) {
		goodInput = true;
		cin >> s;

		if (!graph.vertexExists(s)) {
			cout << "That vertex does not exist! Try again " << endl;
			cin.clear();
			goodInput = false;
		}
		while (cin.get() != '\n');
	}
}



int main (int argc, char* argv[]) {

	ifstream infile;
	ofstream outfile, outfile2;
	Graph graph;
	string s;
	//string WAIT;

	cout << "Enter name of graph file: ";
	openinFile (infile);

	/*load the graph*/
	loadGraph (infile, graph);
	//graph.printGraph();

	cout << "Enter a valid vertex id for the starting vertex: ";

	getStartVertex(graph, s);

	graph.initializeHeap();

	clock_t t1 = clock();
	//std::cout << "Enter name of output file 2" << std::endl;
	//openoutFile (outfile2);
	
	graph.Dijkstra(s/*, outfile2*/);
	clock_t t2 = clock();
	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to apply Dijstra's algorithim: " << timeDiff << endl;

	//graph.printGraph2();

	std::cout << "Enter name of output file" << std::endl;
	openoutFile (outfile);
	graph.printshortestPaths (outfile);

	//cin >> WAIT;
	return 0;
}

