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
//////////////////////////////////////////////////////////////
//                7.3.1 Detect cycle in undirected graph
bool anyCycle(const Graph& graph) {
    // your code
    stack<int> s;
    set<int> visited; 

    vector< vector<int> >::iterator iter = graph.adjList.begin();

    // I want to skip vertexis if they are in the visited set.
    while (iter != graph.adjList.end()) {
        int source = iter.second.src;
        // perform DFS if item goes to vsisted, but not previous , then cycle

    }

    visited.insert(src);
    vector<int> temp;

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

bool dfs(const Graph& graph, int src, int dest) {
    stack<int> s;
    set<int> visited; 

    s.push(src);

    visited.insert(src);
    vector<int> temp;

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






int main(void) {

}