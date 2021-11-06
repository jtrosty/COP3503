#include<vector>
#include<stack>
#include<set>

using std::vector;
using std::stack;
using std::set;

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

bool dfs(const Graph& graph, int src, int dest) {
    std::stack<int> s;
    std::set<int> visited; 
}






int main(void) {

}