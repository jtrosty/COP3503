#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>

using std::vector;
using std::pair;
using std::priority_queue;

vector<int> dijkstra(const Graph& graph, int src); 
bool finishCourses(int numCourses, vector<vector<int>> req); 

struct Edge {
	int src, dest, weight;
	Edge(int _src, int _dest, int _weight) {src = _src; dest = _dest; weight = _weight;}
};

class Graph {
public:
	int numVertices;
	vector<vector<pair<int, int>>> adjList; 
    // e.g. 0: {1, 12}, {2, 4} -> the weight from vertex 0 to 1 is 12 
    //                        and the weight from vertex 0 to 2 is 4

	Graph(const vector<Edge>& edges, int vertices) {
		numVertices = vertices;

		adjList.resize(vertices);

		for (auto &edge : edges) {
			adjList[edge.src].push_back(std::make_pair(edge.dest, edge.weight));
		}
	}
};

    /*
    int smallestOrder = 0;
    for (int i = 0; i < order.size(); i++) {
        if (order.at(i) < order.at(smallestOrder)) smallestOrder = i;
    }
    */
/*
void prim() {
    /* Input an undirected, connected, weighted graph g.
    output: T, a minium spanning tree for G.

    T := 0
    Pick any vertex in G and add it to T

    for j = 1 to n -1
        let C be the set of edges with one endpoint inside T and one endpoint outside T.
        Let e be a minimum weight edge in C.
        Add e to T
        Add the endpoint of e not already in T to T.
    end-for
}
    */

int main(void) {
    vector<vector<int>> req;
    req.resize(2);
    req[0] = {1, 0};
    req[1] = {0, 2};

    std::cout << "Finish classes: " << finishCourses(3, req) << std::endl;


    vector<Edge> edge;
    edge.push_back(Edge(0, 1, 4));
    edge.push_back(Edge(1, 2, 1));
    edge.push_back(Edge(2, 3, 8));
    edge.push_back(Edge(3, 4, 9));
    edge.push_back(Edge(3, 5, 5));
    edge.push_back(Edge(5, 4, 12));
    edge.push_back(Edge(6, 5, 7));
    edge.push_back(Edge(0, 6, 10));
    edge.push_back(Edge(1, 6, 2));
    edge.push_back(Edge(6, 2, 6));
    Graph testGraph(edge, 7);

    std::vector<int> result = dijkstra(testGraph, 0);
    for (int i = 0; i < 7; i++) {
        std::cout << i << " " << result.at(i) << std::endl;
    }

}

/////////////////////////////////////////////////////////////////////////////////
//                 Topological Sorting
bool finishCourses(int numCourses, vector<vector<int>> req) {

   // Code to make graph adj list
    vector< vector<int> > adjList;
    vector<int> sequence;
    std::queue<int> q;
    vector<int> order(numCourses, 0);
    int counter = 0;

    adjList.resize(numCourses);
    // Build an adjancy list
    for (auto v : req) {
        adjList.at(v.at(0)).push_back(v.at(1));
    }
    // Collect the order level
    for (int i =  0; i < req.size(); i++) 
        order.at(req.at(i).at(1))++;

    // If you order 0, add to the queue
    for (int i = 0; i < order.size(); i++) {
        if (order.at(i) == 0) q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for ( auto to : adjList.at(v)) {
            if (--order.at(to) == 0) 
                q.push(to);
        }
        sequence.push_back(v);
        counter++;
    }
    if (counter == numCourses) return true;
    else return false;
}

////////////////////////////////////////////////////////////////////////
//                       DIJKSTRA
vector<int> dijkstra(const Graph& graph, int src) {
    std::set<int> visited;
    int numVertices = graph.numVertices;
    std::vector<int> distanceArray(numVertices, INT_MAX);
    distanceArray.at(src) = 0;
    int smallestVertex = 0;

    while (visited.size() < numVertices) {
        // Set smallest vertex to an index that has not been visited
        for (int i = 0; i < numVertices; i++) {
            if (visited.count(i)) continue;
            smallestVertex = i; 
            break;
        }
        // Find smallest
        for (int i = 0; i < numVertices; i ++) {
            if (visited.count(i)) continue;
            if (distanceArray[i] < distanceArray[smallestVertex]) {
                smallestVertex = i;
            }
        }
        // Perform relaxation
        int size = graph.adjList.at(smallestVertex).size();
        auto vertex = graph.adjList.at(smallestVertex);
        for (int i = 0; i < size; i++ ) {
            if (distanceArray[smallestVertex] + vertex.at(i).second < distanceArray.at(vertex.at(i).first)) {
                distanceArray.at(vertex.at(i).first) = distanceArray[smallestVertex] + vertex.at(i).second;
            }
        }
        visited.insert(smallestVertex);
    }
    return distanceArray;
}