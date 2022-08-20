#include <set>
#include <vector>

class SolutionLeetCode75Day1 {
public:

    int calculateNewValue(int n) {
        int sum = 0;
        while (n != 0) {
            sum += ((n % 10) * (n % 10));
            n = n / 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        std::set<int> previousValues;
        bool isLoop = false;
        while (!previousValues.count(n)) {
            previousValues.emplace(n);
            n = calculateNewValue(n);
            if (n == 1) return true;
        }
        return false;
    }


};

class SolutionSpiralOrder {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
    }
};