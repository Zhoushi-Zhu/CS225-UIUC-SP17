/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <vector>
#include <cstdlib>
#include <iostream>


using namespace std;

class DisjointSets{
private: 
	
public:
	//dsets();
	//dsets(dsets other);

	int find(int elem);
	void addelements(int num);
	void setunion(int a, int b);
vector<int> table;

};

#endif