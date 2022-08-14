#include<vector>>

using std::vector;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> mergedArrays;
        int mergedSize = nums1.size() + nums2.size();
        char isEven = 0;
        if (mergedSize % 2 == 0 && mergedSize != 0) {
            mergedSize = (mergedSize / 2) + 1;
            isEven = 1;
        }
        else {
            mergedSize = mergedSize / 2;
        }
        int index1 = 0;
        int index2 = 0;
        if (mergedSize == 0) return 0.0;
        if (nums1.size() == 0 && nums2.size() == 1) return (double)nums2.at(0);
        if (nums2.size() == 0 && nums1.size() == 1) return (double)nums1.at(0);

        for (int i = 0; i < mergedSize; i++) {
            if ((index1 < nums1.size()) && (index2 < nums2.size())) {
                if (nums1.at(index1) >= nums2.at(index2)) {
                    mergedArrays.push_back(nums1.at(index1++));
                }
                else if (nums2.at(index2) > nums1.at(index1)) {
                    mergedArrays.push_back(nums2.at(index2++));
                }
            }
            else if (index1 >= nums1.size()) {
                    mergedArrays.push_back(nums2.at(index2++));
            }
            else if (index2 >= nums2.size()) {
                    mergedArrays.push_back(nums1.at(index1++));
            }
        }
        if (!isEven) {
            return (double)mergedArrays.at(mergedSize);
        }
        double result = ((double)mergedArrays.at(mergedSize - 1) + (double)mergedArrays.at(mergedSize - 2)) / 2.0;
        return result;
    }
};