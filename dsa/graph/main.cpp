#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
using std::cout;
using std::endl;

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
        std::map<int, vector<Edge> >* agencyList;
        map<int, int> getSortedByWeight(int vertex);
    public:
        Graph();
        void insertEdge(int from, int to, int weight);  
        bool isEdge(int from, int to);  
        int getWeight(int from, int to);  
        vector<int> getAdjacent(int vertex); 
        void printGraph(); 
        void printGraph2();
};

Graph::Graph() {
    agencyList = new std::map<int, vector<Edge> >;
}

void Graph::insertEdge(int from, int to, int weight) 
{
   /*
        insertEdge() adds a new edge between the from and to vertex.
        You will not know how many vertices there may be.
        insertEdge does not output or print anything
   */
    Edge* newEdge = new Edge(to, weight);
    if (agencyList->empty() || agencyList->count(from) == 0) {
        vector<Edge> newVectEdge;
        agencyList->emplace(from, newVectEdge);
    }
    if (agencyList->count(to) == 0) {
        vector<Edge> newVectEdge;
        agencyList->emplace(to, newVectEdge);
    }
    agencyList->at(from).push_back(*newEdge);
}

bool Graph::isEdge(int from, int to) 
{
    /*
        isEdge() returns a boolean indicating true 
        if there is an edge between the from and to vertex
    */
    if (agencyList->count(from)) {
        vector<Edge>* temp = &(agencyList->at(from));
        for (int i = 0; i < temp->size(); i++) {
            if (temp->at(i).toVertex == to) return true;
        }
    }
    return false;
}

int Graph::getWeight(int from, int to) 
{
    // getWeight() returns the weight of the edge between the from and to vertex
    if (agencyList->count(from)) {
        vector<Edge>* temp = &(agencyList->at(from));
        for (int i = 0; i < temp->size(); i++) {
            if (temp->at(i).toVertex == to) return temp->at(i).weight;
        }
    }
    return -1;
}

vector<int> Graph::getAdjacent(int vertex) 
{
    //getAdjacent() returns a sorted vector of all vertices that are connected to a vertex
    vector<int> result;
    if (agencyList->count(vertex)) {
        vector<Edge>* temp = &(agencyList->at(vertex));
        for (int i = 0; i < temp->size(); i++) {
            result.push_back(temp->at(i).toVertex);
        }
    }
    if (result.size() > 1) 
        std::sort (result.begin(), result.end());
    return result;
}

map<int, int> Graph::getSortedByWeight(int vertex) 
{
    //getAdjacent() returns a sorted vector of all vertices that are connected to a vertex
    map<int, int> result;
    if (agencyList->count(vertex)) {
        vector<Edge>* temp = &(agencyList->at(vertex));
        for (int i = 0; i < temp->size(); i++) {
            result.emplace(temp->at(i).weight, temp->at(i).toVertex);
        }
    }
    return result;
}

void Graph::printGraph2()
{
    // printGraph() prints the graph in a format sorted by ascending vertex matrix of weights
    int size = agencyList->size();
    map<int, int> temp;
    auto iter = agencyList->begin();
    for ( ;iter != agencyList->end(); iter++) {
        temp = getSortedByWeight(iter->first);
        cout << iter->first << " ";
        if(!temp.empty()) {
            for (auto iter = temp.begin(); iter != temp.end(); iter++) {
                if (iter == (temp.end()--)) cout << iter->second;
                else cout << iter->second << " ";
            }
        }
        cout << endl;
    }
}

void Graph::printGraph()
{
    // printGraph() prints the graph in a format sorted by ascending vertex matrix of weights
    int size = agencyList->size();
    vector<int> temp;
    auto iter = agencyList->begin();
    for ( ;iter != agencyList->end(); iter++) {
        temp = getAdjacent(iter->first);
        if(!temp.empty()) {
            cout << iter->first << " ";
            for (int i = 0; i < temp.size(); i++) {
                if (i == temp.size() - 1) cout << temp.at(i);
                else cout << temp.at(i) << " ";
            }
        }
        else cout << iter->first;
        if (iter == (--(agencyList->end()))) {}
        else cout << endl;
    }
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
    /*
    Graph g;
    g.insertEdge(1, 2, 3);
    g.insertEdge(2, 3, 7);
    g.insertEdge(2, 4, 5);
    g.insertEdge(3, 4, 15);
    g.insertEdge(4, 1, 4);
    g.printGraph();
    */
}