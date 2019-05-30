// Program to find Dijkstra's shortest path using priority_queue in STL 
#include <utility>
#include <fstream>
#include <iostream>
#include <stack>
#include "Graph.h"
using namespace std;

int main()
{
	//Load input data from file.
	//File format:
	//vertex_count edge_count source_vertex, destination_vertex
	//edge_count lines with format: from to distance.
	//>>>
	ifstream input("input.txt");

	int vertex_count, edge_count, source, dest;
	input >> vertex_count >> edge_count >> source >> dest;

	//Create graph.
	Graph graph(vertex_count);

	//Read edges.
	for (int i = 0; i < edge_count; i++)
	{
		int from, to, distance;
		input >> from >> to >> distance;
		graph.add_edge(from, to, distance);
	}

	input.close();
	//<<<

	graph.find_path(source, dest);

	system("pause");

	return 0;
}
