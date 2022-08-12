#include <string>
#include <set>

using std::string;
using std::set;

class Solution {
public:
    struct Substring {
        int start = 0;
        int end = 0;
        int length = 0;
    };

    int lengthOfLongestSubstring(string s) {
        set<char> usedLetters;
        Substring longestSubString;
        Substring currentSubString;

        for (int i = 0; i < s.size(); i++) {
            if (usedLetters.count(s.at(i))) {

            }
        }
    }
};