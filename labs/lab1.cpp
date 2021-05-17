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
    bool run = true;
    string title;
    vector<string> colData1(0);
    vector<int> colData2(0);
    string userInput;

    // Get title
    cout << "Enter a title for the data:" << endl;
    getline(cin, title);
    cout << "You Entered: " << title << endl;

    // Prompt user for headers of 2 coloums
    string colHeader1;
    string colHeader2;
    // Header 1
    cout << "Enter the colum 1 header: " << endl;
    getline(cin, colHeader1);
    cout << "You entered: " << colHeader1 << endl;
    // header 2 
    cout << "Enter the colum 2 header: " << endl;
    getline(cin, colHeader2);
    cout << "You entered: " << colHeader2 << endl;

    while (run) {

        int comma;

        // Test if user input is valid
        try { 
            cout << "Enter a data point (-1 to stop input):" << endl;
            getline(cin, userInput);

            // Break if -1
            if (userInput == "-1") break;

            // Check for first Comma
            if (comma = userInput.find(',') && (userInput.find(',') == string::npos)) {
                throw runtime_error("No comma.");
            }
            cout << "comma " << comma << endl; 
            // If first comma check good,add string to colData1 
            colData1.push_back(userInput.substr(0, comma));

            // Check if there are too many commas
            if (userInput.rfind(',') == comma) {
                throw runtime_error("Too many commas in input.");
            }
        }
        catch(runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch(invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
        }

        // Attempt to convert the part of string after 1 comma to int.
        int intData = stoi(userInput.substr(comma, string::npos));

        // If Int succeded, add int data to colData2
        colData2.push_back(intData);
        /*
        try {
            // Attempt to convert the part of string after 1 comma to int.
            int intData = stoi(userInput.substr(comma, string::npos));

            // If Int succeded, add int data to colData2
            colData2.push_back(intData);
        }
        catch(invalid_argument& e) {
            cout << "Error: " << "Comma not followed by an integer." << endl;
        }
        */
    }

    // Display data as a table
    // Title
    cout << setw(33) << right << title << endl;
    // column titles
    cout << setw(20) << left << colHeader1 << "|";
    cout << setw(23) << right << colHeader2 << endl;
    // -------------------------------------
    cout << setfill('-') << setw(53) << "" << endl;
    cout << setfill(' '); // reset fill character back to space. 
    // Table Data 
    // colData1 (string) left justified, | colData2 (int) number right justified
    // Breat of The Wild      |               10
    int sizeTable = colData1.size();
    cout << sizeTable << endl;
    for (int i = 0; i < sizeTable; ++i) {
        cout << setw(20) << left << colData1.at(i) << "|";
        cout << setw(23) << right << colData2.at(i) << endl;
    }
    
    // Histogram Looks like:
    // colData1 (string) colData2 Int (int # of starts)
    //           String ****************
    for (int i = 0; i < sizeTable; ++i) {
        cout << setw(20) << right << colData1.at(i) << " ";
        cout << setfill('*') << setw(colData2.at(i)) << "" << endl;
        cout << setfill(' ');
    }

    return 0;
}
