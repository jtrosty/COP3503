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
    //  0      1       2      3      4      5      6      7      8
    // 0,0 -> 1,0 - > 2,0 -> 2,1 -> 2,2 -> 1,2 -> 0,2 -> 0,1 -> 1,1

    vector<int> spiralOrder(vector <vector <int> >& matrix) {
        vector<int> result;

        int leftTop = 0;
        int rightBottom = 2;
        for (int i = 0; i <= rightBottom; i++) {
            result.push_back(matrix.at(leftTop).at(i));
        }
        for (int i = 0; i < rightBottom; i++) {
            result.push_back(matrix.at(i).at(rightBottom));
        }
        rightBottom--;
        for (int i = rightBottom; i >= leftTop; i--) {
            result.push_back(matrix.at(rightBottom).at(i));
        }
        for (int i = rightBottom + 1; i > leftTop; i--) {
            result.push_back(matrix.at(i).at(rightBottom));
        }
        leftTop++;
        return result;
    }
};