#ifndef	_HEAP_H
#define _HEAP_H

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


/*********************************************************************

			HEAP CLASS


*********************************************************************/

class heap {
	public:
	heap (int capacity);
	int insert (const std::string &id, int key, void *pv = NULL);
	int setKey (const std::string &id, int key);
	int deleteMin (std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);
	int remove (const std::string &id, int *pKey = NULL, void *ppData = NULL);

	private:
	class Node {
		public:
		std::string id;
		int key;
		void *pData;
	};

	int capacity;
	int filled;
	hashTable *mapping;
	std::vector<Node> data;
	void percolateUp (int posCur, int key);
	void percolateDown (int posCur);
	int getPos (Node *pn);
};

#endif

