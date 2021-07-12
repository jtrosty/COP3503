#include <string>
#include <iostream>
#define PI 3.14159f

using std::cout;
using std::endl;
using std::string;

class Shape {
    public:
        virtual void Scale(float scaleFactor) = 0;
        virtual void Display() const = 0;

};

class Shape2D {
    public:
        virtual float Area() const = 0;
        void ShowArea() const;
        virtual string GetName2D() const = 0;
        bool operator>(const Shape2D& rhs) const;
        bool operator<(const Shape2D& rhs) const;
        bool operator==(const Shape2D& rhs) const;
};

class Square : public Shape2D {
    float sideLength;
    public:
    // Constructors
    Square();
    Square(float _sideLenght);

    void Scale(float scale);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Triangle : public Shape2D {
    protected:
        float baseLength;
        float heigth;
    public:
        // Constructors
        Triangle();
        Triangle(float _baseLength, float _height);

        void Scale(float scale);
        void Display() const;
        float Area() const;
        string GetName2D() const;
};

class Circle : public Shape2D {
    float radius;
    public:
    // Constructors
    Circle();
    Circle(float _radius);

    void Scale(float scale);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Shape3D {
    public:
        virtual float Volume() const = 0;
        void ShowVolume() const;
        virtual string GetName3D() const = 0;
        bool operator>(const Shape3D& rhs) const;
        bool operator<(const Shape3D& rhs) const;
        bool operator==(const Shape3D& rhs) const;
};

class TriangularPyramid : virtual private Triangle, public Shape3D {
    double pyramidHeight;

    public:
    // Constructors
    TriangularPyramid();
    TriangularPyramid(float _pyramidHeight, float _triangleHeight, float _triangleBase);

    void Scale(float scale);
    void Display() const;
    float Volume() const;
    string GetName3D() const;

};

/*

class Cylinder : public Circle, public Shape3D {
    double height; 

};

class Sphere : public Circle, public Shape3D {

};
*/