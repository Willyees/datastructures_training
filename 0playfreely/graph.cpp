#include "graph.h"
#include <vector>
#include <assert.h>
#include <stack>
#include <queue>

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
void dfsVisit(Graph& g, int u, bool* seen, std::vector<int>& visits, std::vector<int>& pred) {
	if (seen[u])
		return;
	seen[u] = true;
	visits.push_back(u);
	for (auto it = g.begin(u); it != g.end(u); ++it) {
		int pos = it->first;
		if (!seen[pos]){
			pred[pos] = u;
			dfsVisit(g, pos, seen, visits, pred);
		}
	}
	//if using colours, should set there u as black
}

void deapthFirstSearch(Graph& g, int r, std::vector<int>& visits, std::vector<int>& pred) {
	bool* seen = new bool[g.numVertices()]();//initialize the whole array to false
	visits.resize(0);
	visits.clear();
	pred.resize(g.numVertices());
	pred[r] = -1;// r has not any previous vertex in the traversal
	//start from root and search every neighbours
	dfsVisit(g, r, seen, visits, pred);
	//in case graph has vertices that are isolated, search them as well
	for (int i = 0; i < g.numVertices(); ++i) {
		if (!seen[i])
			dfsVisit(g, i, seen, visits, pred);
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
	delete[] colours;
	//missing last part where it checks for possible whites left out because not connected to initial vertex
}

void breadthFirstSearch(Graph& g, int r, std::vector<int>& l) {
	vertexColor* colours = new vertexColor[g.numVertices()]();//final () sets all the values to 
	std::queue<int> q;//used to store the next vertices to visit
	q.push(r);
	colours[r] = Grey;
	l.push_back(r);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto it = g.begin(u); it != g.end(u); ++it) {
			if (colours[it->first] == White) {
				l.push_back(it->first);
				colours[it->first] = Grey;
				q.push(it->first);
			}
		}
		colours[u] = Black;
	}
	delete[] colours;

}
typedef pair<int, int> PII;

//inqueue: status array updated whenver vertex is extrated from PQ
//key[]: records current priority key for each vertex in the PQ, eliminates the need to search the PQ for given vertex index
void mstPrim(Graph& g, std::vector<int>& pred) {
	int n = g.numVertices();
	pred.assign(n, -1);//resize pred with size n and values -1
	std::vector<int> key(n, numeric_limits<int>::max());//storing the weights at positions related to the index of the vertices
	key[0] = 0;
	priority_queue<PII, std::vector<PII>, greater<PII>> pq;
	vector<bool> inQueue(n, true);
	for (int i = 0; i < n; ++i) {
		pq.push(std::make_pair(key[i], 0));//PQ stores all the vertex in graph
	}
	while (!pq.empty()) {
		int u = pq.top().first;//get the index of smallest vertex
		pq.pop();
		inQueue[u] = false;//setting the index u not in the queue 

		//check if any neighbors of u have smaller edges
		for (auto it = g.begin(u); it != g.end(u); ++it) {
			int v = it->first;//index neighbor vertex
			if (inQueue[v]) {
				int w = it->second;
				if (w < key[v]) {//if weight less than v
					pred[v] = u;
					key[v] = w;
					//pq.decreaseKey() not implemented in stl 
				}
			}
		}
	}
}




