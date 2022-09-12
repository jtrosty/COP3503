
#include "../othello.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test case for Othello", "[insert]"){
    vector<vector<int>> testBoard {     {'b', 0 ,  0 , 0 ,  0 ,  0 ,  0 ,  0 },
                                        {'b','w',  0 , 'b', 'b', 'b' , 'b','b'},   
                                        {'b','w',  0,  'b', 'w', 'w', 'w', 'b'},
                                        { 0,  0 ,  0 , 'b', 'w',  0 , 'w', 'b'},
                                        { 0,  0 ,  0 , 'b', 'w', 'w', 'w', 'b'},
                                        { 0,  0 ,  0 , 'b', 'b', 'b' ,'b', 'b'},
                                        { 0,  0 ,  0 , 'b', 'b', 'b', 'b', 'w'},
                                        {'b','w', 'w','w', 'w', 'w', 'w', 0 } };

    REQUIRE(howManyPiecesFlip('b', 2, 2, testBoard) == 2);
    REQUIRE(howManyPiecesFlip('w', 1, 0, testBoard) == 0);
    REQUIRE(howManyPiecesFlip('b', 3, 2, testBoard) == 1);
    REQUIRE(howManyPiecesFlip('b', 7, 7, testBoard) == 7);
    REQUIRE(howManyPiecesFlip('b', 3, 7, testBoard) == 0);
    REQUIRE(howManyPiecesFlip('b', 5, 5, testBoard) == 0);
    REQUIRE(howManyPiecesFlip('b', 3, 5, testBoard) == 8);

}
