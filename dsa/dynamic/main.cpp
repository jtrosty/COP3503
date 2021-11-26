#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <string>
#include <set>
#include <map>
#include <algorithm>


using std::string;
using std::vector;
using std::cout;
using std::endl;

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
int backpack(int W, vector<int> weights, vector<int> values); 
string colorHelper(int value); 
vector<string> color(Graph& graph); 
int cut_bar(vector<int> const& p); 
int numWaysRatOutMaze(vector<vector<int>>& maze); 

/////////////////////////////////////////////////////////////////////////
//          11.3 Dynamic Programming Cutbar Problem
int numWaysRatOutMaze(vector<vector<int>>& maze) {
    // your code
    int x = maze.size();
    int y = maze.at(0).size();
    vector< vector<int> > table(x);
    for (int i = 0; i < x; i++) table.at(i).resize(y);

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (maze.at(i).at(j) == 1) {
                table.at(i).at(j) = 0;
            }
            else if (i == 0) {
                if (j == 0) 
                    table.at(0).at(0) = 1;
                else if (maze.at(i).at(j) == 1)
                    table.at(i).at(j) = 0;
                else if (table.at(i).at(j - 1) == 0) 
                    table.at(i).at(j) = 0;
                else
                    table.at(i).at(j) = 1;
            }
            else if (j == 0) {
                table.at(i).at(j) = table.at(i - 1).at(j);
            }
            else {
                table.at(i).at(j) = table.at(i - 1).at(j) + table.at(i).at(j - 1);
            }
        }
    }
    return table.at(x - 1).at(y - 1);
}

int main(void) {

/////////////////////////// maze
    vector< vector<int> > maze;
    maze.resize(3);
    maze.at(0) = {0, 0, 0};
    maze.at(1) = {0, 0, 1};
    maze.at(2) = {0, 0, 0};


    std::cout << "Maze: " << numWaysRatOutMaze(maze) << std::endl;


/////////////////////////// cut bar
    vector<int> bars = {1, 2, 3, 8};
    vector<int> bars2 = { 1, 1, 3, 4, 5, 6, 7, 8, 8, 12, 9 };
    std::cout << "cut bar: " << cut_bar(bars) << std::endl;

    vector<int> weights;
    weights.push_back(5);
    weights.push_back(4);
    weights.push_back(3);
    vector<int> values;
    values.push_back(10);
    values.push_back(7);
    values.push_back(5);

    backpack(7, weights, values);




    /*
    string input = "())((";
    std::cout << "test 2: " << minParenToAdd(input) << std::endl;
    */
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

/////////////////////////////////////////////////////////////////////////
//          11.1 Dynamic Programming Cutbar Problem
int cut_bar(vector<int> const& p) {
    const int n = p.size();
    int MININT = 0xf0000000;

    int* results = new int[n + 1];
    //for (int i = 0; i <= n; i++) results[i] = 0;
    results[0] = 0;
    
    int tempCompare;

    for (int i = 1; i <= n; i++) {
        tempCompare = MININT;
        for (int j = 1; j <= i; j++) {
            tempCompare = std::max(tempCompare, p.at(j - 1) + results[i - j]);
        }
        results[i] = tempCompare;
    }
    int finalResult = results[n];
    delete[] results;
    return finalResult;
}


/////////////////////////////////////////////////////////////////////////
//          11.2 Dynamic Programming Knapsack Problem
int backpack(int W, vector<int> weights, vector<int> values) {
    // Create the table to be use in dynamically programming solution
    vector< vector<int> > table;
    table.resize(weights.size() + 1);
    for (int i = 0; i <= weights.size(); i++) 
        table.at(i).resize(W + 1);

    for (int i = 0; i <= weights.size(); i++) {
        for (int j = 0; j <= W; j++) {
            // Handles the cases of 0 on the table
            if (i == 0 || j == 0) {
                table.at(i).at(j) = 0;
                continue;
            }
            else if (weights.at(i - 1) > j) {
                table.at(i).at(j) = table.at(i - 1).at(j);
            }
            else {
                int valueWithoutNewWeight = table.at(i - 1).at(j);
                int jLookup;
                if (j - weights.at(i - 1) < 0) jLookup = 0;
                else jLookup = j - weights.at(i - 1);
                int valueWithNewWeight = values.at(i - 1) + table.at(i - 1 ).at(jLookup); 
                if (valueWithNewWeight > valueWithoutNewWeight) 
                    table.at(i).at(j) = valueWithNewWeight;
                else 
                    table.at(i).at(j) = valueWithoutNewWeight;
            }
        }
    }
    /*
    for (int i = 0; i <= weights.size(); i++) {
        cout << "i is " << i << ": ";
        for (int j = 0; j <= W; j++) {
            cout << table.at(i).at(j) << ", ";
        }
        cout << endl;
    }
    */
    return table.at(weights.size()).at(W);
}
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