#include "Segment.h"
#include "DrawVisitor.h"
#include "SauvegardeVisitor.h"
#include "Transformation.h"
#include <sstream>

Segment::Segment(const Vecteur2D& p1, const Vecteur2D& p2, const std::string& couleur)
    : Forme(couleur), p1(p1), p2(p2)
{}

Segment::~Segment() {}

double Segment::aire() const {
    // point = 0
    return 0.0;
}

void Segment::dessiner(DrawVisitor& visitor) const {
    visitor.visit(*this);
}

void Segment::sauvegarder(SauvegardeVisitor& visitor) const {
    visitor.visit(*this);
}

void Segment::appliquerTransformation(const Transformation& t) {
    t.appliquer(*this);
}

Segment::operator std::string() const {
    std::ostringstream oss;
    oss << "Segment [couleur=" << couleur
        << ", p1=" << (std::string)p1
        << ", p2=" << (std::string)p2 << "]";
    return oss.str();
}
