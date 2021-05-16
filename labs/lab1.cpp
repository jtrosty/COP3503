#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
   
   /* Type code here. */
   /* Overall flow of the program:
   Get some input for the title
   Get some input for column header #1
   Get some input for column header #2
   
   Until the user types "-1":
   Get input for a string
   Validate input
   If valid...
      Split
      Validate second half of input
      If also valid...
         Store separate pieces
   
   Print out data in table format
   
   Print out data in chart format
   Notes from stff:
   1. getline(cin, stringVar) - gets all reamaining text on teh current input line. GETLINE DOEST NOT IGNORE LEADING WHITESPACE.
   2. cin does not go to the next line. must have empty getline with a blank variable to go to the next line.   
   3. #include <cctype> library, isalpha, isdigit, isspace, tolower, toupper
   4. find(char or string), substr(index, length), push_back(c), insert(indx, subst), replace (indx, num, substr) CHECK OUT MORE AT C++ STRING LIBRARY!!!!
   */
    vector<int> yearList(4);
    yearList.at(0) = 1999;
    yearList.at(1) = 2000;
    yearList.at(2) = 2001;



    cout << "It worked\n";
   
   return 0;
}
