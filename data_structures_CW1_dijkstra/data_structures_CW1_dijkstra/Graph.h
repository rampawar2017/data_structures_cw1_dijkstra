#pragma once
#include <vector>
#include <list>
#include "Path.h"

//Map represented as edges between vertices.
class Graph
{
private:
	int vertex_count; // Number of vertices 

	//Adjacent vertices for each vertex in the graph.
	std::vector<std::list<Path>> adjacent;

public:
	Graph(int vertex_count);

	//Add an edge to the graph.
	void add_edge(int u, int v, int w);

	//Find shortest path from source to dest.
	void find_path(int source, int dest) const;
};