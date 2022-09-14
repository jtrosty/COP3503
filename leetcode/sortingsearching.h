#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <stack>
#include <queue>
#include <tuple>
#include <queue>

using std::vector;

class SolutionKLargest {
    /*
    *
    * find the kth largets element in a unsorted array. 
    * must be done in O(n) complexity.
    * go thorugh array once.  
    * Start with finding the largest
    * Just keep track of the largest index
    * 
    *   k = 2
    *  2 3 4 5 6
    *  2
    */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        
    }
};
public:
    int findKthLargest(vector<int>& nums, int k) {
        // Get the largest
        std::priority_queue<int, std::vector<int>, std::greater<int>> kLargest; // Makes it act as a min priority queue

        if (nums.size() == 1) return nums.at(0);

        for (int i = 0; i < nums.size(); i++)  {
            if (kLargest.size() < k) {
                kLargest.emplace(nums.at(i));
            }
            else {
                if (nums.at(i) > kLargest.top()) {
                    kLargest.pop();
                    kLargest.emplace(nums.at(i));
                }
            }
        }
        return kLargest.top();
    }
};