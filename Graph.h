#pragma once
#include <iostream>
#include <list>
#define V 1000 // # of vertices
using namespace std;

class Graph
{
private:
	list<int> adjLists[V];
	bool visited[V];
	int distance[V];

public:
	Graph();
	~Graph();
	int GetDegree(int);
	int GetDistance(int);
	bool GetVisited(int);
	void addEdge(int src, int dest);
	void BFS(int startVertex);
};