#pragma once

//Path from a vertex to next vertex.
//It is used as edge between vertices and as total path from a vertex to another vertex in graph.
struct Path
{
	int vertex; //next vertex
	int distance;

	Path(int vertex, int distance)
	{
		this->vertex = vertex;
		this->distance = distance;
	}
};