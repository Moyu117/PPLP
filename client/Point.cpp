#include "Point.h"
#include "DrawVisitor.h"
#include "SauvegardeVisitor.h"
#include "Transformation.h"
#include <sstream>

Point::Point(const Vecteur2D& pos, const std::string& couleur)
    : Forme(couleur), position(pos)
{}

Point::~Point() {}

double Point::aire() const {
    // surface de point = 0
    return 0.0;
}

void Point::dessiner(DrawVisitor& visitor) const {
    visitor.visit(*this);
}

void Point::sauvegarder(SauvegardeVisitor& visitor) const {
    visitor.visit(*this);
}

void Point::appliquerTransformation(const Transformation& t) {
    t.appliquer(*this);
}

Point::operator std::string() const {
    std::ostringstream oss;
    oss << "Point [couleur=" << couleur
        << ", pos=" << (std::string)position << "]";
    return oss.str();
}
