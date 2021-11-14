#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>

using std::vector;
using std::pair;
using std::priority_queue;

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

void topological() {
    /*
    Queue<vertex> q;
    int ocunter = 0;
    q.makeEmpty();
    for each Vertex v
        if (v.indegree == 0) 
            q.enqueue(v);
        while (!q.isEmpty()) {
            Vertext v = q.dequeue();
            v.topNum = ++counter; // assign next number
            for each Vertext w adjacent to v
                if ( --w.indegree == 0 )
                    q.enqueue( w );
        }
        if (counter != NUM_VERTICES) 
            throw CycleFoundException{};  ????
            
}

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
    */

}

vector<int> dijkstra(const Graph& graph, int src) {
    int MAXINT = 0x7fffffff;
    std::vector<int> distanceArray;
    std::set<int> visited;
    int numVertices = graph.numVertices;
    distanceArray.resize(numVertices);
    // PQ.add(source, 0)
    distanceArray.at(src) = 0;
    // Add to PQ the reamining vertices
    for (int i = 0; i < numVertices; i++) {
        if (i == src) continue;
        distanceArray.at(i) = MAXINT;
    }
    // For others PQ.add (v, infinity)
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
            if (distanceArray[smallestVertex] + vertex.at(i).second < distanceArray.at(i)) {
                distanceArray.at(i) = distanceArray[smallestVertex] + vertex.at(i).second;
            }
        }
        visited.insert(smallestVertex);
    }
    return distanceArray;
}

int main(void) {
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