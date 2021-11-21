#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip> 

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::setprecision;

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
    std::vector<float> rankPrev;
    std::vector<float> rank;

    // Functions perform the work to support PageRank
    void CalculateDegree();
    void CalculateRank(int n);

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
//                          Main
/////////////////////////////////////////////////////////////////////////////////////////
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
        websites.InsertPage(from, to);
        // Do Something 
    } 
    //Create a graph object 
    //websites.PrintAll();
    websites.PageRank(power_iterations);
} 

/////////////////////////////////////////////////////////////////////////////////////////
//                          Adjacency Class Definition
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//                  Constructor

AdjacencyList::AdjacencyList() {
    indexCounter = 0;
}
 
/////////////////////////////////////////////////////////////////////////////////////////
//                  Page Rank - most prints out the results
// prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places 
void AdjacencyList::PageRank(int n){  
    CalculateDegree();
    CalculateRank(n);
    cout << std::fixed;
    cout.precision(2);
    ofstream outFile;
    outFile.open("result.txt", std::ofstream::out);
    int oufile = 0;// Set to 1 to print results to file. 
    if (oufile) {
        outFile << std::fixed << std::setprecision(2);
        for (auto iter = index.begin(); iter != index.end(); iter++) {
            outFile << iter->first;
            outFile << " " << rank.at(iter->second) << endl;
        }
    }
    else {
        for (auto iter = index.begin(); iter != index.end(); iter++) {
            cout << iter->first;
            cout << " " << rank.at(iter->second) << endl;
        }
    }
    outFile.close();
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
void AdjacencyList::CalculateRank(int n){  
    rankPrev.resize(indexCounter);
    rank.resize(indexCounter);
    // below sets r(0) to 1/ #of sites
    for (int i = 0; i < indexCounter; i++) {
        rankPrev.at(i) = 1.0 / (float) indexCounter;
    }
    if (n == 1) {
        rank = rankPrev;
        return;
    }
    // Complete number of iteratiosn with n
    for (int k = 1; k < n; k++) {
        for (int i = 0; i < indexCounter; i++) {
            rank.at(i) = 0.0f;
        }
        for (int i = 0; i < indexCounter; i++) {
            Data* current = &adjData.at(i);
            for (int j = 0; j < current->adjListFrom.size(); j++) {
                rank.at(i) += (current->degree.at(j) * rankPrev.at(current->adjListFrom.at(j)));
            }
        }
        for (int i = 0; i < indexCounter; i++) {
            rankPrev.at(i) = rank.at(i);
        }
    }
} 

/////////////////////////////////////////////////////////////////////////////////////////
//                  Insertion funtions
int AdjacencyList::InsertPage(string name) {
    auto result = index.emplace(name, indexCounter);
    if (result.second) indexCounter++;
    
    return result.first->second;
    /*
    if (!index.count(name)) 
        index.emplace(name, indexCounter++);
    return index.at(name);
    */
}

bool AdjacencyList::InsertPage(string from, string to) {
    // Adds the webpages to the index
    int fromInt = InsertPage(from);
    int toInt = InsertPage(to);

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
 