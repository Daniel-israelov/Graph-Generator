#include<iostream>
#include<stdlib.h>
#include<fstream>
#include"Graph.h"
#define P_CYCLE 500  //# of graphs for each probabilty
using namespace std;

Graph* build_random_graph(int, double);
int is_isolated(Graph*);
int connectivity(Graph*);
int diameter(Graph*);
void code_execution(double[], int);
void create_csv(int[], double[]);

/* Driver Code */
int main()
{ 
	srand((unsigned)time(NULL));
	double p1[10] = { 0.003,0.004,0.005,0.0055,0.006,0.007,0.0075,0.008,0.0085, 0.009 };	 //Probabilities vector for threshold1 --> ~0.00690
	double p2[10] = { 0.075,0.08,0.085,0.095,0.1,0.13,0.18,0.23,0.28,0.33 };		 //Probabilities vector for threshold2 --> ~0.11753
	double p3[10] = { 0.0048,0.0053,0.0058,0.0063,0.0068,0.0073,0.0078,0.0083,0.088,0.093 }; //Probabilities vector for threshold3 --> ~0.00690

	code_execution(p1, 1); //For Attribute 1 --> Connectivity
	code_execution(p2, 2); //For Attribute 2 --> Diameter
	code_execution(p3, 3); //For Attribute 3 --> Isolated Vertex
	
	return 0;
}

void code_execution(double p_arr[], int att_indx) //att_indx helps to identify which attribute needs to be checked.
{/*  This function executes all other functions needed to create random graphs  
	 and to check the Attributes.											     
	 At the end of this function there's a function call to create the csv file 
	 with all the calculations and the results. 	*/

	Graph* G;
	int i, attribute_v[10] = { 0 }; // attribute_v --> counts how many graphs are maintaining the current attribute

	for (i = 0; i < 10; i++)
	{
		for (int j{}; j < P_CYCLE; j++) 
		{
			G = build_random_graph(V, p_arr[i]); //Generating Random Graph

			if (att_indx == 1)  //For Attribute 1
				if (connectivity(G) == 1) 
					attribute_v[i]++;

			if (att_indx == 2) //For Attribute 2
				if (diameter(G) <= 2)	
					attribute_v[i]++;
				
			if (att_indx == 3) //For Attribute 3
				if (is_isolated(G) == 1)
					attribute_v[i]++;
			
			delete G;
		}
	}
	create_csv(attribute_v, p_arr);
	cout << "Attribute " << att_indx << " Complete." << endl;
}

void create_csv(int attribute_v[], double p_arr[])
{ /* Funtion to create a CSV file with the results of all Attributes.
	 All tables will be printed to the same single CSV file and will
	 be separated with an empty line and will be printed in blocks
	 in the following order:
	 1st block --> Attribute 1 - Connectivity.
	 2nd block --> Attribute 2 - Diameter.
	 3rd block --> Attribute 3 - Isolated vertex.		*/
	
	ofstream file;
	int i;

	file.open("results.csv", ios::app);

	file << "Probabilities:,";
	for (i = 0; i < 10; i++) //Printing the probabilities according to the threholds
		file << p_arr[i] << ",";

	file << endl;

	file << "Assessment of the probability that the feature exists:,";
	for (i = 0; i < 10; i++) //Printing the Assessment of the probability that the feature exists
		file << attribute_v[i] / 500.0 << ",";

	file << endl << endl;
	file.close();
}

int diameter(Graph* G)
{/* Here we use both BFS and the Distance array to find the diameter of a graph.
    We first run BFS from vertex 0 to check if the graph is connected, if not then
    there's no need to continue the BFS with other vertices.
    If the Graph is connected then we run BFS from each vertex in the graph.	 */

	int i, j, diam = -1;
	i = j = 0;

	G->BFS(0);
	for (i = 0; i < V; i++)
		if (G->GetVisited(i) == false)// Meaning that the graph isn't connected and there's no need to continue BFS on all other vertices.
			return diam;			  // -1 represent INFINITY diameter

	for (i; i < V; i++) //Getting the diam value from BFS(0)
		if (diam < G->GetDistance(i))
			diam = G->GetDistance(i); 

	for (i = 1; i < V; i++)
	{//Calling BFS on each node to get all the options & find the right daimeter 
		G->BFS(i); 
		for (j = 0; j < V; j++)
			if (diam < G->GetDistance(j))
				diam = G->GetDistance(j);
	}
	return diam;
}

int connectivity(Graph* G)
{/* Using BFS one time to check if theres a path from node '0' to all other nodes.
    If not --> the graph is not connected and will return 0,
	else - connected and will return 1.	*/

	G->BFS(0);
	for (int i{}; i < V; i++)
		if (G->GetVisited(i) == false)
			return 0;
	return 1;
}

int is_isolated(Graph* G)
{/*	Finding if there's at least 1 isolated vertex by checking the degrees of the vertices.
	As soon as we find a vertex with degree = 0 we know that there's at least 1 isolated
	vertex and the function will return 1, else - there are no isolated vertices and the
	function will return 0.		 */

	for (int i{}; i < V; i++)
		if (G->GetDegree(i) == 0) //If deg(v) = 0 --> that vertex is isolated
			return 1;
	return 0;
}

Graph* build_random_graph(int v, double p)
{/* Function that generates Random graph with 'v' vertices
	and adding edge with the probabilty of 'p'.	*/

	Graph* G = new Graph();
	int i = 0, j = 1;

	for (i; i < v; i++)
		for (j = i + 1; j < v; j++)
			if ((double)rand() / RAND_MAX <= p)
				G->addEdge(i, j); //Adding edge between 2 nodes in probability p

	return G;
}
