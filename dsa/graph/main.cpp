#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Graph
{
    private:
        // Graph ADJACENCY LIST data structure here 



    public:
        struct Edge {
            int toVertex;
            int weight;
            Edge* next;
            Edge(int to, int edgeWeight) : toVertex(to), weight(edgeWeight) {};
        };
        std::unordered_map<int, Graph::Edge>* agencyList;
        void insertEdge(int from, int to, int weight);  
        bool isEdge(int from, int to);  
        int getWeight(int from, int to);  
        vector<int> getAdjacent(int vertex); 
        void printGraph(); 
};

void Graph::insertEdge(int from, int to, int weight) 
{
   /*
        insertEdge() adds a new edge between the from and to vertex.
        You will not know how many vertices there may be.
        insertEdge does not output or print anything
   */
    if (agencyList->count(from)) {
        Edge* temp = &(agencyList->at(from));
        while (temp->next != nullptr) {
            if (temp->toVertex == to) {
                return;
            }
            temp = temp->next;
        }
        Edge* newEdge = new Edge(from, weight);
        temp->next = newEdge;
    }
    Edge* newEdge = new Edge(from, weight);
    std::pair<int, Graph::Edge> itemToInsert (from, newEdge);
    agencyList->insert(itemToInsert);
}

bool Graph::isEdge(int from, int to) 
{
    /*
        TODO: isEdge() returns a boolean indicating true 
        if there is an edge between the from and to vertex
    */
    if (agencyList->count(from)) {
        Edge* temp = &(agencyList->at(from));
        while (temp->next != nullptr) {
            if (temp->toVertex == to) return true;
        }
        if (temp->toVertex == to) return true;
    }
    else {
        return false;
    }
    return false;
}

int Graph::getWeight(int from, int to) 
{
    // getWeight() returns the weight of the edge between the from and to vertex
    if (agencyList->count(from)) {
        Edge* temp = &(agencyList->at(from));
        while (temp != nullptr) {
            if (temp->toVertex == to) 
                return temp->weight;
            temp = temp->next;
        }
    }

    return 0;
}

vector<int> Graph::getAdjacent(int vertex) 
{
    //TODO: getAdjacent() returns a sorted vector of all vertices that are connected to a vertex
    vector<int> result;
    if (agencyList->count(vertex)) {
        Edge* temp = &(agencyList->at(vertex));
        while (temp != nullptr) {
            result.push_back(temp->toVertex);
        }
    }
    if (result.size() > 1) 
        std::sort (result.begin(), result.end());

    return result;
}

void Graph::printGraph()
{
    //TODO: printGraph() prints the graph in a format sorted by ascending vertex matrix of weights
    int size = agencyList->size();
    vector<int> temp;
    for (int i = 0; i < size; i++) {
        temp = getAdjacent(i);
        cout << i << " ";
        for (int j = 0; j < temp.size(); j++) {
            cout << temp.at(j) << " ";
        }
    }
    cout << endl;
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