#include "Vecteur2D.h"
#include <cstdio> // sscanf

Vecteur2D::Vecteur2D(double x, double y) : x(x), y(y) {}

Vecteur2D::Vecteur2D(const char* s) {
    //  "( x, y )"
    sscanf(s, "(%lf,%lf)", &x, &y);
}

Vecteur2D Vecteur2D::operator+(const Vecteur2D& u) const {
    return Vecteur2D(x + u.x, y + u.y);
}

Vecteur2D Vecteur2D::operator*(double a) const {
    return Vecteur2D(x * a, y * a);
}

Vecteur2D Vecteur2D::operator-() const {
    return Vecteur2D(-x, -y);
}

Vecteur2D::operator std::string() const {
    std::ostringstream os;
    os << "(" << x << ", " << y << ")";
    return os.str();
}

std::ostream& operator<<(std::ostream& os, const Vecteur2D& u) {
    os << (std::string)u;
    return os;
}

double Vecteur2D::determinant(const Vecteur2D& u, const Vecteur2D& v) {
    return u.x * v.y - u.y * v.x;
}
