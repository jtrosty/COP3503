#include <vector>
#include <queue>

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

void relaxEdges() {

}

vector<int> dijkstra(const Graph& graph, int src) {
    int MAXINT = 0xffffffff;
    priority_queue< pair<int, int> > queue;
    int numVertices = graph.numVertices;
    vector<int> result;
    result.resize(numVertices);
    // PQ.add(source, 0)
    queue.push(std::make_pair(0, src));
    result.at(src) = 0;
    // Add to PQ the reamining vertices
    for (int i = 0; i < numVertices; i++) {
        if (i == src) continue;
        result.at(i) = 0xffffffff;
        queue.push(std::make_pair(MAXINT, i));
    }
    // For others PQ.add (v, infinity)
    pair<int, int> top;
    while (!queue.empty()) {
        top = queue.top();

        queue.pop();
        int size = graph.adjList.at(top.second).size();
        for (int i = 0; i < size; i++ ) {
            auto vertex = graph.adjList.at(top.second).at(i);
            if (top.first + vertex.second < result.at(i)) {
                result.at(i) = top.first + vertex.second;
            }

        }
    }
    return result;
}
