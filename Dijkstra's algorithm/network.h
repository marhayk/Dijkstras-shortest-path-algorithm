#pragma once

#include<iostream>
#include <string>
#include <fstream>
#include <thread>

using namespace std;

struct connectionNode;

struct cityNode
{
	string cityName;
	int cityIndex;
	connectionNode *nextConnection;
	cityNode *nextCity;
};

struct connectionNode
{
	int dist;
	int time;
	connectionNode *connection;
	cityNode *destCity;
};

struct dikstrasNode
{
	int distance_time;
	bool include;
	int path;
	cityNode *pathCity;
	cityNode *city; // city pointer with minimum distance
};

class network
{
private:
	cityNode *myCities;
	int count = 0;
	cityNode *lastCityAdded;

	int getIndex(string cityName)
	{
		cityNode *trav = myCities;
		bool found = false;
		for (int x = 0; x < count; x++)
		{

			if (trav->cityName == cityName)
			{
				return x;
			}
			trav = trav->nextCity;
		}
		if (!found)
		{
			return count - 1;
		}
	}
public:
	network()
	{
		myCities = new cityNode;
		myCities->nextCity = NULL;
		lastCityAdded = myCities;
		ifstream cityFile;
		cityFile.open("cities.txt");
		string tempCityName = "";

		while (!cityFile.eof())
		{
			getline(cityFile, tempCityName);

			cityNode *travCity = lastCityAdded;
			while (travCity->nextCity != NULL)
			{
				travCity = travCity->nextCity;
			}

			travCity->nextCity = new cityNode;
			travCity->nextCity->cityName = tempCityName;
			travCity->nextCity->cityIndex = count;
			travCity->nextCity->nextCity = NULL;
			travCity->nextCity->nextConnection = NULL;
			lastCityAdded = travCity;
			count++;
		}
		myCities = myCities->nextCity;

		ifstream connectionFile;
		connectionFile.open("connections.txt");
		string tempConnName = "";
		while (!connectionFile.eof())
		{
			getline(connectionFile, tempConnName);
			string tempSource = "";
			string tempDest = "";
			int tempDistance = 0;
			int tempTime = 0;
			string temp = "";
			int tempTurn = 0;
			for (int x = 0; x < tempConnName.length(); x++)
			{
				if (tempConnName[x] != '\t')
				{
					temp += tempConnName[x];
				}
				else
				{
					if (tempTurn == 0)
					{
						tempSource = temp;
					}
					else if (tempTurn == 1)
					{
						tempDest = temp;
					}
					else if (tempTurn == 2)
					{
						tempDistance = stoi(temp);
					}
					temp = "";
					tempTurn++;
				}
			}
			tempTime = stoi(temp);

			cityNode *trav = myCities;
			bool sourceFound = false;
			bool destFound = false;
			cityNode *source = NULL;
			cityNode *dest = NULL;
			for (int x = 0; x <= count; x++)
			{
				if (sourceFound && destFound)
				{
					if (source->nextConnection == NULL)
					{
						source->nextConnection = new connectionNode;
						source->nextConnection->dist = tempDistance;
						source->nextConnection->time = tempTime;
						source->nextConnection->destCity = dest;
						source->nextConnection->connection = NULL;
					}
					else
					{
						connectionNode *travConn = source->nextConnection;
						while (travConn->connection != NULL)
						{
							travConn = travConn->connection;
						}
						travConn->connection = new connectionNode;
						travConn->connection->dist = tempDistance;
						travConn->connection->time = tempTime;
						travConn->connection->destCity = dest;
						travConn->connection->connection = NULL;
					}
					break;
				}
				if (x < count)
				{
					if (trav->cityName == tempSource)
					{
						source = trav;
						sourceFound = true;
					}
					else if (trav->cityName == tempDest)
					{
						dest = trav;
						destFound = true;
					}
					trav = trav->nextCity;
				}
			}
		}
		cityFile.close();
		connectionFile.close();
	}

	void addCity(string name)
	{
		cityNode *travCity = lastCityAdded;
		while (travCity->nextCity != NULL)
		{
			travCity = travCity->nextCity;
		}

		travCity->nextCity = new cityNode;
		travCity->nextCity->cityName = name;
		travCity->nextCity->cityIndex = count;
		travCity->nextCity->nextCity = NULL;
		travCity->nextCity->nextConnection = NULL;
		lastCityAdded = travCity;
		count++;
	}

	void addConnection(string sourceName, string destName, int distance, int time)
	{
		cityNode *trav = myCities;
		bool sourceFound = false;
		bool destFound = false;
		cityNode *source = NULL;
		cityNode *dest = NULL;
		for (int x = 0; x <= count; x++)
		{
			if (sourceFound && destFound)
			{
				if (source->nextConnection == NULL)
				{
					source->nextConnection = new connectionNode;
					source->nextConnection->dist = distance;
					source->nextConnection->time = time;
					source->nextConnection->destCity = dest;
					source->nextConnection->connection = NULL;
				}
				else
				{
					connectionNode *travConn = source->nextConnection;
					while (travConn->connection != NULL)
					{
						travConn = travConn->connection;
					}
					travConn->connection = new connectionNode;
					travConn->connection->dist = distance;
					travConn->connection->time = time;
					travConn->connection->destCity = dest;
					travConn->connection->connection = NULL;
				}
				break;
			}
			if (x < count)
			{
				if (trav->cityName == sourceName)
				{
					source = trav;
					sourceFound = true;
				}
				else if (trav->cityName == destName)
				{
					dest = trav;
					destFound = true;
				}
				trav = trav->nextCity;
			}
		}

	}

	void shortestDistance(string sourceName, string destName)
	{
		int sourceIndex = 0;
		int destIndex = 0;
		int currentIndex = 0;
		bool sourceFound = false;
		bool destFound = false;
		cityNode *sourceCity = NULL;
		cityNode *destCity = NULL;
		cityNode *currentCity = NULL;

		//get the source and destination indexes
		cityNode *trav = myCities;
		for (int x = 0; x <= count; x++)
		{
			if (sourceFound && destFound)
			{
				break;
			}
			if (x < count)
			{
				if (trav->cityName == sourceName)
				{
					sourceIndex = trav->cityIndex;
					sourceCity = trav;
					sourceFound = true;
				}
				if (trav->cityName == destName)
				{
					destIndex = trav->cityIndex;
					destCity = trav;
					destFound = true;
				}
				trav = trav->nextCity;
			}
		}

		//create and populate the dikstra's array
		dikstrasNode **diksArr;
		diksArr = new dikstrasNode*[count];
		for (int x = 0; x < count; x++)
		{
			diksArr[x] = new dikstrasNode;
			if (x == sourceIndex)
			{
				diksArr[x]->distance_time = 0;
				diksArr[x]->include = true;
			}
			else
			{
				diksArr[x]->distance_time = 100000;
				diksArr[x]->include = false;
			}
			diksArr[x]->path = sourceIndex;
		}

		//finding shortest path
		currentIndex = sourceIndex;
		currentCity = sourceCity;
		for (int x = 0; x < count; x++)
		{
			connectionNode *travConn = currentCity->nextConnection;
			int minDist = 100000;
			int minIndex = 0;
			while (travConn != NULL)
			{
				int index = travConn->destCity->cityIndex;
				if (travConn->dist + diksArr[currentIndex]->distance_time < diksArr[index]->distance_time)
				{
					diksArr[index]->distance_time = travConn->dist + diksArr[currentIndex]->distance_time;
					diksArr[index]->path = currentIndex;
					diksArr[index]->pathCity = currentCity;
					diksArr[index]->city = travConn->destCity;
				}
				travConn = travConn->connection;
			}
			for (int y = 0; y < count; y++)
			{
				if (diksArr[y]->include == false)
				{
					if (diksArr[y]->distance_time < minDist)
					{
						minDist = diksArr[y]->distance_time;
						minIndex = y;
					}
				}
			}
			diksArr[minIndex]->include = true;
			currentIndex = minIndex;
			currentCity = diksArr[minIndex]->city;

			// shortest path found. Break out of the loop
			if (diksArr[destIndex]->include == true)
			{
				cout << "shortest path from " << sourceName << " to " << destName << " is " << diksArr[destIndex]->distance_time << endl;
				cout << "the path is " << destName << "<--";
				cityNode *pathTrav = diksArr[destIndex]->pathCity;
				while (pathTrav != sourceCity)
				{
					cout << pathTrav->cityName << "<--";
					int prevIndex = pathTrav->cityIndex;
					pathTrav = diksArr[prevIndex]->pathCity;
				}
				cout << sourceName << endl;
				break;
			}
		}
	}

	void shortestTime(string sourceName, string destName)
	{
		int sourceIndex = 0;
		int destIndex = 0;
		int currentIndex = 0;
		bool sourceFound = false;
		bool destFound = false;
		cityNode *sourceCity = NULL;
		cityNode *destCity = NULL;
		cityNode *currentCity = NULL;

		//get the source and destination indexes
		cityNode *trav = myCities;
		for (int x = 0; x <= count; x++)
		{
			if (sourceFound && destFound)
			{
				break;
			}
			if (x < count)
			{
				if (trav->cityName == sourceName)
				{
					sourceIndex = trav->cityIndex;
					sourceCity = trav;
					sourceFound = true;
				}
				if (trav->cityName == destName)
				{
					destIndex = trav->cityIndex;
					destCity = trav;
					destFound = true;
				}
				trav = trav->nextCity;
			}
		}

		//create and populate the dikstra's array
		dikstrasNode **diksArr;
		diksArr = new dikstrasNode*[count];
		for (int x = 0; x < count; x++)
		{
			diksArr[x] = new dikstrasNode;
			if (x == sourceIndex)
			{
				diksArr[x]->distance_time = 0;
				diksArr[x]->include = true;
			}
			else
			{
				diksArr[x]->distance_time = 100000;
				diksArr[x]->include = false;
			}
			diksArr[x]->path = sourceIndex;
		}

		//finding shortest path
		currentIndex = sourceIndex;
		currentCity = sourceCity;
		for (int x = 0; x < count; x++)
		{
			connectionNode *travConn = currentCity->nextConnection;
			int minTime = 100000;
			int minIndex = 0;
			while (travConn != NULL)
			{
				int index = travConn->destCity->cityIndex;
				if (travConn->time + diksArr[currentIndex]->distance_time < diksArr[index]->distance_time)
				{
					diksArr[index]->distance_time = travConn->time + diksArr[currentIndex]->distance_time;
					diksArr[index]->path = currentIndex;
					diksArr[index]->pathCity = currentCity;
					diksArr[index]->city = travConn->destCity;
				}
				travConn = travConn->connection;
			}
			for (int y = 0; y < count; y++)
			{
				if (diksArr[y]->include == false)
				{
					if (diksArr[y]->distance_time < minTime)
					{
						minTime = diksArr[y]->distance_time;
						minIndex = y;
					}
				}
			}
			diksArr[minIndex]->include = true;
			currentIndex = minIndex;
			currentCity = diksArr[minIndex]->city;

			// shortest path found. Break out of the loop
			if (diksArr[destIndex]->include == true)
			{
				cout << "shortest time from " << sourceName << " to " << destName << " is " << diksArr[destIndex]->distance_time << endl;
				cout << "the time path is " << destName << "<--";
				cityNode *pathTrav = diksArr[destIndex]->pathCity;
				while (pathTrav != sourceCity)
				{
					cout << pathTrav->cityName << "<--";
					int prevIndex = pathTrav->cityIndex;
					pathTrav = diksArr[prevIndex]->pathCity;
				}
				cout << sourceName << endl;
				break;
			}
		}
	}


	void findBoth(string sourceName, string destName)
	{
		thread first(&network::shortestDistance, *this, sourceName, destName);
		thread second(&network::shortestTime, *this, sourceName, destName);
		first.join();
		second.join();
	}


	void checkCities()
	{
		cityNode *trav = myCities;
		while (trav != NULL)
		{
			cout << trav->cityIndex << ") " << trav->cityName << endl;
			trav = trav->nextCity;
		}
	}

	void checkConn()
	{
		cityNode *trav = myCities;
		while (trav != NULL)
		{
			cout << trav->cityName << "--->";
			connectionNode *travConn = trav->nextConnection;
			while (travConn != NULL)
			{
				cout << travConn->destCity->cityName << " (" << travConn->dist << ", " << travConn->time << "), ";
				travConn = travConn->connection;
			}
			cout << endl;
			trav = trav->nextCity;
		}
	}

};