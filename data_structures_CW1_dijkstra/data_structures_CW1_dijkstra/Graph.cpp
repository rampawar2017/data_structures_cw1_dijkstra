#include "Graph.h"
#include <queue>
#include "Path.h"
#include <stack>
#include <iostream>
#include "Compare.h"

using namespace std;

Graph::Graph(int vertex_count)
{
	this->vertex_count = vertex_count;
	//Initialize empty list of edges for each vertex.
	adjacent.resize(vertex_count);
}

void Graph::add_edge(int u, int v, int w)
{
	//Graph is bidirectional so add edge from u to v and from v to u.
	adjacent[u].emplace_back(Path(v, w));
	adjacent[v].emplace_back(Path(u, w));
}

//Find shortest path from source to dest.
void Graph::find_path(int source, int dest) const
{
	//Priority queue to store possible paths and sort them by distance.
	std::priority_queue<Path, std::vector<Path>, Compare> queue;

	//Create and initialize vector of distances.
	std::vector<int> dist(vertex_count, INT_MAX);

	const int NO_PATH = -1;
	//Previous vertices in best path.
	std::vector<int> back_path(vertex_count, NO_PATH);

	//Insert source to queue and initialize its distance as 0. 
	queue.push(Path(source, 0));
	dist[source] = 0;

	//Repeat until all paths are checked.
	while (!queue.empty())
	{
		//Take first vertex from priority queue.
		const int v = queue.top().vertex;
		queue.pop();

		//Update distances for all adjacent vertices.
		for (auto path : adjacent[v])
		{
			// Get vertex label and distance of current adjacent of v. 
			const int u = path.vertex;
			const int distance = path.distance;

			//Check if there is a shorter path from v to u. 
			if (dist[u] > dist[v] + distance)
			{
				//Update distance for u.
				dist[u] = dist[v] + distance;
				back_path[u] = v;
				queue.push(Path(u, dist[u]));
			}
		}
	}

	//Check if any path was found.
	if (back_path[dest] == NO_PATH) {
		cout << "There is no path from " << source << " to " << dest << ".\n";
	}
	else
	{
		//Restore path in backward order and store it in stack.
		std::stack<int> way;
		for (auto vertex = dest; true; vertex = back_path[vertex])
		{
			way.push(vertex);
			if (back_path[vertex] == NO_PATH) break;
		}

		//Print path in forward order reading it from the stack.
		cout << "Shortest path from " << source << " to " << dest << ": ";
		while (!way.empty())
		{
			cout << way.top() << " ";
			way.pop();
		}
		cout << "\nDistance: " << dist[dest] << endl;
	}
}