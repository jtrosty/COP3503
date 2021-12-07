#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::string;

class Graph {
    private:
     vector< vector<int>> matrix;
     int numOfVertices;
    public:
      Graph();
      void insertEdge(int from, int to, int weight);  
      bool isEdge(int from, int to);
      int getWeight(int from, int to);
      vector<int> getAdjacent(int vertex);
      void printGraph(); 
};

Graph::Graph() {
    numOfVertices = 0;
    /*
    int size = 10;
    matrix.resize(size);
    for (int i = 0; i < size; i++) 
        matrix.at(i).resize(size);
        */
}

void Graph::insertEdge(int from, int to, int weight) {
    // Check to see if the maxtrix needs to be resized.  
    if(from >= numOfVertices || to >= numOfVertices) {
        int resize;
        if (from > to) resize = from;
        else  resize = to;
        resize += 1;
        matrix.resize(resize);
        for (int i = 0; i < resize; i++) 
            matrix.at(i).resize(resize);
        numOfVertices = resize;
    } 
    matrix.at(from).at(to) = weight;
    matrix.at(from).at(0) = 1;
    matrix.at(to).at(0) = 1;
}

bool Graph::isEdge(int from, int to) {
    if (matrix.at(from).at(to) != 0) return true;
    else                             return false;
}

int Graph::getWeight(int from, int to) {
    if (from < matrix.size() && to < matrix.size())
        return matrix.at(from).at(to);
    else 
        return 0;
    return 0;
}

vector<int> Graph::getAdjacent(int vertex) {
    vector<int> result;
    for (int i = 1; i < matrix.at(vertex).size(); i++) {
        if (matrix.at(vertex).at(i) > 0) result.push_back(i);
    }
    return result;
} 

void Graph::printGraph() {
    if (matrix.size()) {
        for (int i = 1; i < matrix.size(); i++) {
            if (matrix.at(i).at(0) != 0) {
                cout << i;
                for (int j = 1; j < matrix.at(i).size(); j++) {
                    if (matrix.at(j).at(0) != 0) {
                        cout << " " << matrix.at(i).at(j);
                    }
                }
                cout << endl;
            }
        }
    }
}
/*
    bool hasEdge = 0;
    string printOut;
    if (matrix.size()) {
        for (int i = 1; i < matrix.size(); i++) {
            hasEdge = 0;
            printOut = std::to_string(i);
            for (int j = 1; j < matrix.at(i).size(); j++) {
                printOut.append(" ");
                if (matrix.at(i).at(j) > 0) hasEdge = 1;
                printOut.append(std::to_string(matrix.at(i).at(j)));
                if (matrix.at(i).at(j) > 0) hasEdge = 1;
            }
            if (hasEdge) cout << printOut << endl;
        }
    }
    */

int main (void) {
    Graph graph;
    graph.insertEdge(1, 2, 10);

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