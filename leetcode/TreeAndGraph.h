#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <stack>
#include <queue>
#include <tuple>

using std::to_string;

class SolutionIslands {
public:
/*
    Input: grid = [
    ["1","1","1","1","0"],
    ["1","1","0","1","0"],
    ["1","1","0","0","0"],
    ["0","0","0","0","0"]
    ]
    Output: 1

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'.

    So a breath first search would solve this. Go through 
*/
    int searchIslands(vector<vector<char>>& grid, set<string>& visited, int i, int j) {
        int numOfRows = grid.size();
        int numOfCols = grid.at(0).size();
        if (i == numOfRows || j == numOfCols) return 0;

        string indexes = to_string(i);
        indexes.append(to_string(j));
        if (visited.count(indexes)) {
            return 0;
        }
        else if (grid.at(i).at(j) == '1' ) {
            visited.emplace(indexes);
            if (numOfCols == 1 && numOfRows == 1) {
                if (grid.at(i).at(j) == '1') return 1;
                else return 0;
            }
            else if (numOfRows == 1) {
                searchIslands(grid, visited, i, j + 1);
            }
            else if (numOfCols == 1) {
                searchIslands(grid, visited, i + 1, j);
            }
            else if (i == 0 && j == 0) {
                searchIslands(grid, visited, i + 1, j);
                searchIslands(grid, visited, i, j + 1);
            }
            else if ((i == numOfRows - 1) && j == 0) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j + 1);
            }
            else if (i == 0 && (numOfCols -1) == j) {
                searchIslands(grid, visited, i, j - 1);
                searchIslands(grid, visited, i + 1, j);
            }
            else if ((i == numOfRows - 1) && (numOfCols -1) == j) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j - 1);
            }
            else if (i == 0) {
                searchIslands(grid, visited, i + 1, j);
                searchIslands(grid, visited, i, j + 1);
                searchIslands(grid, visited, i, j - 1);
            }
            else if (i == numOfRows -1) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j + 1);
                searchIslands(grid, visited, i, j - 1);
            }
            else if (j == 0) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j + 1);
                searchIslands(grid, visited, i + 1, j);
            }
            else if (j == numOfCols -1) {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i, j - 1);
                searchIslands(grid, visited, i + 1, j);
            } else {
                searchIslands(grid, visited, i - 1, j);
                searchIslands(grid, visited, i + 1, j);
                searchIslands(grid, visited, i, j - 1);
                searchIslands(grid, visited, i, j + 1);
            }
        }
        return 1;
    }

    int numIslands(vector<vector<char>>& grid) {
        set<string> visited;
        int numOfRows = grid.size();
        int numOfCols = grid.at(0).size(); 
        int result = 0;

        for (int i = 0; i < numOfRows; i++) {
            for (int j = 0; j < numOfCols; j++) {
                if (grid.at(i).at(j) == '1') {
                    // Begin BFS
                    result += searchIslands(grid, visited, i, j);
                }
            }
        }
        return result;
    }
};