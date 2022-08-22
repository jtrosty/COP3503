#include <string>
#include <unordered_map>
#include <vector>
#include <set>

using std::string;
using std::unordered_map;
using std::vector;
using std::set;

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