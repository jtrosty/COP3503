#include <string>
#include <unordered_map>
#include <vector>
#include <set>

using std::string;
using std::unordered_map;
using std::vector;
using std::set;

class SolutionReorderLogFiles {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        
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