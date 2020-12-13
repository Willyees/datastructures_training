#include <list>
#include <vector>
enum vertexColor { White, Grey, Black };
enum edgeType { Tree, Backward, Forward, Cross };
typedef std::pair<int, int> Vertex;//pair<int vertex 'id', int weight>
typedef std::list<std::pair<int, int>> VertexList;

//linked list graph implementation
class Graph {
	VertexList* _vertices;//pointer to array of lists. all stored in the heap
	int _n;
	bool _directed;

public:
	//Graph(); no default constructor because the list of vertices is a static array, cannot be resized later on. need to add all the vertices when instantiated
	Graph(int n, bool directed);
	Graph(int n);
	~Graph();
	//void load(char* file);
	bool directed();
	int numVertices();
	bool isEdge(int u, int v);
	bool isEdge(int u, int v, int weight);
	int edgeWeight(int u, int v);
	void addEdge(int u, int v);
	void addEdge(int u, int v, int weight);
	bool removeEdge(int u, int v);
	VertexList::const_iterator begin(int u);
	VertexList::const_iterator end(int u);
};


void deapthFirstSearch(Graph& g, int r, std::vector<int>&, std::vector<int>&);//O(N+E)
void dfsVisit(Graph& g, int u, bool* seen, std::vector<int>&, std::vector<int>&);//O(N+E)

//not using recursion
void depthFirstSearchColours(Graph& g, int r, std::list<int>& q);//O(N+E)

void breadthFirstSearch(Graph& g, int r, std::vector<int>& q);//O(N + E)

void mstPrim(Graph& g, std::vector<int>& pred);