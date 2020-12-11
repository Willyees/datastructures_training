#include "graph.h"
#include <vector>
#include <assert.h>
#include <stack>
using namespace std;

Graph::Graph(int n, bool directed) : _n(n), _directed(directed) {
	_vertices = new VertexList[n];
}

Graph::Graph(int n) : _n(n), _directed(false) {
	_vertices = new VertexList[n];
}

Graph::~Graph() {
	delete[] _vertices;
}

bool Graph::directed() {
	return _directed;
}

int Graph::numVertices() {
	return _n;
}
bool Graph::isEdge(int u, int v) {
	if (_vertices[u].size()) {
		int i;
		i = begin(u)->first;
		assert("asd");
	}
	auto it_b = begin(u);
	auto it_e = end(u);
	for (auto it = begin(u); it != end(u); ++it) {
		if (it->first == v)
			return true;
	}
	return false;
}
bool Graph::isEdge(int u, int v, int weight) {
	for (auto it = begin(u); it != end(u); ++it) {
		if (it->first == v && it->second == weight)
			return true;
	}
	return false;
}

//returns weight of specific edge u->v
int Graph::edgeWeight(int u, int v) {
	assert(isEdge(u, v) && "edge u->v does not exists");
	for (auto it = begin(u); it != end(u); ++it) {
		if (it->first == v)
			return it->second;
	}
	return -1;

}
//add relation between vertex u and v (u->v)
void Graph::addEdge(int u, int v) {
	addEdge(u, v, 0);
}

void Graph::addEdge(int u, int v, int weight) {
	_vertices[u].push_back(std::make_pair(v, weight));
}

bool Graph::removeEdge(int u, int v) {

	for (auto it = begin(u); it != end(u); ++it) {
		if ((*it).first == v) {
			_vertices[u].erase(it);
			return true;
		}
	}
	return false;
}

VertexList::const_iterator Graph::begin(int u) {
	return _vertices[u].cbegin();
}

VertexList::const_iterator Graph::end(int u) {
	return _vertices[u].cend();
}


//Visit algorithms

//Best, average, worst: O(V + E)
void dfsVisit(Graph& g, int u, bool* seen, std::list<int>& pred) {
	if (seen[u])
		return;
	seen[u] = true;
	pred.push_back(u);
	for (auto it = g.begin(u); it != g.end(u); ++it) {
		int pos = it->first;
		if (!seen[pos])
			dfsVisit(g, pos, seen, pred);
	}
	//if using colours, should set there u as black
}

void deapthFirstSearch(Graph& g, int r, std::list<int>& q) {
	bool* seen = new bool[g.numVertices()]();//initialize the whole array to false
	q.resize(0);
	q.clear();
	//start from root and search every neighbours
	dfsVisit(g, r, seen, q);
	//in case graph has vertices that are isolated, search them as well
	for (int i = 0; i < g.numVertices(); ++i) {
		if (!seen[i])
			dfsVisit(g, i, seen, q);
	}
	delete[] seen;
}


//not recursive
void depthFirstSearchColours(Graph& g, int r, std::list<int>& q) {
	vertexColor* colours = new vertexColor[g.numVertices()]();
	std::stack<int> s;
	s.push(r);
	while (s.size() > 0) {
		int u = s.top();
		s.pop();
		if (colours[u] == White) {
			q.push_back(u);
			colours[u] = Grey;
			for (auto it = g.begin(u); it != g.end(u); ++it) {
				s.push(it->first);
			}
		}
	}
	//missing last part where it checks for possible whites left out because not connected to initial vertex
}




