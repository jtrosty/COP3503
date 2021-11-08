#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

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

void bfs(const Graph& graph, int src) {
    std::queue<int> q;
    std::set<int> visited;
    std::vector<int> result;

    q.push(src);

    vector<int> temp;
    visited.insert(src);
    result.push_back(src);

    while(!q.empty()) {
        int top = q.front();
        q.pop();
        temp = graph.adjList.at(top);
        std::sort(temp.begin(), temp.end());
        for (int i = 0; i < temp.size(); i++) {
            if (visited.count(temp.at(i)) == 0) {
                visited.insert(temp.at(i));
                result.push_back(temp.at(i));
                q.push(temp.at(i));
            }
        }
    }
    /*
    for (auto iter = visited.begin(); iter != visited.end(); iter++) {
        if (iter == (visited.end()--)) cout << *iter;
        else cout << *iter << " ";
    }
    */
   for (int i = 0; i < result.size(); i++) {
       cout << result.at(i) << " ";
   }
}



int main (void) {
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
    bfs(*testGraph, 0);


}
