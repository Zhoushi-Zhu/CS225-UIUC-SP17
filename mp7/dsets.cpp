/* Your code here! */
#include "dsets.h"
#include <iostream>
#include <vector>

using namespace std;

int DisjointSets::find(int elem){
	//if(table.empty() || elem < 0 || elem >= table.size())
		//return -1;

	if(table[elem] < 0)
		return elem;
	else
		return find(table[elem]);
}

void DisjointSets::setunion(int a, int b){
	int root1 = find(a);
	int root2 = find(b);

	int newSize = table[root1] + table[root2];
	if(table[root1] <= table[root2]){
		table[root2] = root1;
		table[root1] = newSize;
	}else{
		table[root1] = root2;
		table[root2] = newSize;
	}
}

void DisjointSets::addelements(int num){
	for(int i = 0; i < num; i++){
		table.push_back(-1);
	}
}




