// Dijkstra's algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "network.h"

using namespace std;

int main()
{
	network n1;
	/*n1.addCity("A");
	n1.addCity("B");
	n1.addCity("C");
	n1.addCity("D");
	n1.addCity("E");
	n1.addCity("F");
	n1.addCity("G");
	n1.addConnection("A", "B", 10, 0);
	n1.addConnection("B", "A", 10, 0);
	n1.addConnection("A", "D", 20, 0);
	n1.addConnection("D", "A", 20, 0);
	n1.addConnection("A", "G", 15, 0);
	n1.addConnection("G", "A", 15, 0);
	n1.addConnection("B", "E", 1, 0);
	n1.addConnection("E", "B", 1, 0);
	n1.addConnection("G", "C", 3, 0);
	n1.addConnection("C", "G", 3, 0);
	n1.addConnection("E", "C", 13, 0);
	n1.addConnection("C", "E", 13, 0);
	n1.addConnection("E", "F", 17, 0);
	n1.addConnection("F", "E", 17, 0);
	n1.addConnection("F", "D", 2, 0);
	n1.addConnection("D", "F", 2, 0);*/
	//cout << "before" << endl;
	//n1.checkConn();
	//n1.checkCities();
	//n1.shortestDistance("Rugby", "Fargo");
	//n1.shortestTime("Rugby", "Fargo");
	//n1.findBoth("Rugby", "Fargo");
	n1.shortestDistance("Rugby", "Fargo");
	//cout << endl << endl;
	//n1.addCity("Dickinson");
	//n1.addConnection("Dickinson", "Williston", 131, 131);
	//n1.addConnection("Williston", "Dickinson", 131, 131);
	//cout << "after" << endl;
	//n1.checkCities();
	//n1.checkConn();
	system("pause");
	return 0;
}

