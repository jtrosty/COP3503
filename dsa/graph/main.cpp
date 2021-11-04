#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;


class Graph
{
   private:
      // Graph ADJACENCY LIST data structure here 
      struct Edge {
          int toVertex;
          int weight;
          Edge* next;
          Edge(int to, int edgeWeight) : toVertex(to), weight(edgeWeight) {};
      };

      struct Vertex {
          int value;
          Edge* edge;
          Vertex (int newValue) : value(newValue), edge(nullptr) {}
      };
      vector<Edge*> agencyList;

    public:
      void insertEdge(int from, int to, int weight);  
      bool isEdge(int from, int to);  
      int getWeight(int from, int to);  
      vector<int> getAdjacent(int vertex); 
      void printGraph(); 
};

void Graph::insertEdge(int from, int to, int weight) 
{
   /*
        TODO: insertEdge() adds a new edge between the from and to vertex.
        You will not know how many vertices there may be.
        insertEdge does not output or print anything
   */
}

bool Graph::isEdge(int from, int to) 
{
    /*
        TODO: isEdge() returns a boolean indicating true 
        if there is an edge between the from and to vertex
    */
    return true;
}

int Graph::getWeight(int from, int to) 
{
    //TODO: getWeight() returns the weight of the edge between the from and to vertex
    return 0;
}

vector<int> Graph::getAdjacent(int vertex) 
{
    //TODO: getAdjacent() returns a sorted vector of all vertices that are connected to a vertex
    return vector<int>();
}

void Graph::printGraph()
{
    //TODO: printGraph() prints the graph in a format sorted by ascending vertex matrix of weights
}

int main()
{
    //DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK

    int noOfLines, operation, vertex, to, fro, weight, source, j;
    vector<int> arr;
    int arrSize;
    Graph g;
    cin>>noOfLines;
    for(int i=0;i<noOfLines;i++)
    {
        cin>>operation;
        switch(operation)
        {
            case 1: 
                cin>>fro;
                cin>>to;
                cin>>weight;
                g.insertEdge(fro,to,weight);
                break;
            case 2: 
                cin>>fro;
                cin>>to;
                cout<<g.isEdge(fro,to)<<"\n";
                break;
            case 3: 
                cin>>fro;
                cin>>to;
                cout<<g.getWeight(fro,to)<<"\n";
                break;
            case 4: 
                cin>>vertex;
                arr=g.getAdjacent(vertex);
                arrSize = arr.size();
                j=0;
                while(j<arrSize)
                {
                    cout<<arr[j]<<" ";
                    j++;
                }
                cout<<"\n";
                break;
            case 5: 
                g.printGraph();
                cout<<"\n";
                break;
        }
    }
}