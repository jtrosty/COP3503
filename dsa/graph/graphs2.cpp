#include<vector>
#include<stack>
#include<set>
#include<iostream>

using std::vector;
using std::stack;
using std::set;
using std::cout;
using std::endl;
/*
struct Edge 
{
	int src, dest;
	Edge(int _src, int _dest) {src = _src; dest = _dest;}
};

class Graph 
{
  public:
	int numVertices;
	vector< vector<int> > adjList;  // adjacency list

	Graph(const vector<Edge>& edges, int vertices) {
		numVertices = vertices;

		adjList.resize(vertices);

		for (auto &edge : edges) {
			adjList[edge.src].push_back(edge.dest);
		}
	}
};
*/
struct Edge {
	int src, dest;
	Edge(int _src, int _dest) {src = _src; dest = _dest;}
};

class Graph {
public:
	int numVertices;
	vector<vector<int>> adjList;

	Graph(const vector<Edge>& edges, int vertices) {
		numVertices = vertices;

		adjList.resize(vertices);

		for (auto &edge : edges) {
			adjList[edge.src].push_back(edge.dest);
			adjList[edge.dest].push_back(edge.src);
		}
	}
};
//////////////////////////////////////////////////////////////
//               Depth first search
bool dfs(const Graph& graph, int src, int dest) {
    stack<int> s;
    set<int> visited; 

    s.push(src);

    visited.insert(src);
    vector<int> temp = {0};
    vector<int> prev; 

    while(!s.empty()) {
        int top = s.top();
        if (top == dest) return true;
        s.pop();
        temp = graph.adjList.at(top);
        
        for (int i = 0; i < temp.size(); i++) {
            if (visited.count(temp.at(i)) == 0) {
                visited.insert(temp.at(i));
                s.push(temp.at(i));
            }
        }
    }
    return false;
}
//////////////////////////////////////////////////////////////
//                7.3.1 Detect cycle in undirected graph
bool cycleHelper(const Graph& graph, int src) {
    stack<int> s;
    set<int> visited; 
    int* parent =  new int[graph.numVertices];
    for (int i = 0; i < graph.numVertices; i++) parent[i] = -1;

    s.push(src);

    visited.insert(src);
    vector<int> temp = {0};
    int prev = -1;

    while(!s.empty()) {
        int top = s.top();
        s.pop();
        temp = graph.adjList.at(top);
        
        for (int i = 0; i < temp.size(); i++) {
            if (visited.count(temp.at(i)) == 0 && temp.at(i) != prev) {
                visited.insert(temp.at(i));
                if (parent[temp.at(i)] == -1) parent[temp.at(i)] = top;
                s.push(temp.at(i));
            }
            else  {
                if ((visited.count(top)) && parent[top] != temp.at(i) ) return true;
            }
        }
        prev = top;
    }
    return false;
}
bool anyCycle(const Graph& graph) {
    // your code
    bool result = false;
    int size = graph.adjList.size();
    for (int i = 0; i < size; i++) {
        result = cycleHelper(graph, i);
        if (result) return true;
    }
    return false;
}






int main(void) {
    vector<Edge> edges;
    edges.push_back(Edge(0, 1));
    edges.push_back(Edge(0, 2));
    edges.push_back(Edge(1, 2));
    edges.push_back(Edge(2, 6));
    edges.push_back(Edge(1, 3));
    edges.push_back(Edge(3, 4));
    edges.push_back(Edge(3, 5));
    edges.push_back(Edge(4, 7));


    Graph* testGraph = new Graph(edges, 8);
    if (anyCycle(*testGraph)) cout << "contains cycle" << endl;
    else cout << " no cycle" << endl;
}