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

class SolutionReverseStringK {
public:
    /*
    *1. go through array one time in a loop.
    *2. another loop to perfomr a swap, need to conisder even and odd.
    *3. need size of the string
    
                for (int j = 0; j < halfK; j++) {
                int index1 = i + j;
                int index2 = i + (k - 1) + j;
                swapChar(s, index1, index2);
            }
            
                string newString;
        
        if (sizeS == 1 || sizeS == 0) return s;
        
        for (int i = 0; i < sizeS; i++) {
            if (i == 0 || i % 2k == 0) {
                
            }
            newString.push_back(s.at(i));
    */
    void swapChar(string& s, int index1, int index2) {
        char temp = s.at(index1);
        s.at(index1) = s.at(index2);
        s.at(index2) = temp;
    }
    
    string reverseStr(string s, int k) {
        int sizeS = s.size();
        int halfK = k / 2;
        
        if (sizeS == 1 || sizeS == 0) return s;
        
        int counter = 0;
        for (int i = 0; i < sizeS; i = 2 * k * counter) {
            if (i + (k - 1) < sizeS) {
                for (int j = 0; j < halfK; j++) {
                    int index1 = i + j;
                    int index2 = i + (k - 1) - j;
                    swapChar(s, index1, index2);
                }
            } else {
                // reached the end
                int endReverse = (sizeS - 1 - i)  / 2;
                for (int j = 0; j < endReverse; j++) {
                    int index1 = i + j;
                    int index2 = sizeS -1 - j;
                    swapChar(s, index1, index2);             
                }
            }
            counter++;
            i++;
        }
        return s;
    }
};

class SolutionCompareVersion {
public:
    vector<int> makeSubSrings(string version) {
        vector<int> result;
        int subStringStart = 0;
        bool leadingZeroes = true;
        int size = version.size();

        for (int i = 0; i < size; i++) {
            if (version.at(i) == '.') {
                if (leadingZeroes == true) 
                    result.push_back(0);
                else 
                    result.push_back(stoi(version.substr(subStringStart, i - subStringStart)));

                subStringStart = i + 1;
                leadingZeroes = true;
            }
            else if (leadingZeroes && (version.at(i) == '0')) {
                subStringStart++;
            }
            else if (version.at(i) != 0) {
                leadingZeroes = false;
            }
        }
        if (leadingZeroes == true) 
            result.push_back(0);
        else 
            result.push_back(stoi(version.substr(subStringStart)));
        return result;
    }

    int compareVersion(string version1, string version2) {
        vector<int> version1Vect = makeSubSrings(version1);
        vector<int> version2Vect = makeSubSrings(version2);

        int size;
        bool version1Longer = true;
        int length1 = version1Vect.size();
        int length2 = version2Vect.size();
        int length = length1 - length2;
        if (version1Vect.size() < version2Vect.size()) {
            size = version1Vect.size();
            version1Longer = false;
        }
        else size = version2Vect.size();
        for (int i = 0; i < size; i++) {
            int item1 = version1Vect.at(i);
            int item2 = version2Vect.at(i);
            if (version1Vect.at(i) < version2Vect.at(i)) {
                return -1;
            }
            else if ( version1Vect.at(i) > version2Vect.at(i)) {
                return 1;
            }
        }
        if (length > 0) {
            for (int i = size; i < version1Vect.size(); i++) {
                if (version1Vect.at(i) > 0) {
                    return 1;
                }
            }
        }
        else if (length < 0) {
            for (int i = size; i < version2Vect.size(); i++) {
                if (version2Vect.at(i) > 0) {
                    return 1;
                }
            }
        }
        return 0;
    }
};

class SolutionThreeSum {
public:
    bool isSolnInResults(vector<int>& newSolution, vector<vector<int>>& results) {
        bool isUnique = false;
        for (int i = 0; i < results.size(); i++) {
            sort(results.at(i).begin(), results.at(i).end());
            for (int j = 0; j < 3; j++) {
                if (results.at(i).at(j) != newSolution.at(j)) {
                    isUnique = true;
                }
            }
        }
        return isUnique;
    }

    vector<int> twoSum(vector<int>& nums, int target) {

        vector<int> sorted;
        for (int i = 0; i < nums.size(); i++) {
            sorted.push_back(nums.at(i));
        }
        std::sort(sorted.begin(), sorted.end());

        int frontPointer = 0;
        int backPointer = nums.size() -1;
        int sum = 0;
        int numbers[2];
        vector<int> result{};

        while (frontPointer != backPointer) {
            sum = sorted.at(frontPointer) + sorted.at(backPointer);
            if (sum == target) {
                numbers[0] = sorted.at(frontPointer);
                numbers[1] = sorted.at(backPointer);
                break;
            } 
            else if (sum > target) {
                backPointer--;
            }
            else if (sum < target) {
                frontPointer++;
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums.at(i) == numbers[0] || nums.at(i) == numbers[1]) {
                result.push_back(i);
            }
        }
        return result;
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        set<int> numsVisited;

        sort(nums.begin(), nums.end());
        int size = nums.size();
        for (int i = 0; i < size; i++) {
            if (nums[i] > 0 ) break; // We are done no way to get zero again.
            // Perform 2sum
            numsVisited.clear();
            if (i == 0 || nums[i - 1] != nums[i]) {
                for (int j = i + 1; j < size; j++) {
                    int needValue = -(nums.at(i) + nums.at(j));
                    if (numsVisited.count(needValue)) {
                        vector<int> newResult = {nums.at(i), nums.at(j), needValue};
                        result.push_back(newResult);
                        while (j + 1 < size && nums.at(j) == nums.at(j + 1)) { // skip duplicates
                            j++;
                        }
                    }
                    numsVisited.emplace(nums.at(j));
                }
            }
        }
        return result;
    }
};

/*    bool isSolnInResults(vector<int>& newSolution, vector<vector<int>>& results) {
        bool isUnique = false;
        for (int i = 0; i < results.size(); i++) {
            sort(results.at(i).begin(), results.at(i).end());
            for (int j = 0; j < 3; j++) {
                if (results.at(i).at(j) != newSolution.at(j)) {
                    isUnique = true;
                }
            }
        }
        return isUnique;
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        set<int> usedNumbers;
        unordered_map<int, int> numsMap;
        for (int i = 0; i < nums.size(); i++) numsMap.emplace(nums.at(i), i);
        
        sort(nums.begin(), nums.end());

        int first = 0;
        int middle = first + 1;
        int end = nums.size() - 1;
        int count = 0;
        // Special cases
        if (nums.size() < 3) return result; // not big enough
        while ((first + 1) < end) {
            int valueFirst = nums.at(first); 
            int valueEnd = nums.at(end);
            int valueNeed = -(valueEnd + valueFirst);
            if (numsMap.count(valueNeed)) {
                // check if new triplet is in the resuls
                vector<int> newResult = {nums.at(first), nums.at(middle), nums.at(end)};
                if (result.size() == 0) result.push_back(newResult);
                else {
                    isSolnInResults(newResult, result);
                    result.push_back(newResult);
                }
            }
            if (count % 2 == 0) first++;
            else                end--;
            count++;
        }
        return result;
    }
            if (middle == end) {
                first++;
                middle = first + 1;
            }
            if ((nums.at(first) + nums.at(middle) + nums.at(end)) == 0) {
                if ((usedNumbers.count(nums.at(middle)) == 0) || (usedNumbers.count(nums.at(first)) == 0) || usedNumbers.count(nums.at(end))) {
                    vector<int> newResult = {nums.at(first), nums.at(middle), nums.at(end)};
                    result.push_back(newResult);
                    usedNumbers.emplace(nums.at(first));
                    usedNumbers.emplace(nums.at(middle));
                    usedNumbers.emplace(nums.at(end));
                    first++;
                    end--;
                    middle = first + 1;
                }
                else {
                    middle++;
                }
            }
            else {
                middle++;
            }
        }
        return result;
        */

class SolutionProductExceptSelf {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int totalProductNoZero = 1;
        set<int> zeroIndex;
        for (int i = 0; i < nums.size(); i++) {
            if (nums.at(i) == 0) {
                zeroIndex.emplace(i);
            }
            else {
                totalProductNoZero = totalProductNoZero * nums.at(i);
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (zeroIndex.size() > 1) {
                nums.at(i) = 0;
            }
            else if (zeroIndex.size() == 1) {
                if (nums.at(i) != 0) {
                    nums.at(i) = 0;
                }
                else {
                    nums.at(i) = totalProductNoZero;
                }
            }
            else {
                int temp = nums.at(i);
                nums.at(i) = (totalProductNoZero / temp) + (totalProductNoZero % temp);
            }
        }
        return nums;
    }
};

class SolutionRotateFast {
public:
    void rotate(vector<vector<int>>& matrix) {
        int matrixLength = matrix.size();
        int oddSizeAdjustment = 0;
        int half = matrixLength / 2;

        // transpose
        for (int i = 0; i < matrixLength; i++) {
            for (int j = i; j < matrixLength; j++) {
                swap(matrix.at(i).at(j), matrix.at(j).at(i));
            }
        }
        // reverse
        for (int i = 0; i < matrixLength; i++) {
            for (int j = i; j < half; j++) {
                swap(matrix.at(i).at(j), matrix.at(i).at(matrixLength - i - 1));
            }
        }
    }
};
class SolutionRotate {
public:
    void swap(vector<vector<int>>& matrix, int i, int j, int l) {
        int TL = matrix.at(i).at(j);
        int TR = matrix.at(j).at(l - i);
        int BR = matrix.at(l - i).at(l - j);
        int BL = matrix.at(l - j).at(i);

        int temp;
        temp = matrix.at(i).at(j);
        //  TL                      BL
        matrix.at(i).at(j) = matrix.at(l - j).at(i);
        //    BL                  BR
        matrix.at(l - j).at(i) = matrix.at(l - i).at(l - j) ;
        //    BR                  TR
        matrix.at(l - i).at(l - j) = matrix.at(j).at(l - i);
        //    TR               TL
        matrix.at(j).at(l - i) = temp;
    }

    void rotate(vector<vector<int>>& matrix) {
        int matrixLength = matrix.size();
        int oddSizeAdjustment = 0;
        int half;
        if (matrixLength % 2 == 1) {
            half = (matrixLength / 2) + 1;
        }
        else half = matrixLength / 2;

        for (int i = 0; i < half; i++) {
            int innerLength = matrixLength - i - 1;
            for (int j = i; j < innerLength; j++) {
                swap(matrix, i, j, matrixLength - 1);
            }
        }
    }
};

class SolutionMinWindow2 {
public:
    string minWindow(string s, string t) {
        int left = -1;
        int right = 0;
        int tSize = t.size();
        int sSize = s.size();
        int startSmallestWindow = -1;
        int countSmallestWindow = 1;
        unordered_map<char, int> tLetter;
        set<char> lettersCompletelyInWindow;
        for (int i = 0; i < tSize; i++) {
            if (tLetter.count(t.at(i)) == 0) {
                tLetter.emplace(t.at(i), -1);
            }
            else {
                tLetter.at(t.at(i))--;
            }
        }

        while (right < sSize) {
            char currLeter = s.at(right);
            if (tLetter.count(currLeter) == 0) {
                // This letter is not in t
                right++;
            }
            else {
                tLetter.at(currLeter)++;
                if (left == -1) left = right; // Handles the first time right finds a letter in the window.  
                if (tLetter.at(currLeter) == 0) {
                    // we have all the letters need for this letter!
                    lettersCompletelyInWindow.emplace(currLeter);
                    if (tLetter.size() == lettersCompletelyInWindow.size()) {
                        // Then we have all the letters in the window! make sure left is where we want it.
                        if (startSmallestWindow == -1) {
                            startSmallestWindow = left;
                            countSmallestWindow = right - left + 1;
                        }
                        else if (countSmallestWindow > (right - left + 1) ) {
                            startSmallestWindow = left;
                            countSmallestWindow = right - left + 1;
                        }
                        // Now move left untill the window is not valid
                        while (tLetter.size() == lettersCompletelyInWindow.size()) {
                            if (countSmallestWindow > (right - left + 1) ) {
                                startSmallestWindow = left;
                                countSmallestWindow = right - left + 1;
                            }
                            char leftCurrLetter = s.at(left);
                            if (tLetter.count(leftCurrLetter) == 1) {
                                tLetter.at(leftCurrLetter)--;
                                if (tLetter.at(leftCurrLetter) < 0) {
                                    // The window is not valid
                                    lettersCompletelyInWindow.erase(leftCurrLetter);
                                }
                            }
                            left++;
                        }
                        while (left <= right && tLetter.count(s.at(left)) == 0) left++;
                    }
                }
                right++;
            }
        }
        if (startSmallestWindow == -1) return "";
        /*
        if (startSmallestWindow + countSmallestWindow >= sSize) {
            return s.substr(startSmallestWindow);
        }
        */
        return s.substr(startSmallestWindow, countSmallestWindow);
    }
};

class SolutionMinWindow {
public:
    int aLowerStart = 65;
    int aUpperStart = 97;

    int getIndex(char letter) {
        if (letter < 97) {
            return letter - aLowerStart;
        }
        return letter - aUpperStart + 26;
    }


    void adjustLeft(string& string, queue<int>& queue, int& left, int tAlpha[]) {
        char letter = string.at(queue.front());
        tAlpha[getIndex(letter)]++;
        queue.pop();
        if (!queue.empty()) {
            left = queue.front();
        }
    }

    string minWindow(string s, string t) {
        queue<int> lettersInWindow;
        int tAlpha[52];
        for (int i = 0; i < 52; i++) {
            tAlpha[i] = -1;
        }
        int tSize = t.size();
        int sSize = s.size();
        int resultFront = 0;
        int resultCount = -1;
        // Built my hash Map
        for (int i = 0; i < tSize; i++) {
            char oneLetter = t.at(i);
            int indexCalc = getIndex(oneLetter);
            if (tAlpha[indexCalc] == -1) {
                tAlpha[indexCalc] = 0;
            }
            tAlpha[indexCalc]++;
        }

        int left = 0;
        int right = 0;
        while (right < sSize) {
            char oneLetter = s.at(right);
            int indexCalc = getIndex(oneLetter);
            if (tAlpha[indexCalc] < 0) {
                // Not a useful letter
                right++;
            }
            else if (tAlpha[indexCalc] > 0) {
                // success
                if (lettersInWindow.empty()) left = right;
                lettersInWindow.push(right);
                tAlpha[indexCalc]--;
                if ((tAlpha[indexCalc]) == 0)  {
                    // check to see if we have all of t
                    if (lettersInWindow.size() == tSize) {
                        // We should have all the letters
                        if ((right - left) < resultCount || resultCount == -1) {
                            resultFront = left;
                            resultCount = right - left + 1;
                        }
                        adjustLeft(s, lettersInWindow, left, tAlpha);
                    }
                }
                right++;
            } 
            else  {
                // We hit a letter we already used up. 
                while ((tAlpha[indexCalc] == 0) && !lettersInWindow.empty()) {
                    adjustLeft(s, lettersInWindow, left, tAlpha);
                }
            }
        }
        if (resultCount == -1) {
            return "";
        }
        return s.substr(resultFront, resultCount);
    }
};

class SolutionGroupAnagrams {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, int> anagramExist;
        int strsSize = strs.size();
        string sortedString;
        for (int i = 0; i < strsSize; i++) {
            sortedString = strs.at(i); 
            sort(sortedString.begin(), sortedString.end());

            if (anagramExist.count(sortedString) == 0) {
                anagramExist.emplace(sortedString, result.size());
                vector<string> newVector;
                newVector.push_back(strs.at(i));
                result.push_back(newVector);
            }
            else {
                result.at(anagramExist.at(sortedString)).push_back(strs.at(i));
            }
        }
        struct {
            bool operator()(vector<string>& a, vector<string>& b) {return a.size() > b.size();}
        } comp;
        sort(result.begin(), result.end(), comp);
        return result;
    }
};

/*
/// SHITTTY SOLUTION 
vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector< set< char> > theAnagrams;
        vector<vector<string>> result;
        int strsSize = strs.size();
        for (int i = 0; i < strsSize; i++) {
            // First Case done
            if (i == 0) {
                int lengthOfWord = strs.at(i).size();
                set<char> firstSet;
                for (int j = 0; j < lengthOfWord; j++) {
                    firstSet.emplace(strs.at(i).at(j));
                }
                theAnagrams.push_back(firstSet);
                result.at(0).push_back(strs.at(i));
            }
            else {
                int lengthOfWord = strs.at(i).size();
                int numOfSets = theAnagrams.size();
                bool anagram = true;
                for (int j = 0; j < theAnagrams; j++) {
                    auto iter = theAnagrams.at(j).begin(); 
                    auto end = theAnagrams.at(j).end(); 
                    for (; iter != end; iter++) {
                        if (iter->first)
                    
                   }
                }
                theAnagrams.push_back(firstSet);
                result.at(0).push_back(strs.at(i));

            }
        }
        return result;
    }
    */

class SolutionIntToRoman {
public:
    void appendLetters(string& result, char letter, int quantity) {
        for (int i = 0; i < quantity; i++) {
            result.push_back(letter);
        }
    }

    string intToRoman(int num) {
 
        tuple<char, int, int> roman[7];
        roman[0] = make_tuple('M', 1000, 900);
        roman[1] = make_tuple('D', 500, 400);
        roman[2] = make_tuple('C', 100, 90);
        roman[3] = make_tuple('L', 50, 40);
        roman[4] = make_tuple('X', 10, 9);
        roman[5] = make_tuple('V', 5, 4);
        roman[6] = make_tuple('I', 1, 1);
        string result;
        int value;

        for (int i = 0; i < 7; i++) {
            char letter;       // = get<0>(romanNums.at(i);
            int number;       //= get<1>(romanNums.at(i));
            int specialCase;  // = get<2>(romanNums.at(i));
            char specialCaseletter;       //= get<1>(romanNums.at(i));
            tie(letter, number, specialCase) = roman[i];
            value = num / number;
            appendLetters(result, letter, value);
            num = num - (number * value);
            if (((num % number) >= specialCase) && (number != 1)) {
                if (letter == 'M' || letter == 'D') specialCaseletter = 'C';
                else if (letter == 'L' || letter == 'C') specialCaseletter = 'X';
                else if (letter == 'V' || letter == 'X') specialCaseletter = 'I';
                appendLetters(result, specialCaseletter, 1);
                appendLetters(result, letter, 1);
                num = num - (specialCase);
            }
        }
        return result;

        // TODO: Delete 
        /*
         vector<tuple<char, int, int>> romanNums;
        romanNums.emplace_back(make_tuple('M', 1000, 900));
        romanNums.emplace_back(make_tuple('D', 500, 400));
        romanNums.emplace_back(make_tuple('C', 100, 90));
        romanNums.emplace_back(make_tuple('L', 50, 40));
        romanNums.emplace_back(make_tuple('X', 10, 9));
        romanNums.emplace_back(make_tuple('V', 5, 4));
        romanNums.emplace_back(make_tuple('I', 1, 1));      
        value = num / 1000;
        appendLetters(result, 'M', value);
        if (num % 1000 > 900) {
            appendLetters(result, 'D', 1);
            appendLetters(result, 'M', 1);
        }
        for (int i = 0; i < 7); i++) {
            char letter;       // = get<0>(romanNums.at(i));
            char number;       //= get<1>(romanNums.at(i));
            char specialCase;  // = get<2>(romanNums.at(i));
            tie(letter, number, specialCase) = romans.at(i);
            value = num / number;
            appendLetters(result, letter, value);
            num = num - (number * value);
            if (((num % number) > specialCase) && (number != 1)) {
                appendLetters(result, get<0>(romanNums.at(i + 1)), 1);
                appendLetters(result, letter, 1);
                num = num - (specialCase);
            }
        }
        */

    }
};

class SolutionNeedleHaystack {
public:
    int strStr(string haystack, string needle) {
        int haySize = haystack.size();
        int needleSize = needle.size();
        for (int i = 0; i < haySize; i++) {
            if (haystack.at(i) == needle.at(0)) {
                if (needle.compare(haystack.substr(i, needleSize)) == 0) {
                    return i;
                }
            }
        }
        return -1;
    }
};

class SolutionMaxArea {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int largestLeft = left;
        int largestRight = right;
        int largestArea = 0;
        int currentArea = 0;
        
        while (left != right) {
            currentArea = std::min(height.at(left), height.at(right)) * (right - left);
            if (currentArea > largestArea) {
                largestArea = currentArea;
                largestLeft = left;
                largestRight = right;
            }
            if (height.at(left) < height.at(right)) {
                left++;
            }
            else {
                right--;
            }
        }
        return largestArea;
    }
};


class SolutionMissingNumber {
public:
    int missingNumber(vector<int>& nums) {
        int* findMissing = new int[nums.size() + 1] {};
        for (int i = 0; i < nums.size(); i++) {
            findMissing[nums.at(i)] = 1;
        }
        int i = 0;

        // Find the missing falue
        while (findMissing[i] == 1) {i++;}

        delete[] findMissing;
        return i;
    }
};

class SolutionValidParen {
public:
    bool isValid(string s) {
        stack<char> brackets;
        char value;
        for (int i = 0; i < s.size(); i++) {
            value = s.at(i);
            switch (value) {
                case '(': 
                    brackets.push(value);
                    break;
                case '[': 
                    brackets.push(value);
                    break;
                case '{': 
                    brackets.push(value);
                    break;
                case ')': 
                    if (!brackets.empty() && (brackets.top() == '(')) brackets.pop();
                    else return false;
                    break;
                case ']': 
                    if (!brackets.empty() && brackets.top() == '[') brackets.pop();
                    else return false;
                    break;
                case '}': 
                    if (!brackets.empty() && brackets.top() == '{') brackets.pop();
                    else return false;
                    break;
            }
        }
        if (brackets.empty()) return true;
        return false;
    }
};

class SolutionTrap {
public:
    int trap(vector<int>& height) {
        // Go through from left
        vector<int> leftHeights;
        vector<int> rightHeights;
        leftHeights.resize(height.size());
        rightHeights.resize(height.size());
        
        int result = 0;
        int maxHeight = 0;
        for (int i = 0; i < height.size(); i++) {
            if (height.at(i) > maxHeight) {
                maxHeight = height.at(i);
            }
            leftHeights.at(i) = maxHeight;
        }
        // Go through from right
        maxHeight = 0;
        for (int i = height.size() - 1; i > -1; i--) {
            if (height.at(i) > maxHeight) {
                maxHeight = height.at(i);
            }
            rightHeights.at(i) = maxHeight;
        }

        for (int i = 0; i < height.size(); i++) {
            int min = 0;
            if (rightHeights.at(i) < leftHeights.at(i)) min = rightHeights.at(i);
            else                                        min = leftHeights.at(i);
            result += min - height.at(i);
        }
        return result;
    }
};

class SolutionTrapBad {
public:
    int trap(vector<int>& height) {
        set<int> skipTheseIndexes;
        int result = 0;
        for (int i = 1; i < height.size(); i++) {
            // Lets find the first peak
            if (height.at(i) < height.at(i - 1)) {
                // We have a peak at i - 1
                int peak = height.at(i - 1);
                int j = i;
                int waterTotal = 0;
                bool trapped = true;
                int highestLocal = 0;
                int highestLocalIndex = 0;

                while (height.at(j) < peak) {
                    if (height.at(j) > highestLocal) {
                        highestLocal = height.at(j);
                        highestLocalIndex = j;
                    }
                    if (j >= height.size() - 1) {
                        // reached the end the current peak didn't work. 
                        trapped = false;
                        break;
                    }
                    int currenHeight = height.at(j++);
                    waterTotal += peak - currenHeight;
                }
                if (trapped) {
                    result += waterTotal;
                    for (int k = i; k != j; k++) {
                        skipTheseIndexes.emplace(k);
                    }
                    i = j;
                }
                else if (highestLocal) {
                    i = j;
                }
            }
        }
        for (int i = height.size() - 2; i >= 0; i-- ) {
            if (skipTheseIndexes.count(i)) {
                continue;
            }
            // Lets find the first peak
            if (height.at(i) < height.at(i + 1)) {
                // We have a peak at i - 1
                int peak = height.at(i + 1);
                int j = i;
                int waterTotal = 0;
                bool trapped = true;
                int tempHeightLocal = 0;
                int tempWaterTotalForHeightsLocal = 0;
                int heightLocal = 0;
                int waterTotalForHeightsLocal = 0;

                while (height.at(j) < peak) {
                    if (j == 0) {
                        // reached the end the current peak didn't work. 
                        trapped = false;
                        break;
                    }
                    int currenHeight = height.at(j--);
                    waterTotal += peak - currenHeight;
                }
                if (trapped) {
                    result += waterTotal;
                    i = j;
                }
            }

        }
        return result;
    }
};

class SolutionTwoSum {
  public:
    struct NumsSorted {
        int number;
        int originalIndex;
    };
    struct {
        bool operator()(NumsSorted a, NumsSorted b) const {return a.number > b.number;}
    } compareLess;

    vector<int> twoSum(vector<int>& nums, int target) {

        vector<int> sorted;
        for (int i = 0; i < nums.size(); i++) {
            sorted.push_back(nums.at(i));
        }
        std::sort(sorted.begin(), sorted.end());

        int frontPointer = 0;
        int backPointer = nums.size() -1;
        int sum = 0;
        int numbers[2];
        vector<int> result{};

        while (frontPointer != backPointer) {
            sum = sorted.at(frontPointer) + sorted.at(backPointer);
            if (sum == target) {
                numbers[0] = sorted.at(frontPointer);
                numbers[1] = sorted.at(backPointer);
                break;
            } 
            else if (sum > target) {
                backPointer--;
            }
            else if (sum < target) {
                frontPointer++;
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums.at(i) == numbers[0] || nums.at(i) == numbers[1]) {
                result.push_back(i);
            }
        }
        return result;
    }
};

class SolutionReorderLogFiles {
public:
    struct comparePairStrings {
        bool operator()(const pair <string, string>& a, const pair <string, string>& b) const {
            if (a.second.compare(b.second) > 0) {
                return 0;
            } else if (a.second.compare(b.second) < 0) {
                return 1;
            } else {
                if (a.first.compare(b.first) > 0) {
                    return 1;
                }
            }
            return 0;
        }
    };

    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<int> trackDigits;
        vector< pair <string, string> > trackLetters;
        vector<string> result;

        for(int i = 0; i < logs.size(); i++) {
            int count = 0;
            while (logs.at(i).at(count) != ' ') {
                count++;
            }

            if (logs.at(i).at(0 + count + 1) >= 48 && logs.at(i).at(0 + count + 1) <= 57) {
                // It is a number
                trackDigits.push_back(i);
            }
            else {
                string identifier = logs.at(i).substr(0, count);
                string contents = logs.at(i).substr(count); 
                trackLetters.push_back(make_pair(identifier, contents));
            }
        }
        // Sort the letters
        sort(trackLetters.begin(), trackLetters.end(), comparePairStrings());

        // build log
        for (int i = 0; i < trackLetters.size(); i++) {
            result.push_back(trackLetters.at(i).first + trackLetters.at(i).second);
        }
        for (int i = 0; i < trackDigits.size(); i++) {
            result.push_back(logs.at(trackDigits.at(i)));
        }
        return result;
    }
};

class SolutionNumberToWords {
public:
        const string zero = "Zero";
        const string wordsTens[10] = {"", "", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety "};
        const string wordsNumber[20] = {"", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine ", "Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "};
        const string wordsBig[5] = {"Hundred ", "", "Thousand ", "Million ", "Billion "};

        string convertToWords(int threeDigitsMax, string range) {
            string result{};
            if (threeDigitsMax <= 0) return result;
            if (threeDigitsMax >= 1000) {
                return "Digits supplied to this funciton but be only 3";
            }
            int remainder = threeDigitsMax / 100;
            if ((remainder) > 0) {
                result.append(wordsNumber[remainder]);
                result.append(wordsBig[0]);
            }
            remainder = threeDigitsMax % 100;
            if (remainder > 19) {
                int tenth = remainder / 10;
                int ones = remainder % 10;
                result.append(wordsTens[tenth]);
                if (ones != 0) {
                    result.append(wordsNumber[ones]);
                }
            }
            else {
                result.append(wordsNumber[remainder]);
            }
            if (range.compare("hundred") != 0) {
                result.append(range);
            }
            if (range == wordsBig[1]) {
                return result;
            }
            return result;
        }

        string numberToWords(int num) {
            const int BILLION         = 1000000000;
            const int MILLION            = 1000000;
            const int THOUSAND              = 1000;
            string result{};
            int range = BILLION; // 1
            int threeDigits = 0;
            if (num == 0) return zero;
            for (int i = 4; i > 0; i--) {
                if (i != 4) {
                    range = range / 1000;
                } 
                threeDigits = (num / range) % 1000;
                result.append(convertToWords(threeDigits, wordsBig[i]));
            }
            if (result.at(result.size() - 1) == ' ') {
                result.pop_back();
            }
            return result;
    }
};

class SolutionFirstUniqueCharacter {
  public:
    int firstUniqChar(string s) {
        unordered_map<char, int> data; 
        for (int i = 0; i < s.size(); i++) {
            if (data.count(s.at(i))) {
                // it is in the list
                data.at(s.at(i)) = -1;
            }
            else {
                data.emplace(s.at(i), i);
            }
        }
        int result = -1;
        auto iter = data.begin();
        for (; iter != data.end(); iter++) {
            if ((iter->second > -1)) {
                result = iter->second;
                break;
            }
        }
        iter = data.begin();
        for (; iter != data.end(); iter++) {
            if ((iter->second < result) && (iter->second > -1)) {
                result = iter->second;
            }
        }
        return result;
    }
};

class SolutionMostCommonWord {
    bool skipWhiteSpace(char& letter) {
        if ( letter == ' ' ||
             letter == '!' ||
             letter == '?' ||
             letter == ',' ||
             letter == '.' ||
             letter == '\'' ||
             letter == ';' )
             return true;
        return false;
    }

    bool isBanned(string word, set<string>& banned) {
        return banned.count(word);
    }

  public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_map<string, int> results;
        set<string> bannedWords;
        for (int i = 0; i < banned.size(); i++) {
            bannedWords.emplace(banned.at(i));
        }
        // got through and find words
        
        for (int i = 0; i < paragraph.size(); i++) {
            if (skipWhiteSpace(paragraph.at(i))) continue;
            else {
                // found a word
                int count = 0;
                while(((i + count ) < paragraph.size()) && !skipWhiteSpace(paragraph.at(i + count))) {
                    char* letter = &paragraph.at(i + count);
                    // 101 is where A starts
                    if (*letter >= 65 && *letter <= 90) {
                        *letter = *letter + 32;
                    }
                    count++;
                }
                string word = paragraph.substr(i, count);
                if (!isBanned(word, bannedWords)) {
                    if (results.count(word)) {
                        results.at(word)++;
                    }
                    else {
                        results.emplace(word, 1);
                    }
                }
                i += count;
            }
        }
        string mostCommon;
        int numOfTimes = 0;
        for (auto iter = results.begin(); iter != results.end(); iter++) {
            if (iter->second > numOfTimes) {
                mostCommon = iter->first;
                numOfTimes = iter->second;
            } 
        }
        return mostCommon;
    }


};

class SolutionAtoi {
public:
    bool isRelaventInt(char input) {
        char plus = '+';
        char negative = '-';
        char decimal = '.';
        char zero = 30;
        char nine = 39;
        if (input <= nine ||
            input >= zero ||
            input == plus ||
            input == negative ||
            input == decimal) 
            return true;
        return false;
    }

    int myAtoi(string s) {
        char whitespace = ' ';
        char plus = '+';
        char negative = '-';
        char decimal = '.';

        bool isNegative = false;

        int i = 0;
        while (isRelaventInt(s.at(i))) {
            if (i < s.size() && isRelaventInt(s.at(i + 1))) {
                if (s.at(i) == negative) isNegative = true;

                // We have a number


            }


            i++;
        }
        return 0;
    }
};

/*
    vector<int> twoSum(vector<int>& nums, int target) {

        vector<NumsSorted> sorted;
        for (int i = 0; i < nums.size(); i++) {
            NumsSorted* temp = new NumsSorted;
            temp->number = nums.at(i);
            temp->originalIndex = i;
            sorted.push_back(temp);
        }
        std::sort(sorted.begin(), sorted.end(), compareLess);

        int frontPointer = 0;
        int backPointer = nums.size() -1;
        int sum = 0;
        vector<int> result;
        int resultArray[2];

        while (frontPointer != backPointer) {
            sum = sorted.at(frontPointer).number + sorted.at(backPointer).number;
            if (sum == target) {
                result.push_back(sorted.at(frontPointer).originalIndex);
                result.push_back(sorted.at(backPointer).originalIndex);
                resultArray[0] = sorted.at(frontPointer).originalIndex;
                resultArray[1] = sorted.at(backPointer).originalIndex;
                break;
            } 
            else if (sum > target) {
                backPointer--;
            }
            else if (sum < target) {
                frontPointer++;
            }
        }
        return result;
    }
    */