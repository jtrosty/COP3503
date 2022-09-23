#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'numberOfItems' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. STRING s  ****||***
 *  2. INTEGER_ARRAY startIndices
 *  3. INTEGER_ARRAY endIndices
 */
 struct Container {
     int numOfItems;
     int startIndex;
     int endIndex;
 }

vector<int> numberOfItems(string s, vector<int> startIndices, vector<int> endIndices) {
    stack<char> compartmentStack;
    vector<int> result;
    for (int i = 0; i < startIndices.size(); i++) {
        int counter = 0;
        int currResult = 0;
        bool boundary = false;
        for (int j = startIndices.at(i) - 1; j <= endIndices.at(i) - 1; j++) {
            if (s.at(j) == '|'  && !boundary) {
                boundary = true;
            } 
            else if (s.at(j) == '|' && boundary) {
                currResult += counter;
                counter = 0;
            }
            else if (s.at(j) == '*' && boundary) {
                counter++;
            }
        }
        result.push_back(currResult);
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string startIndices_count_temp;
    getline(cin, startIndices_count_temp);

    int startIndices_count = stoi(ltrim(rtrim(startIndices_count_temp)));

    vector<int> startIndices(startIndices_count);

    for (int i = 0; i < startIndices_count; i++) {
        string startIndices_item_temp;
        getline(cin, startIndices_item_temp);

        int startIndices_item = stoi(ltrim(rtrim(startIndices_item_temp)));

        startIndices[i] = startIndices_item;
    }

    string endIndices_count_temp;
    getline(cin, endIndices_count_temp);

    int endIndices_count = stoi(ltrim(rtrim(endIndices_count_temp)));

    vector<int> endIndices(endIndices_count);

    for (int i = 0; i < endIndices_count; i++) {
        string endIndices_item_temp;
        getline(cin, endIndices_item_temp);

        int endIndices_item = stoi(ltrim(rtrim(endIndices_item_temp)));

        endIndices[i] = endIndices_item;
    }

    vector<int> result = numberOfItems(s, startIndices, endIndices);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'minimalHeaviestSetA' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY arr as parameter.
do not need to use all weights,
Some weights can be used again.
a can only be size 2. 
be just has to be less. 
this is like two sum
// maybe sort the array
2, 3, 5, 6, 7 
a 7 - 7
b 2,3,5 - 10
a 6,7 - 13 - 23

1 2 2 3 4 5 - sum is 17
A 5 4 - 9
B -Target 8, 1 2 2 3 -8

 */

vector<int> minimalHeaviestSetA(vector<int> arr) {
    int sizeArr = arr.size(); // 5
    if (sizeArr == 1) return arr;
    
    int sumOfArr = 0; // 23 in example
    for (int i = 0; i < sizeArr; i++) {
        sumOfArr += arr.at(i);
    }
    int halfOfArr = sumOfArr / 2;
    sort(arr.begin(), arr.end());
    int ptrA = sizeArr - 1;
    int ptrB = 0;
    
    
    int sumA = 0;
    vector<int> indexOfA;
    while (sumA < halfOfArr + 1) {
        sumA += arr.at(ptrA);
        indexOfA.push_back(ptrA);
        ptrA--;
    }
    int target = sumOfArr - sumA;
    int sumB = 0;
    while (sumB != target) {
        sumB += arr.at(ptrB);
        ptrB++;
    }
    vector<int> result; 
    for (int i = 0; i < indexOfA.size(); i++) {
        result.push_back(arr.at(indexOfA.at(indexOfA.size() - 1 - i)));
    }
    return result;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string arr_count_temp;
    getline(cin, arr_count_temp);

    int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

    vector<int> arr(arr_count);

    for (int i = 0; i < arr_count; i++) {
        string arr_item_temp;
        getline(cin, arr_item_temp);

        int arr_item = stoi(ltrim(rtrim(arr_item_temp)));

        arr[i] = arr_item;
    }

    vector<int> result = minimalHeaviestSetA(arr);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

