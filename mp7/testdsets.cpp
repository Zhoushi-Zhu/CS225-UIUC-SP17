/**
 * @file testdsets.cpp
 * Performs basic tests of DisjointSets.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"

using std::cout;
using std::endl;

int main()
{
    DisjointSets s;

    s.addelements(50);
    cout<<"1"<<endl;
    s.setunion(2, 3);
    cout<<"2"<<endl;
    s.setunion(3, 5);
    cout<<"3"<<endl;
    s.setunion(5, 7);
    cout<<"4"<<endl;
    s.setunion(7, 2);
    cout<<"5"<<endl;
    s.setunion(4, 6);
    cout<<"6"<<endl;
    cout<<"122``````````````````"<<endl;

    for(size_t i = 0; i < s.table.size(); i++)
        cout<<s.table[i]<<endl;



    //cout << s.find(7) << endl;
    //cout << s.find(5) << endl;
    cout << s.find(6) << endl;

    s.addelements(1);

    cout << s.find(50) << endl;

    s.setunion(50, 3);

    cout << s.find(50) << endl;
    cout << "Disjoint Sets test complete" << endl;

    return 0;
}
