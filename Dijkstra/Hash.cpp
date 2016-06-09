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


/************************************************************************


			    hashTable()

************************************************************************/
hashTable::hashTable(int size) {
	capacity = getPrime(size);
	try{
		data.resize(capacity);
	}
	catch (std::bad_alloc& ba) {
		std::cerr << "Error: " <<  std::endl;
		exit(1);
	}
	filled = 0;
	for (int i = 0; i < capacity; i++) {
		data[i].key = "";
		data[i].isOccupied = false;
		data[i].isDeleted = false;
	}
}

/************************************************************************


			   insert()

************************************************************************/
int hashTable::insert(const std::string& key, void *pv) {
	int index;
	if (filled < (capacity / 2)) {
		index = hash(key);
		while (data[index].isOccupied) {
			if (data[index].key == key && !data[index].isDeleted)
				return 1;
			if (capacity - index == 1) {
				index = 0;
				continue;
			}
			index++;
		}
		data[index].key = key;
		data[index].isOccupied = true;
		data[index].isDeleted = false;
		if (pv != NULL)
			data[index].pv = pv;
		filled++;
		return 0;
	}
	if (filled >= (capacity / 2)) {
		if(this->rehash()) {
			this->insert(key, pv);
		}
		else
			return 2;
	}
}

/************************************************************************


			  contains()

************************************************************************/

bool hashTable::contains(const std::string& key) {
	if(findPos(key) > -1)
		return true;
	return false;
}


/************************************************************************


			   remove()

************************************************************************/

bool hashTable::remove(const std::string& key) {
	int found = findPos(key);
	if (found == -1)
		return false;
	data[found].isDeleted = true;
	return true;
}

/************************************************************************


			setPointer()

************************************************************************/
int hashTable::setPointer (const std::string &key, void *pv) {
	int found = findPos(key);
	if (found == -1)
		return 1;
	data[found].pv = pv;
	return 0;
}

/************************************************************************


			getPointer()

************************************************************************/
void* hashTable::getPointer (const std::string &key, bool *b) {
	int found = findPos(key);
	if (found == -1) {
		if (b != NULL)
	  		*b = false;
		return NULL;
	}
	if(b != NULL)
		*b = true;

	return data[found].pv;
}

/************************************************************************


			rehash()

************************************************************************/
bool hashTable::rehash() {
	int oldSize = capacity;
	capacity = getPrime(2*oldSize);
	int index;
	std::cout << capacity << std::endl;
	std::vector<hashItem> bigger(capacity);
	for (int i = 0; i < capacity; i++) {
		bigger[i].isOccupied = false;
	}
	filled = 0;
	for (int i = 0; i < oldSize; i++) {
		if(data[i].isOccupied && !(data[i].isDeleted)) {
			index = hash(data[i].key);
			while (bigger[index].isOccupied != false) {
				if (capacity - index == 1)
					index = 0;
				index ++;
			}
			bigger[index].key = data[i].key;
			bigger[index].isOccupied = true;
			bigger[index].isDeleted = false;
			bigger[index].pv = data[i].pv;
			filled++;
		}
	}
	try{
		data = bigger;
	}
	catch (std::bad_alloc& ba) {
		std::cerr << "Error: " << ba.what() << std::endl;
		return false;
	}
	return true;
}


/************************************************************************


			       hash()

************************************************************************/
int hashTable::hash(const std::string& key) {
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++)
		hashVal = 37*hashVal + key[i];
	hashVal %= capacity;
	if (hashVal < 0)
		hashVal += capacity;
	return hashVal;

}

/************************************************************************


			   findPos()

************************************************************************/
int hashTable::findPos(const std::string& key) {
	int index = hash(key);
	for (int i = 0; data[index].isOccupied; index++) {
		if (index == capacity)
			index = 0;
		if (data[index].key == key && !data[index].isDeleted)
			return index;
	}
	return -1;
}

/************************************************************************


			  getPrime()

************************************************************************/
unsigned int hashTable::getPrime(int size) {
	int primes[6] = {786433, 1572869, 3145739, 6291469, 12582917, 25165843};
	for (int i = 0; i < 6; i++) {
		if (primes[i] > size)
			return primes[i];
	}
	return 0;
}

