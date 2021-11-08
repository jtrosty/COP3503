#include <string>
#include <iostream>

class AdjacencyList { 
    private: 
    //Think about what member variables you need to initialize 
    public: 
    //Think about what helper functions you will need in the algorithm 
        void PageRank(int n);
}; 
 
void AdjacencyList::PageRank(int n){  } // prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places 
 
// This class and method are optional. To accept the input, you can use this method: 
 
 
int main() 
{ 
    int no_of_lines, power_iterations; 
    std::string from, to; 
    std::cin >> no_of_lines; 
    std::cin >> power_iterations; 
    for(int i=0; i< no_of_lines; i++) 
    { 
        std::cin >> from; 
        std::cin >> to; 
        // Do Something 
    } 
    //Create a graph object 
    //Created_Graph.PageRank(power_iterations); 
} 