#ifndef _HASH_H
#define _HASH_H

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


/*********************************************************************

			HASH TABLE CLASS


*********************************************************************/
class hashTable {
	public:
	hashTable(int size = 0);
	int insert(const std::string &key, void *pv = NULL);
	bool contains(const std::string &key);
	void *getPointer(const std::string &key, bool *b = NULL);
	int setPointer(const std::string &key, void *pv);
	bool remove(const std::string &key);

	private:
	class hashItem {
		public:
		std::string key;
		bool isOccupied;
		bool isDeleted;
		void *pv;
  };

	int capacity;
	int filled;
	std::vector<hashItem> data;
	int hash(const std::string &key);
	int findPos(const std::string &key);
	bool rehash();
	static unsigned int getPrime(int size);
};

#endif
