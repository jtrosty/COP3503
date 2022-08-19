#include <stdio.h>
#include <vector>
#include "addTwoNum.h"
#include "LongestSubStringNoRepeat.h"
#include "MedianTwoSortedArrays.h"
#include "LongestPalindrom.h"

using std::vector;

int main(void) {
    /////////// LongestPalindrome TEST CODE
    SolutionLongestPalindrome testPalindrom;

    printf("Results are: %s\n", testPalindrom.longestPalindrome("xaabacxcabaaxcabaax"));
    printf("Results are: %s\n", testPalindrom.longestPalindrome("aaaaa"));
    printf("Results are: %s\n", testPalindrom.longestPalindrome("aaaa"));
    printf("Results are: %s\n", testPalindrom.longestPalindrome("babad"));


    
    /////////// Median Sorted Array TEST CODE
    /*
    printf("We are running Full bore \n");
    SolutionMedianSortedArrays testCodeMedian;
    std::vector<int> nums1 = { 1};
    std::vector<int> nums2 = { 1};
    std::vector<int> nums3 = { 1, 2};
    std::vector<int> nums4 = { 3, 4};
    printf("Results are: %f\n", testCodeMedian.findMedianSortedArrays(nums1, nums2));
    printf("Results are: %f\n", testCodeMedian.findMedianSortedArrays(nums2, nums1));
    printf("Results are: %f\n", testCodeMedian.findMedianSortedArrays(nums3, nums4));
    printf("Results are: %f\n", testCodeMedian.findMedianSortedArrays(nums4, nums3));
    */
    /////////// LONGEST SUB STRING NO REPEATE TEST CODE
    /*
    Solution testCast;
    printf("Results are: %i\n", testCast.lengthOfLongestSubstring("ab"));
    printf("Results are: %i\n", testCast.lengthOfLongestSubstring("dvdf"));
    printf("Results are: %i\n", testCast.lengthOfLongestSubstring("bbbbbbb"));
    printf("Results are: %i\n", testCast.lengthOfLongestSubstring("pwwkew"));
    */
    
    /////////// ADD TWO NUMBERS TEST CODE
    /*
    SolutionAddTwoNumbers solAddTwoNum;
    SolutionAddTwoNumbers::ListNode* list2 = new SolutionAddTwoNumbers::ListNode(6);
    list2->next = new SolutionAddTwoNumbers::ListNode(4);
    list2->next->next = new SolutionAddTwoNumbers::ListNode(9);
    SolutionAddTwoNumbers::ListNode* list1 = new SolutionAddTwoNumbers::ListNode(4);
    list1->next = new SolutionAddTwoNumbers::ListNode(9);
    SolutionAddTwoNumbers::ListNode* result = solAddTwoNum.addTwoNumbers(list1, list2);

    while (result != nullptr) {
        printf("%i ", result->val);
        result = result->next;
    }
    printf("\n");
    printf("iok\n");
    */

    return 0;
}