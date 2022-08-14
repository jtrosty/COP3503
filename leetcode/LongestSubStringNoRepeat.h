#include <string>
#include <set>
#include <vector>

using std::string;
using std::set;
using std::vector;

class Solution {
public:
    struct Substring {
        int start = 0;
        int end = 0;
        int length = 1;
    };

    bool isLongestSubstring(Substring& currentSubString, Substring& longestSubstring) {
        if (currentSubString.length > longestSubstring.length) return true;
        return false;
    }

    void resetSubstring(Substring& subString, int index) {
                    subString.start = index;
                    subString.end = index;
                    subString.length = 0;
    }

    void transferSubString(Substring& currentSubString, Substring& longestSubString, int index) {
                    longestSubString.start = currentSubString.start;
                    longestSubString.end = currentSubString.end;
                    longestSubString.length = currentSubString.length;
    }

    int lengthOfLongestSubstring(string s) {
        set<char> usedLetters;
        Substring longestSubString;
        Substring currentSubString;
        
        usedLetters.insert(s.at(0));

        for (int i = 1; i < s.size(); i++) {
            if (usedLetters.count(s.at(i))) {
                if (isLongestSubstring(currentSubString, longestSubString)) {
                    transferSubString(currentSubString, longestSubString, i);
                    resetSubstring(currentSubString, i);
                }
                else {
                    resetSubstring(currentSubString, i);
                    usedLetters.clear();
                }
            }
            else {
                usedLetters.insert(s.at(i));
                currentSubString.end++;
                currentSubString.length = usedLetters.size();
            }
        }
        if (isLongestSubstring(currentSubString, longestSubString)) {
            currentSubString.length = usedLetters.size();
            transferSubString(currentSubString, longestSubString, s.length() - 1);
        }
        return longestSubString.length;
    }
};