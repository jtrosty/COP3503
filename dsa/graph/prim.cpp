#define MAXNUMVERTICES 100
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <climits>
using namespace std;

class Graph
{
    private:
        int theGraph[MAXNUMVERTICES][MAXNUMVERTICES] = {0};
        set<int> vertices;      

    public:
        void insertEdge(int from, int to, int weight);
        void insertVertex(int x);
        void primMST();
        // Feel free to add more methods to the API
};

void Graph::insertEdge(int from, int to, int weight)
{
	 this->theGraph[to][from] = weight;
     this->theGraph[from][to] = weight;
}

void Graph::insertVertex(int x)
{
	 this->vertices.insert(x);
}

void Graph::primMST()
{
    vector< vector<int> > MST;
    set<int> inMST;
    //  Find the smallet edge and start at a vertex
    int startWeight = 0x7fffffff;
    int startSmallest;
    for (auto iterI = vertices.begin(); iterI != vertices.end(); iterI++) {
        for (auto iterJ = vertices.begin(); iterJ != vertices.end(); iterJ++){
            if (theGraph[*iterI][*iterJ] == 0) continue;
            if (theGraph[*iterI][*iterJ] < startWeight) {
                startWeight = theGraph[*iterI][*iterJ];
                startSmallest = *iterI;
            }
        }
    }
    
    int index = startSmallest;
    inMST.insert(index);

    while (inMST.size() < vertices.size()) {
        // Add vertices edges to MST
        /*
        for (int i = 0; i < vertices.size(); i++) {
            if (theGraph[index][i] == 0 || inMST.count(i)) continue;
            MST.push_back({i, theGraph[index][i]});
        }
        */
        // Find the smallest edge connected to starting edge
        int weight = 0x7fffffff;
        int to;
        int from;
        // Find the smallest edge connected 
        for (auto iter = inMST.begin(); iter != inMST.end(); iter++) {
            index = *iter;
            for (auto iterK = vertices.begin(); iterK != vertices.end(); iterK++) {
                if (theGraph[index][*iterK] == 0 || inMST.count(*iterK)) continue;
                if (theGraph[index][*iterK] < weight ) {
                    to = *iterK;
                    from = index;
                    weight = theGraph[index][*iterK];
                }
            }
        }
        inMST.insert(to);
        cout << from << " " << to << endl;
    }
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
    myGraph->primMST();
}