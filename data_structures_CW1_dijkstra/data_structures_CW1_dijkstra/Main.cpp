// Program to find Dijkstra's shortest path using priority_queue in STL 
#include <utility>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

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

//Map represented as edges between vertices.
class Graph
{
private:
	int vertex_count; // Number of vertices 

	//Adjacent vertices for each vertex in the graph.
	vector<list<Path>> adjacent;

public:
	Graph(int vertex_count);

	//Add an edge to the graph.
	void add_edge(int u, int v, int w);

	//Find shortest path from source to dest.
	void find_path(int source, int dest) const;
};

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

//Comparator to sort paths by distance in priority queue.
class Compare
{
public:
	bool operator() (Path a, Path b) const
	{
		return a.distance > b.distance;
	}
};

//Find shortest path from source to dest.
void Graph::find_path(int source, int dest) const
{
	//Priority queue to store possible paths and sort them by distance.
	priority_queue<Path, vector<Path>, Compare> queue;

	//Create and initialize vector of distances.
	vector<int> dist(vertex_count, INT_MAX);

	const int NO_PATH = -1;
	//Previous vertices in best path.
	vector<int> back_path(vertex_count, NO_PATH);

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
		stack<int> way;
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
