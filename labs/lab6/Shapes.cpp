#include "Shapes.h"

/* ************************************************
************* BASE CLASS: SHAPE *******************
***************************************************/
// Virtual Destructor
Shape::~Shape(){}

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
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
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
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
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
TriangularPyramid::TriangularPyramid() {
    pyramidHeight = 0.0f;
}

TriangularPyramid::TriangularPyramid(float _pyramidHeight, float _triangleBase, float _triangleHeight)
        : Triangle(_triangleBase, _triangleHeight) {
    pyramidHeight = _pyramidHeight;
}

// Behavior
void TriangularPyramid::Scale(float _scaleFactor) {
    pyramidHeight *= _scaleFactor;
    Triangle::Scale(_scaleFactor);
}

void TriangularPyramid::Display() const {
    cout << "The volume of the TriangularPyramid is: " << Volume() << endl;
    cout << "The height is: " << pyramidHeight << endl;
    Triangle::Display();
}

float TriangularPyramid::Volume() const {
    return ((float) 1 / 3) * pyramidHeight * Triangle::Area();
}

string TriangularPyramid::GetName3D() const {
    return "TriangularPyramid";
}

/* ************************************************
******************** Cylinder *********************
***************************************************/
// Constructors
Cylinder::Cylinder() : Circle() {
    height = 0.0f;
}

Cylinder::Cylinder(float _height, float _radius) 
        : Circle(_radius) {
    height = _height;
}

void Cylinder::Scale(float _scale) {
    height *= _scale;
    Circle::Scale(_scale);
}

void Cylinder::Display() const {
    cout << "The volume of the Cylinder is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    Circle::Display();
}

float Cylinder::Volume() const {
    return (Circle::Area() * height);
}

string Cylinder::GetName3D() const {
    return "Cylinder"; 
}

/* ************************************************
********************** Sphere *********************
***************************************************/

Sphere::Sphere() : Circle() {
    radius = 0.0f;
}

Sphere::Sphere(float _radius) : Circle(_radius) {
    radius = _radius;
}

void Sphere::Scale(float _scale) {
    Circle::Scale(_scale);
}

void Sphere::Display() const {
    cout << "The volume of the Sphere is : " << Volume() << endl;
    Circle::Display();
}

float Sphere::Volume() const {
    return ((float) 4 / 3) * radius * (Circle::Area());
}

string Sphere::GetName3D() const {
    return "Sphere";
}