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
			adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
		}
	}
};

void relaxEdges() {

}

vector<int> dijkstra(const Graph& graph, int src) {
    priority_queue<int[2]> queue;
    vector<int> result;
    // PQ.add(source, 0)
    int source[] = {src, 0};
    queue.push(source);
    for (int i = 0; i < graph.numVertices; i++) {
        source[0] = i;
        source[1] = 0xffffffff;
        queue.push(source);
    }
    // For others PQ.add (v, infinity)
    while (!queue.empty()) {
        relaxEdges();
    }

    return result;
}
