#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
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
   */

    // ****************** VARIABLES ****************************************
    string title = ""; // Title of table
    string userInput = ""; // Holds user input interation of while loop
    bool run = true;
    vector<string> colData1(0); // Holds string data, i of colData1 matched wiht i of colData2
    vector<int> colData2(0);

    // ***************** TITLE AND HEADERS FOR TABLE AND HISTOGRAM *********
    // Get title
    cout << "Enter a title for the data:" << endl;
    getline(cin, title);
    cout << "You entered: " << title << endl;

    // Prompt user for headers of 2 coloums
    string colHeader1;
    string colHeader2;
    // Header 1
    cout << "Enter the column 1 header:" << endl;
    getline(cin, colHeader1);
    cout << "You entered: " << colHeader1 << endl;
    // header 2 
    cout << "Enter the column 2 header:" << endl;
    getline(cin, colHeader2);
    cout << "You entered: " << colHeader2 << endl;


    // ******************** DATA INPUT WHILE LOOP **************************

    while (run) {
        int comma = -1;
        int intData = 0; 
        // Test if user inputs commas correctly
        try { 
            cout << "Enter a data point (-1 to stop input):" << endl;
            getline(cin, userInput);

            // Break if -1
            if (userInput == "-1"){
                run = false;
                break;   
            } 

            // Check for first Comma
            comma = userInput.find(','); 
            if ((userInput.find(',') == string::npos)) {
                throw runtime_error("No comma in string.");
            }

            // Check if there are too many commas
            if (userInput.rfind(',') != comma) {
                throw runtime_error("Too many commas in input.");
            }
        }
        catch(runtime_error& e) {
            cout << "Error: " << e.what() << endl;
            continue;
        }
        catch(invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            continue;
        }
        
        // tests if user has integer after the only comma
        try {
            // Attempt to convert the part of string after 1 comma to int.
            intData = stoi(userInput.substr(comma + 1, string::npos)); 
        } 
        catch (exception& e) {
            cout << "Error: Comma not followed by an integer." << endl;
            continue;
        }

        // If first comma check good,add string to colData1 
        colData1.push_back(userInput.substr(0, comma));
        // If a good int was pulled, add int data to colData2
        colData2.push_back(intData);
        cout << "Data string: " << userInput.substr(0, comma) << endl;
        cout << "Data integer: " << intData << endl;
    }

    // ****************** DRAW TABLE WITH DATA ***********************************
    // Display data as a table
    // Title
    cout << endl; // adds space between top of table to data entry section
    cout << setw(33) << right << title << endl;
    // column titles
    cout << setw(20) << left << colHeader1 << "|";
    cout << setw(23) << right << colHeader2 << endl;
    // -------------------------------------
    cout << setfill('-') << setw(44) << "" << endl;
    cout << setfill(' '); // reset fill character back to space. 
    // Table Data 
    // colData1 (string) left justified, | colData2 (int) number right justified
    // Breat of The Wild      |               10
    int sizeTable = colData1.size();
    for (int i = 0; i < sizeTable; ++i) {
        cout << setw(20) << left << colData1.at(i) << "|";
        cout << setw(23) << right << colData2.at(i) << endl;
    }
    
    // ****************** DRAW HISTOGRAM WITH DATA ***********************************
    // Histogram Looks like:
    // colData1 (string) colData2 Int (int # of starts)
    //           String ****************
    cout << endl; // adds space between top of table to data entry section
    for (int i = 0; i < sizeTable; ++i) {
        cout << setw(20) << right << colData1.at(i) << " ";
        cout << setfill('*') << setw(colData2.at(i)) << "" << endl;
        cout << setfill(' ');
    }
  
    return 0;
}
