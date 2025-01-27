#pragma once
#include <string>
#include <sstream>

class Vecteur2D {
public:
    double x, y;
    explicit Vecteur2D(double x = 0, double y = 0);
    explicit Vecteur2D(const std::string& s);
    Vecteur2D operator+(const Vecteur2D& u) const;
    Vecteur2D operator*(double a) const;
    Vecteur2D operator-() const;
    operator std::string() const;
};