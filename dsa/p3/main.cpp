#include <string>
#include <iostream>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::string;

class AdjacencyList { 
    private: 
    //Think about what member variables you need to initialize 
    struct Data {
        std::vector<int> adjListTo;

        // The adjListFrom ints correspond to the degrees in degre
        std::vector<int> adjListFrom;
        std::vector<float> degree;
    };
    int indexCounter;
    std::map<string, int> index;
    std::map<int, Data > adjData;
    std::vector<float> rank;

//std::vector<int> adjListFrom;
    // resutls

    void CalculateDegree();
    void CalculateRank();

    public: 
    // Constructor
    AdjacencyList();

    void PageRank(int n);

    // Insertion functions
    int InsertPage(string name);
    bool InsertPage(string from, string to);

    // Print functions
    void PrintAll();
}; 

/////////////////////////////////////////////////////////////////////////////////////////
//                  Constructor

AdjacencyList::AdjacencyList() {
    indexCounter = 0;
}
 
// prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places 
void AdjacencyList::PageRank(int n){  
    rank.resize(indexCounter);
    for (int i = 0; i < indexCounter; i++) {

    }

} 

/////////////////////////////////////////////////////////////////////////////////////////
//                  Calculate Degree funtions
void AdjacencyList::CalculateDegree() {
    for (int i = 0; i < indexCounter; i++) {
        std::vector<int>* current = &adjData.at(i).adjListFrom;
        int numEdges = current->size();
        for (int j = 0; j < numEdges; j++) {
            // Calculate degree, iterate through the 'from list' got to the from vertex and determine number of
            // 'to's, the degree at current vertex is 1 / (numOfTos) of the from Vertex
            float degree = ((float) 1.0 / (float) adjData.at(current->at(j)).adjListTo.size());
            adjData.at(i).degree.push_back(degree);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//                  Calculate Rank funtions
void AdjacencyList::CalculateRank(){  
    rank.resize(indexCounter);
    for (int i = 0; i < indexCounter; i++) {
        rank.at(i) = 1.0 / (float) indexCounter;
    }
    for (int i = 0; i < indexCounter; i++) {
        rank.at(i) = 1.0 / (float) indexCounter;
    }
} 

/////////////////////////////////////////////////////////////////////////////////////////
//                  Insertion funtions
int AdjacencyList::InsertPage(string name) {
    if (!index.count(name)) 
        index.emplace(name, indexCounter++);
    return index.at(name);
}

bool AdjacencyList::InsertPage(string from, string to) {
    // Adds the webpages to the index
    int fromInt = insertPage(from);
    int toInt = insertPage(to);

    // Logic to add webpage to adjency list
    if (!adjData.count(fromInt)) {
        // Need to make the vector to add it to the list
        Data newAdjList;
        adjData.emplace(fromInt, newAdjList);
    }
    if (!adjData.count(toInt)) {
        // Need to make the vector to add it to the list
        Data newAdjList;
        adjData.emplace(toInt, newAdjList);
    }
    adjData.at(fromInt).adjListTo.push_back(toInt);
    adjData.at(toInt).adjListFrom.push_back(fromInt);
}

/////////////////////////////////////////////////////////////////////////////////////////
//                  Print funtions
void AdjacencyList::PrintAll() {
    for (auto iter = index.begin(); iter != index.end(); iter++) {
        cout << iter->first << ": " << iter->second << endl;
    }
    for (int i = 0; i < indexCounter; i++) {
        cout << i << ": ";
        auto a = adjData.at(i);
        for (int j = 0; j < a.adjListTo.size(); j++) {
            cout << a.adjListTo.at(j) << " ";
        }
        cout << endl;
    }


}

 
// This class and method are optional. To accept the input, you can use this method: 
 
 
int main() 
{ 
    AdjacencyList websites;
    int no_of_lines, power_iterations; 
    std::string from, to; 
    std::cin >> no_of_lines; 
    std::cin >> power_iterations; 
    for(int i=0; i< no_of_lines; i++) 
    { 
        std::cin >> from; 
        std::cin >> to; 
        websites.insertPage(from, to);
        // Do Something 
    } 
    //Create a graph object 
    websites.printAll();

    //Created_Graph.PageRank(power_iterations); 
} 