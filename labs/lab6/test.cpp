#include <iostream>
#include "Shapes.h"

int main(void) {
    Square zeroSquare;
    Square twoSquare(5.0f);
    zeroSquare.Display();

    twoSquare.GetName2D();
    twoSquare.Display();

    cout << (twoSquare > zeroSquare) << endl;
    cout << (twoSquare < zeroSquare) << endl;
    cout << (twoSquare == zeroSquare) << endl;

    TriangularPyramid test1;
    TriangularPyramid test2(2.0f, 2.0f, 2.0f);
    test1.Display();
    test2.Display();
    test2.Scale(3.0f);
    test2.Display();




    return 0;
}