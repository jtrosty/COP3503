#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <stack>
#include <queue>
#include <tuple>

using std::to_string;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class SolutionSumRootToLeaf {
public:
    /*
    * make and array of these numbers, then calculate them.
    DFS, make and array of  each set of binary and calcuate the values each makes.  
    
    
    */
    int sum = 0;
    void preorder(TreeNode* node, int currentSum) {
         if (node != nullptr) {
            currentSum = (currentSum << 1 | node->val);
            if (node->left == nullptr && node->right == nullptr) {
                sum += currentSum;
            }
            preorder(node->left, currentSum);
            preorder(node->right, currentSum);
         }
    }
    

    
    int sumRootToLeaf(TreeNode* root) {
        preorder(root, 0);
        return sum;
    }
};
class SolutionLadderLength {
    /*
    * 1. maybe make another array of ints, where i add up each character.  any word that cna be converted into woudl be 26 letters away. 
    * 2. Maybe sort the world list and this array based on the array's values. 
    * 
    * Sort all the words in teh word list. and teh begining and end word. 
    * build them into a tree then search through the tree to find the word i want. 
    * 
    */

public:
    bool ladderDfs(vector<vector<int>>& graph, set<int>& visited, int count, int& finalCount, int source, int destination) {
        count++;
        visited.emplace(source);
        bool finalResult = false;
        for (int i = 0; i < graph.at(source).size(); i++) {
            if (visited.count(graph.at(source).at(i))) {
                continue;
            }
            if (graph.at(source).at(i) == destination) {
                if (count < finalCount || finalCount == -1)  {
                    finalCount = count;
                }
                return true;
            }
            bool result  = ladderDfs(graph, visited, count, finalCount, graph.at(source).at(i), destination);
            if (result) finalResult = true;
        }
        return finalResult;
    }

    bool compareLadderWords(string a, string b) {
        int lettersDifferent = 0;
        int indexOfDifferentLetter;
        if (a.size() != b.size()) return false;

        for (int i = 0; i < a.size(); i++) {
            if (a.at(i) != b.at(i)) {
                lettersDifferent++;
            }
            if (lettersDifferent > 1) return false;
        }
        if (lettersDifferent == 1) {
            return true;
        }
        return false;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Start with making an adjancey matrix
        set<int> visited;
        int count = 1;

        wordList.push_back(beginWord);

        // Build the graph
        int endWordIndex = -1;
        int wordBeingIndex = wordList.size() - 1;
        vector<vector<int>> graph(wordList.size());

        for (int i = 0; i < wordList.size(); i++) {
            for (int j = i; j <wordList.size(); j++) {
                if (wordList.at(i).compare(endWord) == 0) endWordIndex = i;
                if ((wordList.at(i).compare(beginWord) == 0) && (i != wordList.size() - 1)) {
                    wordList.pop_back();
                    wordBeingIndex = i;
                }
                if (compareLadderWords(wordList.at(i), wordList.at(j))) {
                    graph.at(i).push_back(j);
                    graph.at(j).push_back(i);
                }
            }
        }
        if (endWordIndex == -1) return 0;
        int finalCount = -1;
        ladderDfs(graph, visited, count, finalCount, wordBeingIndex, endWordIndex);
        if (finalCount == -1) return 0;
        return finalCount;
    }
};

class SolutionCanFinish {
public:
    /*
    If I build a graph with this. 
    Need to check for cycle. 
    0 - 1
    1 - 2 
    2 - 0
    */
    bool dfs2(set<int>& visited, vector<vector<int>>& graph, int source, int destination) {
        bool result = false;
        for (int i = 0; i < graph.at(source).size(); i++) {
            if (graph.at(source).at(i) == destination) {
                return true;
            }
            else {
                if(visited.count(graph.at(source).at(i))) continue;
                visited.emplace(source);
                result = dfs2(visited, graph, graph.at(source).at(i), destination);
                if (result) return true;
            }
        }
        return false;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        set<int> visited; 
        vector<vector<int>> graph(numCourses);
        bool result = true;
        for (int i = 0; i < prerequisites.size(); i++) {
            graph.at(prerequisites.at(i).at(0)).push_back(prerequisites.at(i).at(1));
        }
        for (int i = 0; i < graph.size(); i++) {
            result = dfs2(visited, graph, i, i);
            visited.clear();
            if (result) return false;
        }
        return true;
    }


    bool dfs(vector<vector<int>>& graph, set<int>& path, set<int>& visited, int course, int prereq) {
        bool result;
        for (int i = 0; i < graph.at(prereq).size(); i++) {
            path.emplace(course);
            if (path.count(graph.at(prereq).at(i)) || graph.at(prereq).at(i) == prereq) {
                // we have a cycle 
                return false;
            }
            if (visited.count(graph.at(prereq).at(i))) continue;
            path.emplace(prereq);
            result = dfs(graph, path, visited, prereq, graph.at(prereq).at(i));
            if (result == false) return false;
            path.clear();
        }
        return true;
    }

    bool canFinish2(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        bool result = true;
        for (int i = 0; i < prerequisites.size(); i++) {
            graph.at(prerequisites.at(i).at(0)).push_back(prerequisites.at(i).at(1));
        }
        // graph is built, now check for a cycle., 
        // use DFS
        set<int> visited;
        set<int> path;
        for (int i = 0; i < graph.size(); i++) {
            if (visited.count(i)) continue;
            for (int j = 0; j < graph.at(i).size(); j++) {
                if (i == graph.at(i).at(j)) return false;
                result = dfs(graph, path, visited, i, graph.at(i).at(j));
                if (result == false) return false;
            }
            visited.emplace(i);
        }
        return result;
    }
};

class SolutionValidateTree {
public:
    void addToArray(vector<int>& array, TreeNode* node) {
        if (node == nullptr) return;

        addToArray(array, node->left);
        array.push_back(node->val);
        addToArray(array, node->right);
    }

    bool isValidBST(TreeNode* root) { 
        vector<int> array;
        addToArray(array, root);
        if (array.size() == 1) return true;
        for (int i = 0; i < array.size() - 1; i++) {
            if (array.at(i) < array.at(i+1)) {
                // great
            }
            else {
                return false;
            }
        }
        return true;
    }

    bool isValidBST2(TreeNode* root) {
        bool result;
        if (root->left != nullptr && root->right != nullptr) {
            if (root-> left->val < root->val && root->right->val > root->val) {
                // good. 
                result = isValidBST(root->right);
                result = isValidBST(root->left);
            }
            else return false;
        }
        else if (root->left != nullptr) {
            if (root->left->val < root->val) {
                result = isValidBST(root->left);
            }
            else return false;
        }
        else if (root->right != nullptr) {
            if (root->right->val > root->val) {
                result = isValidBST(root->right);
            }
            else return false;
        }
        else if (root->left == nullptr && root->right == nullptr) { 
            return true;
        }
        if (result == false) return false;
        return true;
    }
};

class SolutionZigZag {
public:

    void zigZag(vector<vector<int>>& result, TreeNode* node, int depth) {
        if (node == nullptr) return;

        depth++;
        if (result.size() < depth) {
            vector<int> newVector;
            result.push_back(newVector);
        }
        zigZag(result, node->left, depth);
        result.at(depth - 1).push_back(node->val);
        zigZag(result, node->right, depth);
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        zigZag(result, root, 0);
        for (int i = 1; i < result.size(); i += 2) {
            std::reverse(result.at(i).begin(), result.at(i).end());
        }
        return result;
    }
};

class SolutionIslands {
public:
/*
    Input: grid = [
    ["1","1","1","1","0"],
    ["1","1","0","1","0"],
    ["1","1","0","0","0"],
    ["0","0","0","0","0"]
    ]
    Output: 1

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'.

    So a breath first search would solve this. Go through 
*/

    int searchIslands(vector<vector<char>>& grid, set<string>& visited, int i, int j) {
        int numOfRows = grid.size();
        int numOfCols = grid.at(0).size();
        if (i == numOfRows || j == numOfCols) return 0;

/*
        int r, nr, nc, c;
        if (r - 1 >= 0 && grid[r-1][c] == '1') dfs(grid, r - 1, c);
        if (r + 1 < nr && grid[r+1][c] == '1') dfs(grid, r + 1, c);
        if (c - 1 >= 0 && grid[r][c-1] == '1') dfs(grid, r, c - 1);
        if (c + 1 < nc && grid[r][c+1] == '1') dfs(grid, r, c + 1);
        */

        string indexes = to_string(i);
        indexes.append(to_string(j));
        if (visited.count(indexes)) {
            return 0;
        }
        else if (grid.at(i).at(j) == '1' ) {
            visited.emplace(indexes);
            if (numOfCols == 1 && numOfRows == 1) {
                if (grid.at(i).at(j) == '1') return 1;
                else return 0;
            }
            else if (numOfRows == 1) {
                searchIslands(grid, visited, i, j + 1);
            }
            else if (numOfCols == 1) {
                searchIslands(grid, visited, i + 1, j);
            }
            else if (i == 0 && j == 0) {
                searchIslands(grid, visited, i + 1, j);
                searchIslands(grid, visited, i, j + 1);
            }
            else if ((i == numOfRows - 1) && j == 0) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j + 1);
            }
            else if (i == 0 && (numOfCols -1) == j) {
                searchIslands(grid, visited, i, j - 1);
                searchIslands(grid, visited, i + 1, j);
            }
            else if ((i == numOfRows - 1) && (numOfCols -1) == j) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j - 1);
            }
            else if (i == 0) {
                searchIslands(grid, visited, i + 1, j);
                searchIslands(grid, visited, i, j + 1);
                searchIslands(grid, visited, i, j - 1);
            }
            else if (i == numOfRows -1) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j + 1);
                searchIslands(grid, visited, i, j - 1);
            }
            else if (j == 0) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j + 1);
                searchIslands(grid, visited, i + 1, j);
            }
            else if (j == numOfCols -1) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j - 1);
                searchIslands(grid, visited, i + 1, j);
            } else {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i + 1, j);
                searchIslands(grid, visited, i, j - 1);
                searchIslands(grid, visited, i, j + 1);
            }
        }
        return 1;
    }

    int numIslands(vector<vector<char>>& grid) {
        set<string> visited;
        int numOfRows = grid.size();
        int numOfCols = grid.at(0).size(); 
        int result = 0;

        for (int i = 0; i < numOfRows; i++) {
            for (int j = 0; j < numOfCols; j++) {
                if (grid.at(i).at(j) == '1') {
                    // Begin BFS
                    result += searchIslands(grid, visited, i, j);
                }
            }
        }
        return result;
    }
};