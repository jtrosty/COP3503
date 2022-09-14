#include <stdio.h>
#include <iostream>
#include <vector>
#include "addTwoNum.h"
#include "LongestSubStringNoRepeat.h"
#include "MedianTwoSortedArrays.h"
#include "LongestPalindrom.h"
#include "LeetCodeDay1.h"
#include "SolutionStringArray.h"
#include "LinkedList.h"
#include "TreeAndGraph.h"
#include "sortingsearching.h"

using std::cout;
using std::endl;
using std::vector;

int main(void) {

    ///////////  Compare Version TEST CODE
    SolutionCopyRandomList copyRandomList;
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    node1->next = node2;
    node1->random = NULL;
    node2->next = NULL;
    node2->random = node2;
    copyRandomList.copyRandomList(node1);


    ///////////  Compare Version TEST CODE
    SolutionMergeTwoLists solnMergeTwoLists;
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);
    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    ///////////  merge k listTEST CODE
    SolutionMergeKLists mergeK;
    vector<ListNode*> inputMergeK = {list1, list2};
    mergeK.mergeKLists(inputMergeK);

    SolutionReverseK reverseK;
    list1 = reverseK.reverseKGroup(list1, 2);


    solnMergeTwoLists.mergeTwoLists(list1, list2);
    

    ///////////  Compare Version TEST CODE
    SolutionCompareVersion compareVersion;
    std::cout << "Result " << compareVersion.compareVersion("1.2", "1.10") << std::endl;
    std::cout << "Result " << compareVersion.compareVersion("1.01", "1.001") << std::endl;
    std::cout << "Result " << compareVersion.compareVersion("0.1", "1.1") << std::endl;

    ///////////  ThreeSum TEST CODE
    SolutionThreeSum threeSum;
    vector<int> threeSumTestCase = {-1,0,1,2,-1,-4 }; // - 4 -1 -1 0 1 2
    vector<int> threeSumTest2 = {0, 1, 1}; // - 4 -1 -1 0 1 2
    vector<int> threeSumTest3 = {0, 0, 0, 0}; // - 4 -1 -1 0 1 2
    vector<int> threeSumTest4 = {-2, 0, 1, 1, 2}; // - 4 -1 -1 0 1 2
    vector<vector<int>> threeSumResult = threeSum.threeSum(threeSumTest4);
    int sizeRow = threeSumResult.size();
    int sizeCol = threeSumResult.at(0).size();
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            std::cout << threeSumResult.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    ///////////  Rotate TESTCODE
    /*
    SolutionRotate rotate;
    vector<vector<int>> vect {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    rotate.rotate(vect);
    */

    ///////////  Min Window Substring TESTCODE
    /*
    string s3 = "aaaaaaaaaaaabbbbbcdd";
    string t3 ="abcdd";
    SolutionMinWindow2 MinWindow;
    string s2 = "ab";
    string t2 = "a";
    std::cout << "MinWindow " << MinWindow.minWindow(s2, t2) << std::endl;
    std::cout << "MinWindow " << MinWindow.minWindow(s3, t3) << std::endl;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    std::cout << "MinWindow " << MinWindow.minWindow(s, t) << std::endl;
    string s1 = "ADOBECODEBANC";
    string t1 = "ABC";
    std::cout << "MinWindow " << MinWindow.minWindow(s1, t1) << std::endl;
    */


    ///////////  Groud Anagrams TESTCODE
    /*
    SolutionGroupAnagrams anagrams;
    vector<string> test = {"eat","tea","tan","ate","nat","bat"};
    auto reslt = anagrams.groupAnagrams(test);


    ///////////  Int to RomanTEST CODE
    SolutionIntToRoman intToRoman;
    std::cout << "int to Roman 1 " << intToRoman.intToRoman(1) << std::endl;
    std::cout << "int to Roman 2 " << intToRoman.intToRoman(3) << std::endl;
    std::cout << "int to Roman 3 " << intToRoman.intToRoman(58) << std::endl;
    std::cout << "int to Roman 3 " << intToRoman.intToRoman(1994) << std::endl;


    ///////////  Needle Haystack Container TEST CODE
    string haystack = "hello";
    string needle = "ll";
    SolutionNeedleHaystack needleHay;

    std::cout << "First occurence " << needleHay.strStr(haystack, needle) << std::endl;

*/


    ///////////  Max Container TEST CODE
    /*
    vector<int> maxTest1 = {1,8,6,2,5,4,8,3,7};
    vector<int> maxTest2 = {1,2,4,3};
    SolutionMaxArea solMaxArea;
    std::cout << "max Area " << solMaxArea.maxArea(maxTest1) << std::endl;
    std::cout << "max Area " << solMaxArea.maxArea(maxTest2) << std::endl;
    */
    ///////////  Valid Paren TEST CODE
    /*
    vector<int> test1 = {9,6,4,2,3,5,7,0,1};
    SolutionMissingNumber solMissingNumber;
    std::cout << "Missing number: " << solMissingNumber.missingNumber(test1) << std::endl;
    */

    ///////////  Valid Paren TEST CODE
    /*
    SolutionValidParen validParen;
    std::cout << "Parent " << validParen.isValid("()") << std::endl;
    */

    ///////////  trapping rain TEST CODE
    /*
    SolutionTrap trapWater;
    vector<int> heightTest = {5,4,1,2};
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> fail = {4, 2, 3};
    vector<int> failAgain = {0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> failAgain2 = {6,8,5,0,0,6,5};
    std::cout << "amt of trapped water: " << trapWater.trap(failAgain2) << std::endl;
    std::cout << "amt of trapped water: " << trapWater.trap(heightTest) << std::endl;
    */
    ///////////  reorder log FilesTEST CODE
    /*
    SolutionReorderLogFiles reorderLog;
    vector<string> logs = {"dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero" }; 
    vector<string> result = reorderLog.reorderLogFiles(logs);
    for (int i = 0; i < result.size(); i++) {
        std::cout << result.at(i) << std::endl;
    }
    std::cout << std::endl;
    */

    ///////////  two sum TEST CODE
    /*
    SolutionTwoSum solutiontwoSum;
    vector<int> test1 = {2,7,11,15};
    vector<int> result = solutiontwoSum.twoSum(test1, 9);
    std::cout << "TwoSum result: " << result.at(0) << " " << result.at(1) << std::endl;
    */

    ///////////  number to Words TEST CODE
    /*
    SolutionNumberToWords NumToWords;
    std::cout << "Num To words: " << NumToWords.numberToWords(0) << std::endl;
    std::cout << "Num To words: " << NumToWords.numberToWords(1) << std::endl;
    std::cout << "Num To words: " << NumToWords.numberToWords(100) << std::endl;
    std::cout << "Num To words: " << NumToWords.numberToWords(123) << std::endl;
    std::cout << "Num To words: " << NumToWords.numberToWords(12345) << std::endl;
    std::cout << "Num To words: " << NumToWords.numberToWords(1234567) << std::endl;
    std::cout << "Num To words: " << NumToWords.numberToWords(1234567890) << std::endl;
    */

    /*
    ///////////  First Unique CharTEST CODE
    SolutionFirstUniqueCharacter FirstUnique;
    std::cout << "First unique char at: " << FirstUnique.firstUniqChar("leetcode") << std::endl;
    std::cout << "First unique char at: " << FirstUnique.firstUniqChar("s") << std::endl;
    std::cout << "First unique char at: " << FirstUnique.firstUniqChar("aabb") << std::endl;


    ///////////  Most Common Word TEST CODE
    SolutionMostCommonWord MostCommonWord;
    string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
    string paragraph2 = "Bob";
    vector<string> banned {"hit"};
    std::cout << "Most commond word: " << MostCommonWord.mostCommonWord(paragraph, banned) << std::endl;
    std::cout << "Most commond word: " << MostCommonWord.mostCommonWord(paragraph2, banned) << std::endl;



    int whatIsTheHappiestNumber;
    /////////// Spiral Order TEST CODE
    SolutionSpiralOrder spiral;
    vector< vector <int> > matrix {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    auto result = spiral.spiralOrder(matrix); 
    for (int i = 0; i < result.size(); i++) {
        std::cout << result.at(i) << " ";
    }
        std::cout << std::endl;

    /////////// Happy Number TEST CODE

    SolutionLeetCode75Day1 happyNumber;
    printf("Results are: %i\n",happyNumber.isHappy(2)); 
    printf("Results are: %i\n",happyNumber.isHappy(19)); 
    printf("Results are: %i\n",happyNumber.isHappy(1)); 
    /////////// LongestPalindrome TEST CODE
    */

    /*
    SolutionLongestPalindrome testPalindrom;

    printf("Results are: %s\n", testPalindrom.longestPalindrome("xaabacxcabaaxcabaax"));
    printf("Results are: %s\n", testPalindrom.longestPalindrome("aaaaa"));
    printf("Results are: %s\n", testPalindrom.longestPalindrome("aaaa"));
    printf("Results are: %s\n", testPalindrom.longestPalindrome("babad"));
    */


    
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