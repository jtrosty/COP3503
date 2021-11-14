#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <iostream>

using std::set;
using std::stack;
using std::vector;
using std::unordered_map;

/*
class Graph {
    public:
        int numVertices;
        vector<vector<int>> adjList;
        int numOfEdges;

        struct Edge {
            int src, dest;
            Edge(int _src, int _dest) {src = _src; dest = _dest;}
        };

        Graph(const vector<vector<int>>& edge, int vertices) {
            numVertices = vertices;
            numOfEdges = edge.size();

            adjList.resize(vertices);

            for (int i = 0; i < vertices; i++) {
                adjList[edge.at(i).at(0)].push_back(edge.at(i).at(1));
                adjList[edge.at(i).at(1)].push_back(edge.at(i).at(0));
            }
        }
};
*/

class Solution {
    public:
    //////////////////////////////////////////////////////////////
    //               Depth first search
    void dfs(unordered_map<int, vector<int>>& adjList, vector<bool>& visited, int src) {
        visited[src] = true;
        for (auto i: adjList[src]) {
            if (visited[i] == false) 
                dfs(adjList, visited, i);
        }
    }

    int makeConnected(int n, vector<vector<int>>& connections) {
        vector<bool> visited(n, false);
        unordered_map<int, vector<int>> adjList;
        // Make adjency list, find number of edges
        int numOfEdges = 0;
        for (int i = 0; i < connections.size(); i++) {
            adjList[connections[i][0]].push_back(connections[i][1]);
            adjList[connections[i][1]].push_back(connections[i][0]);
            numOfEdges++;
        }

        // Find number of seperated graphs
        int numOfSeperateGraphs = 0;
        for ( int i = 0; i < n; i++) {
            if (!visited[i]) {
                numOfSeperateGraphs++;
                dfs(adjList, visited, i);
            }
        }
        // Return result
        if (numOfEdges < n - 1) return -1;
        int extraEdges = numOfEdges - ((n-1) - (numOfSeperateGraphs - 1));
        if (extraEdges >= (numOfSeperateGraphs -1)) 
            return numOfSeperateGraphs - 1;
        return -1;
    }
};

int main (void) {
    vector<vector<int>> testCase;
    testCase.push_back({0, 1});
    testCase.push_back({0, 2});
    testCase.push_back({1, 2});
    Solution mySolution;
    std::cout << mySolution.makeConnected(4, testCase) << std::endl;

}