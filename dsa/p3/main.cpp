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
    int indexCounter;
    std::map<string, int> index;
    std::map<int, std::vector<int>> adjList;
    // resutls
    std:: vector<float> rank;

    public: 
    // Constructor
    AdjacencyList();

    void PageRank(int n);

    // Insertion functions
    int insertPage(string name);
    bool insertPage(string from, string to);

    // Print functions
    void printAll();
}; 

/////////////////////////////////////////////////////////////////////////////////////////
//                  Constructor

AdjacencyList::AdjacencyList() {
    indexCounter = 0;
}
 
void AdjacencyList::PageRank(int n){  } // prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places 

/////////////////////////////////////////////////////////////////////////////////////////
//                  Insertion funtions
int AdjacencyList::insertPage(string name) {
    if (!index.count(name)) 
        index.emplace(name, indexCounter++);
    return index.at(name);
}

bool AdjacencyList::insertPage(string from, string to) {
    // Adds the webpages to the index
    int fromInt = insertPage(from);
    int toInt = insertPage(to);

    // Logic to add webpage to adjency list
    if (!adjList.count(fromInt)) {
        // Need to make the vector to add it to the list
        std::vector<int> toVector = {toInt};
        adjList.emplace(fromInt, toVector);
    }
    else  adjList.at(fromInt).push_back(toInt);
}

/////////////////////////////////////////////////////////////////////////////////////////
//                  Print funtions
void AdjacencyList::printAll() {
    for (auto iter = index.begin(); iter != index.end(); iter++) {
        cout << iter->first << ": " << iter->second << endl;
    }
    for (int i = 0; i < indexCounter; i++) {
        cout << i << ": ";
        auto a = adjList.at(i);
        for (int j = 0; j < adjList.at(i).size(); j++) {
            cout << a.at(j) << " ";
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