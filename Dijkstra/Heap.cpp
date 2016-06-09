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


/************************************************************************


			       heap()

************************************************************************/
heap::heap (int Capacity) {
	capacity = Capacity;
	try {
		data.resize(capacity + 1);
		mapping = new hashTable(capacity * 2);
	}
	catch (std::bad_alloc& ba) {
		std::cerr << "Error: " << ba.what() << std::endl;
		exit(1);
	}
	filled = 0;
}
/************************************************************************


			       insert()

************************************************************************/
int heap::insert (const std::string& id, int key, void* pv) {
	//heap is full
	if (filled == capacity)
		return 1;
	if (mapping->contains(id))
		return 2;

	int i = ++filled;
	data[i].id = id;
	data[i].key = key;
	if (pv) {
		data[i].pData = pv;
		//std::cout << std:: endl << "The address of s is : " << pv << std::endl;
	}
	mapping->insert(id, &data[i]);
	percolateUp(i, key);
	return 0;

}

/************************************************************************


			       setKey()

************************************************************************/
int heap::setKey (const std::string& id, int key) {
	bool b;
	Node *pNode = static_cast <Node *> (mapping->getPointer(id, &b));
	if (b == false ||pNode == NULL)
		return 1;
	int i = getPos(pNode);
	if (pNode->key < key) {
		data[i].key = key;
		data[0] = data[i];
		percolateDown(i);
	}
	else if (pNode->key > key) {
		data[i].key = key;
		data[0] = data[i];
		percolateUp(i, key);
	}
	return 0;
}


/************************************************************************


			    deleteMin()

************************************************************************/
int heap::deleteMin(std::string* pId, int* pKey, void* ppData) {
 //   std::cout << "DeleteMin() was called" << std::endl;
	if (filled == 0) {
		return 1;
	}
	if (pId != NULL) {
        *pId = data[1].id;
	}
	if (pKey != NULL) {
        *pKey = data[1].key;
	}
	if (ppData != NULL) {
		*(static_cast <void **> (ppData)) = data[1].pData;
	}
	mapping-> remove(data[1].id);
	data[1] = data[filled--];
	percolateDown(1);

	//std::cout << "The address of v is :" << ppData << std::endl;
	return 0;
}

/************************************************************************


			       remove()

************************************************************************/
int heap::remove (const std::string& id, int* pKey, void* ppData) {
	bool b;
	Node *pNode = static_cast <Node *> (mapping->getPointer(id, &b));
	if (!pNode)
		return 1;
	int i = getPos(pNode);
	std::string* pId;
	*pKey = data[i].key;
	this-> setKey(id, data[1].key - 1);
	this-> deleteMin(NULL, NULL, ppData);
	return 0;

}

/************************************************************************


			   percolateUp()

************************************************************************/
void heap::percolateUp (int i, int key) {
	data[0] = data[i];
	for( ; i > 1 && key <= data[i/2].key; i /= 2) {
   	data[i] = data[i/2];
   	mapping-> setPointer(data[i].id, &data[i]);
   }
   data[i] = data[0];
   mapping-> setPointer(data[i].id, &data[i]);
}
/************************************************************************


			  percolateDown()

************************************************************************/
void heap::percolateDown (int i) {
	int child;
	data[0] = data[i];
	for ( ; i * 2 <= filled; i = child) {
		child = i * 2;
		if (child != filled)
			if (data[child +1].key < data[child].key)
				child++;
		if (data[i].key > data[child].key) {
			data[i] = data[child];
			data[child] = data[0];
			mapping-> setPointer(data[i].id, &data[i]);
		}
		else
			break;
	}
	data[i] = data[0];
	mapping-> setPointer(data[i].id, &data[i]);
	return;
}

/************************************************************************


			     getPos()

************************************************************************/
int heap::getPos (Node* pNode) {
	int pos = pNode - &data[0];
	return pos;
}

