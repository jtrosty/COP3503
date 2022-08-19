#include <string>
using std::string;

class SolutionLongestPalindrome {
public:
    struct Palindrome {
        int start;
        int end;
        int size;
    };

    bool updateIfLongestPalindrome(Palindrome& longestPalindrome, int start, int end) {
        int sizeOfNewPalindrome = end - start + 1;
        if ((sizeOfNewPalindrome) > longestPalindrome.size) {
            longestPalindrome.start = start;
            longestPalindrome.end = end;
            longestPalindrome.size = sizeOfNewPalindrome;
            return true;
        }
        return false;
    }

    string longestPalindrome(string s) {
        // Strategy: find the center of a palindrome
        int size = s.size();

        if (size <= 1) return s;
        Palindrome longestPalindrome;
        longestPalindrome.start = 0;
        longestPalindrome.end = 1;
        longestPalindrome.size = 1;
        if (size == 2) {
            if (s.at(0) == s.at(1)) return s;
        }


        // The center of a plindrome can't start at 1
        for (int i = 1; i < size; i++) {
            // Case if Palindrome size is odd.
            if ((i < (size - 1)) && (s.at(i - 1) == s.at(i + 1))) {
                //  We have the start of a palindrome
                updateIfLongestPalindrome(longestPalindrome, i-1, i+1);
                int numIndexesToCheck = 0;
                if (i - 1 < (size - 1 - (i + 1))) numIndexesToCheck = i - 1;
                else                    numIndexesToCheck = (size - 1 - (i + 1));

                for (int j = 0; j < numIndexesToCheck; j++) {
                    int begin = i - j -2;
                    int end = i + j + 2;
                    if (s.at(begin) == s.at(end)) {
                        updateIfLongestPalindrome(longestPalindrome, begin, end);
                    }
                    else break;
                }
            }
            // case if Palindrome size is even
            if (s.at(i - 1) == s.at(i)) {
                updateIfLongestPalindrome(longestPalindrome, i-1, i);
                int numIndexesToCheck = 0;
                if (size - i - 1 > (i - 1)) numIndexesToCheck = i - 1;
                else                    numIndexesToCheck = size - i - 1;

                for (int j = 0; j < numIndexesToCheck; j++) {
                    int begin = i - j - 2;
                    int end = i + j + 1;
                    if (s.at(begin) == s.at(end)) {
                        updateIfLongestPalindrome(longestPalindrome, begin, end);
                    }
                    else break;
                }

            }
        }
        
        if (longestPalindrome.size == 0) return s.substr(0, 0);
        return s.substr(longestPalindrome.start, longestPalindrome.size);
    }
};