#define MAXNUMVERTICES 10
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <climits>
using namespace std;

class Graph
{
    private:
        int theGraph[MAXNUMVERTICES][MAXNUMVERTICES] = {INT_MAX};
        set<int> vertices;      

    public:
        void insertEdge(int from, int to, int weight);
        void insertVertex(int x);
        int sumOfMST();
        // Feel free to add more methods to the API
};

void Graph::insertEdge(int to, int from, int weight)
{
	 this->theGraph[to][from] = weight;
     this->theGraph[from][to] = weight;
}

void Graph::insertVertex(int x)
{
	 this->vertices.insert(x);
}

int Graph::sumOfMST()
{
    int result = 0;
    int nextEdgeWeight;
    set<int> visited;
    // Build MST
    int nextVertexToAdd;
    visited.emplace(*(vertices.begin()));
    while (visited.size() < vertices.size()) {
        nextEdgeWeight = INT_MAX;
        for (auto iter = visited.begin(); iter != visited.end(); iter++) {
            for (int i = 0; i < MAXNUMVERTICES; i++) {
                if (theGraph[*iter][i] != 0 && !visited.count(i)) {
                    if (theGraph[*iter][i] < nextEdgeWeight) {
                        nextEdgeWeight = theGraph[*iter][i];
                        nextVertexToAdd = i;
                    }
                }
            }
        }
        result += nextEdgeWeight;
        visited.emplace(nextVertexToAdd);
    }
    return result;
    // Sum up MST        
}

int main()
{
    Graph *myGraph = new Graph();
    int numEdges, inVert, outVert, wt;
    std::cin >> numEdges;
    for (int i=0; i<numEdges; i++)
    {
        std::cin >> inVert;
        std::cin >> outVert;
        std::cin >> wt;
        myGraph->insertEdge(inVert, outVert, wt);
        myGraph->insertVertex(inVert);
        myGraph->insertVertex(outVert);
    }
    cout << myGraph->sumOfMST();
}