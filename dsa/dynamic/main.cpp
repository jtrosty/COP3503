#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <string>

using std::string;
using std::vector;


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