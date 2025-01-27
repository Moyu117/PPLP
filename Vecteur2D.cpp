#include "Vecteur2D.h"
#include <cstdio>

Vecteur2D::Vecteur2D(double x, double y) : x(x), y(y) {}

Vecteur2D::Vecteur2D(const std::string& s) {
    // 关键修改：使用 sscanf_s 替代 sscanf
    sscanf_s(s.c_str(), "(%lf,%lf)", &x, &y);
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
    os << "(" << x << "," << y << ")";
    return os.str();
}