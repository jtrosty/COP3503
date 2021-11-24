#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <string>
#include <set>
#include <map>


using std::string;
using std::vector;
class Graph {
public:
	// An array of vectors to represent an adjacency list
	vector<vector<int>> adjList;

	// The number of vertices in the graph
	int V;

	// The Constructor
};
int minParenToAdd(string s); 
int fuseMetals(vector<int>& values); 
/////////////////////////////////////////////////////////////////////////
//                  Graph Color 11.1.3
//Vertex 0: RED
//Vertex 1: BLUE
//Vertex 2: RED
//Vertex 3: GREEN
//Vertex 4: GREEN
//Vertex 5: BLUE
string colorHelper(int value) {
    switch(value) {
        case 0: 
            return "RED";
            break;
        case 1: 
            return "BLUE";
            break;
        case 2: 
            return "GREEN";
            break;
        case 3: 
            return "YELLOW";
            break;
        case 4: 
            return "ORANGE";
            break;
        case 5: 
            return "PURPLE";
            break;
    }
}

vector<string> color(Graph& graph) {
    const int numOfColors = 5;
    std::map<int, int> determined;
    int colorToChoose[numOfColors] = {0};
    
    // Loop through each vertex, determine the available colors. 
    for (int i = 0; i < graph.V; i++) {
        auto list = graph.adjList.at(i);
        int size = list.size();
        for (int j = 0; j < size; j++) {
            if (determined.count(list.at(j))) {
                colorToChoose[determined.at(list.at(j))] = 1;
            }
        }
        for (int j = 0; j < numOfColors; j++) {
            if (colorToChoose[j] == 0) {
                determined.emplace(i, j);
                break;
            }
        }
        for (int j = 0; j < numOfColors; j++) colorToChoose[j] = 0;
    }
    // Make the result
    vector<string> result;
    string temp;
    for (int i = 0; i < graph.V; i++) {
        //temp = i + " - ";
        //temp.append(colorHelper(determined.at(i)));
        result.push_back(colorHelper(determined.at(i)));
        //temp.erase();
    }
    return result;
}

int main(void) {
    string input = "())((";
    std::cout << "test 2: " << minParenToAdd(input) << std::endl;
    /*
    vector<int> test;
    test.push_back(2);
    test.push_back(4);
    test.push_back(3);
    vector<int> test2;
    test2.push_back(1);
    test2.push_back(8);
    test2.push_back(3);
    test2.push_back(5);
    std::cout << "hello " << fuseMetals(test2) << std::endl;
    */

}

int minParenToAdd(string s) {
	// your code
    std::stack<char> stack;
    if (s.size() == 1) return 1;
    if (s.size() == 0) return 0;
    
    stack.push(s.at(0));
    for (int i = 1; i < s.size(); i++) {
        if (stack.empty()) {
            stack.push(s.at(i));
            continue;
        }

        if(stack.top() == '(' && s.at(i) == ')')
            stack.pop();
        else    
            stack.push(s.at(i));
    }
    return stack.size();
}

int fuseMetals(vector<int>& values) {
    int result = 0;
    int temp;
    int tempResult;
    std::priority_queue<int, vector<int>, std::greater<int> > 
        pq(values.begin(), values.end());

    while (pq.size() > 1) {
        temp = pq.top();
        pq.pop();
        tempResult = temp + pq.top();
        result = result + tempResult;
        pq.pop();
        pq.push(tempResult);
    }
    return result;
}