#include "Circle.h"
#include <iostream>

Circle::Circle() : ptCntr(0, 0), R(1) {}

Circle::Circle(Vector& cntr, double r) : ptCntr(cntr), R(r > 0 ? r : 0) {}

Circle::Circle(double x, double y, double r) :
    ptCntr(x, y), R(r > 0 ? r : 0) {}

void Circle::Move(Vector& v) {
    ptCntr = ptCntr + v;
}

void Circle::Out() {
    std::cout << "Circle: center=("
        << ptCntr.GetX() << ", " << ptCntr.GetY()
        << "), radius=" << R << std::endl;
}

double Circle::Area() {
    return 3.14159 * R * R;
}