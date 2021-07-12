#include "Shapes.h"

/* ************************************************
******************** SHAPE 2D *********************
***************************************************/
bool Shape2D::operator>(const Shape2D& rhs) const {
    if (this->Area() > rhs.Area()) return true;
    else return false;
}

bool Shape2D::operator<(const Shape2D& rhs) const {
    if (this->Area() < rhs.Area()) return true;
    else return false;
}

bool Shape2D::operator==(const Shape2D& rhs) const {
    if (this->Area() == rhs.Area()) return true;
    else return false;
}

void Shape2D::ShowArea() const {
    cout << Area() << endl;
}

/* ************************************************
******************** SHAPE 3D *********************
***************************************************/
bool Shape3D::operator>(const Shape3D& rhs) const {
    if (this->Volume() > rhs.Volume()) return true;
    else return false;
}

bool Shape3D::operator<(const Shape3D& rhs) const {
    if (this->Volume() < rhs.Volume()) return true;
    else return false;
}

bool Shape3D::operator==(const Shape3D& rhs) const {
    if (this->Volume() == rhs.Volume()) return true;
    else return false;
}

void Shape3D::ShowVolume() const {
    cout << Volume() << endl;
}

/* ************************************************
******************** Square ***********************
***************************************************/
Square::Square() {
    sideLength = 0.0f;
}

Square::Square(float _sideLength) {
    sideLength = _sideLength;
}

// Behavior
void Square::Scale(float _scaleFactor) {
    sideLength *= _scaleFactor;
}

void Square::Display() const {
    cout << "The area of the Square is: " << Area() << endl;
    cout << "Length of a side: " << sideLength << endl;
}

float Square::Area() const {
    return (sideLength * sideLength);
}

string Square::GetName2D() const {
    return "Square";
}

/* ************************************************
******************** Triangle *********************
***************************************************/
// Constructors
Triangle::Triangle() {
    baseLength = 0.0f;
    heigth = 0.0f;
}

Triangle::Triangle(float _baseLength, float _height) {
    baseLength = _baseLength;
    heigth = _height;
}

// Behavior
void Triangle::Scale(float _scaleFactor) {
    baseLength *= _scaleFactor;
    heigth *= _scaleFactor;
}

void Triangle::Display() const {
    cout << "The area of the Triangle is: " << Area() << endl;
    cout << "Base: " << baseLength << endl;
    cout << "Height: " << heigth << endl;
}

float Triangle::Area() const {
    return (0.5f * (baseLength * heigth));
}

string Triangle::GetName2D() const {
    return "Triangle";
}

/* ************************************************
******************** Circles **********************
***************************************************/
// Constructors
Circle::Circle() {
    radius = 0.0f;
}

Circle::Circle(float _radius) {
    radius = _radius;
}

// Behavior
void Circle::Scale(float _scaleFactor) {
    radius *= _scaleFactor;
}

void Circle::Display() const {
    cout << "The area of the Circle is: " << Area() << endl;
    cout << "Radius: " << radius << endl;
}

float Circle::Area() const {
    return (PI * (radius * radius));
}

string Circle::GetName2D() const {
    return "Circle";
}

/* ************************************************
**************** Trianglular Pyramid **************
***************************************************/
// Constructors
TriangularPyramid::TriangularPyramid() 
        : Triangle() {
    pyramidHeight = 0.0f;
}

TriangularPyramid::TriangularPyramid(float _pyramidHeight, float _triangleHeight, float _triangleBase)
        : Triangle(_triangleBase, _triangleHeight) {
    pyramidHeight = _pyramidHeight;
}

// Behavior
void TriangularPyramid::Scale(float _scaleFactor) {
    pyramidHeight *= _scaleFactor;
    Triangle::Scale(_scaleFactor);
}

void TriangularPyramid::Display() const {
    cout << "The Volume of the Pyramid is: " << Volume() << endl;
    cout << "height is: " << pyramidHeight << endl;
    Triangle::Display();
}

float TriangularPyramid::Volume() const {
    return ((float) 1 / 3) * pyramidHeight * Triangle::Area();
}

string TriangularPyramid::GetName3D() const {
    return "Triangular Pyramid";
}