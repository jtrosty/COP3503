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
        virtual ~Shape();
};

class Shape2D : virtual public Shape {
    public:
        virtual float Area() const = 0;
        void ShowArea() const;
        virtual string GetName2D() const = 0;
        bool operator>(const Shape2D& rhs) const;
        bool operator<(const Shape2D& rhs) const;
        bool operator==(const Shape2D& rhs) const;
};

class Square : virtual public Shape2D {
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

class Triangle : virtual public Shape2D {
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

class Circle : virtual public Shape2D {
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

class Shape3D : virtual public Shape {
    public:
        virtual float Volume() const = 0;
        void ShowVolume() const;
        virtual string GetName3D() const = 0;
        bool operator>(const Shape3D& rhs) const;
        bool operator<(const Shape3D& rhs) const;
        bool operator==(const Shape3D& rhs) const;
};

class TriangularPyramid : private Triangle, public Shape3D {
    float pyramidHeight;

    public:
    // Constructors
    TriangularPyramid();
    TriangularPyramid(float _pyramidHeight, float _triangleHeight, float _triangleBase);

    void Scale(float scale);
    void Display() const;
    float Volume() const;
    string GetName3D() const;

};


class Cylinder : private Circle, public Shape3D {
    double height; 

    public:
    // Constructors
    Cylinder();
    Cylinder(float _height, float _radius);

    void Scale(float _scale);
    void Display() const;
    float Volume() const;
    string GetName3D() const;
};

class Sphere : private Circle, public Shape3D {
    float radius;

    public:
    // Constructor
    Sphere();
    Sphere(float _radius);

    void Scale(float _scale);
    void Display() const;
    float Volume() const;
    string GetName3D() const;
};