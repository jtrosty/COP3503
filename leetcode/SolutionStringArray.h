#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <stack>

using std::string;
using std::unordered_map;
using std::vector;
using std::set;
using std::pair;
using std::stack;

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