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
using std::vector;

class SolutionMaxProfit {
public:
    // hold the buying and show sell for each day after. 
    // Trakc macx
    // 
    int maxProfit(vector<int>& prices) { 
        int minPrice = INT_MAX;
        int profit = 0;
        for (int i = 0; i < prices.size(); i++) {
            if (prices.at(i) < minPrice) {
                minPrice = prices.at(i);
            }
            else if ((prices.at(i) - minPrice) > profit) {
                profit = prices.at(i) - minPrice;
            }
        }
        return profit;
    }

    int maxProfitBad(vector<int>& prices) {
        int result = 0;
        if (prices.size() == 1) return 0;
        int tempRevenue = 0;

        vector<vector<int>> trackRevenue(prices.size());
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < i; j++) {
                tempRevenue = ((prices.at(i) - prices.at(j)));
                if (i == 1) {
                    result = tempRevenue;
                }
                else {
                    if (tempRevenue > result) {
                        result = tempRevenue;
                    }
                }
                //trackRevenue.at(j).push_back(tempRevenue);
            }
        }
        if (result < 0) return 0;
        return result;
    }
};