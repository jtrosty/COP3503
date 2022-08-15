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

    void transferSubString(Substring& currentSubString, Substring& longestSubString) {
                    longestSubString.start = currentSubString.start;
                    longestSubString.end = currentSubString.end;
                    longestSubString.length = currentSubString.length;
    }

    int lengthOfLongestSubstring(string s) {
        set<char> usedLetters;
        int lengthLongestSubstring = 0;

        
        if (s.size() == 0) return 0;
        if (s.size() == 1) return 1;
        
        int left = 0;
        int right = 0;
        while(left < s.size() && right < s.size()) {
            if (!usedLetters.count(s.at(right))) {
                usedLetters.emplace(s.at(right++));
            }
            else {
                
                while((s.at(left) != s.at(right)) && (left != right)) {
                    usedLetters.erase(s.at(left));
                    left++;
                }
                //usedLetters.erase(s.at(left));
                left++;
                right++;
            }
            if (usedLetters.size() > lengthLongestSubstring) {
                lengthLongestSubstring = usedLetters.size();
            }
        }
        return lengthLongestSubstring;
    }

    int lengthOfLongestSubstringSlow(string s) {
        set<char> usedLetters;
        Substring longestSubString;
        Substring currentSubString;
        
        if (s.size() == 0) return 0;
        if (s.size() == 1) return 1;
        
        for (int i = 0; i < s.size(); i++) {
            usedLetters.clear();
            usedLetters.emplace(s.at(i));
            resetSubstring(currentSubString, i);

            int subIndex;
            if ((i + 1) < s.size()) {
                subIndex = i + 1;
            }
            while (subIndex < s.size() && !usedLetters.count(s.at(subIndex))) {
                usedLetters.emplace(s.at(subIndex));
                currentSubString.end++;
                currentSubString.length = usedLetters.size();
                subIndex++;
            } 
            if (isLongestSubstring(currentSubString, longestSubString)) {
                currentSubString.length = usedLetters.size();
                transferSubString(currentSubString, longestSubString);
            }
        }
        return longestSubString.length;
    }
};