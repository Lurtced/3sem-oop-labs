#pragma once
#include "Shape.h"
#include "MyVector.h"

class Circle : public Shape {
private:
    Vector ptCntr;
    double R;

public:
    Circle();
    Circle(Vector& cntr, double r);
    Circle(double x, double y, double r);

    void Move(Vector& v) override;
    void Out() override;
    double Area() override;
};