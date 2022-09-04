#include <vector>

using std::vector;

struct Tile {
	char occupied = 0;
    vector<Tile>* neighbors;
};
// char, 0 means empty, 1 is whilte, -1 is black

// 2,2, We know that there is a enemy piece at 2,3, We need to lookk at 2,5
// 2,2 and enemyat 3,3. We need look donw to 8,8
int checkTiles(int x, int y, int directionX, int directionY, char team, char enemyTile, vector<vector<int>>& board) {
    int boardSize = board.size() - 1;
    int furtherTiles = 0;
  
  	if (x >= 0 && x <= boardSize && y >= 0 && y <= boardSize) {
        x += directionX;
        y += directionY;
    }
    int tile = board.at(x).at(y);
    if (tile == enemyTile) {
      furtherTiles = checkTiles(x, y, directionX, directionY, team, enemyTile, board);
      if (furtherTiles < 0) {
        return -1;
      }
      else {
        return 1 + furtherTiles;
      }
    }
    else {
      return -1;
    }
      
      /*
  	while (nextTile->occupied != 0 &&
            x >= 0 && x <= boardSize && y >= 0 && y <= boardSize) {
        x += directionX;
        y += directionY;
        if (nextTile->occupied == enemyTile) {
            count++;
        }
      	else if (nextTile->occupied == team) {
            // We have reached ours
           result += count;
           break;
        }
      	else {
          break;
        }
    }
  	return result;
    */
}

int howManyPiecesFlip(char team, int x, int y, vector<vector<int>>& board) {
  	int* currentTile = &(board.at(x).at(y));
  	char enemyTile;
    int result = 0;
  
  	if (team == 1) enemyTile = -1;
  	else enemyTile = 1;
  
  	// At the edge or not. 
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            result += checkTiles(x, y, i, j, team, enemyTile, board); 
        }
    }
    return result;
}