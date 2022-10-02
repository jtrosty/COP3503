#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <stack>
#include <queue>
#include <tuple>

using std::string;
using std::unordered_map;
using std::vector;
using std::set;
using std::pair;
using std::tuple;
using std::stack;
using std::queue;
using std::cout;
using std::endl;
using std::make_pair;
using std::make_tuple;
using std::get;
using std::tie;
using std::swap;
using std::sort;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class SolutionRankTransform {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
                vector<int> sortedArr;
        sortedArr.assign(arr.begin(), arr.end());
        sort(sortedArr.begin(), sortedArr.end());
        int sizeArr = arr.size();
        
        unordered_map<int, int> rankMap;
        int rank = 1;
        for (int i = 0; i < sizeArr; i++) {
            if (rankMap.count(sortedArr.at(i)) == 0) {
                rankMap.emplace(sortedArr.at(i), rank++);
            }
        }
        for ( int i = 0 ; i < sizeArr; i++) {
            arr.at(i) = rankMap.at(arr.at(i));
        }
        return arr;
    }
};
/**
 * Definition for a binary tree node.
 */
class SolutionSumBST {
public:
    bool treeWalk(TreeNode* node, int remainder) {
        while (node != nullptr) {
            if (node->val == remainder) return true;
            else if (node->val > remainder) {
                node = node->left;
            }
            else if (node->val < remainder) {
                node = node->right;
            }
        }        
        return false;
    }
    
    bool preTreeWalk(TreeNode* node, TreeNode* root2, int target) {
        if (node == nullptr) return false;
        
        if (preTreeWalk(node->left, root2, target)) return true;
        if (preTreeWalk(node->right, root2, target)) return true;
        if (treeWalk(root2, target - node->val)) return true;
        return false;
    }
    
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        TreeNode* currNode1 = root1;
        TreeNode* currNode2 = root2;
        int remainder;
        return preTreeWalk(root1, root2, target);

    }
};