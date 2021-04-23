#include "Graph.h"
#include<iostream>
#include<list>

using namespace std;
Graph::Graph() 
{//Constructor
    for (int i{}; i < V; i++)
    {//Initializing all arrays
        adjLists->push_back(0);
        visited[i] = false;
        distance[i] = -1;
    }
}

Graph::~Graph() {}//Destructor

// Add edges to the graph
void Graph::addEdge(int x, int y) 
{//Connecting two vertices with undirected edge --> (x,y) = (y,x)
    adjLists[x].push_back(y);
    adjLists[y].push_back(x);
}

// BFS 
void Graph::BFS(int startVertex) 
{
    list<int> queue;

    /* Initializing the start vertex */
    visited[startVertex] = true;
    distance[startVertex] = 0;
    queue.push_back(startVertex);

    list<int>::iterator i;
    
    while (!queue.empty()) 
    {
        int currVertex = queue.front();
        queue.pop_front();

        for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i) 
        {
            int adjVertex = *i;
            if (!visited[adjVertex]) 
            {
                visited[adjVertex] = true;
                distance[adjVertex] = distance[currVertex] + 1;
                queue.push_back(adjVertex);
            }
        }
    }
}

bool Graph::GetVisited(int i)
{//If a vertex is visited it gets 'true' value, else 'false'
    if (visited[i] == true)
        return true;
    return false;
}

int Graph::GetDistance(int i)
{//return the distance between two vertices
    return distance[i];
}

int Graph::GetDegree(int i)
{//size of a list[i] is the degree of the 'i' vertex
    return adjLists[i].size();
}