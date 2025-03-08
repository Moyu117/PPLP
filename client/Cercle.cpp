#include "Cercle.h"
#include "DrawVisitor.h"
#include "SauvegardeVisitor.h"
#include "Transformation.h"
#include <sstream>
#include <cmath>

Cercle::Cercle(const Vecteur2D& c, double r, const std::string& couleur)
    : Forme(couleur), centre(c), rayon(r) {}

double Cercle::aire() const {
    return 3.1415926 * rayon * rayon; // πr²
}

void Cercle::dessiner(DrawVisitor& visitor) const {
    visitor.visit(*this);
}

void Cercle::sauvegarder(SauvegardeVisitor& visitor) const {
    visitor.visit(*this);
}

void Cercle::appliquerTransformation(const Transformation& t) {
    t.appliquer(*this);
}

Cercle::operator std::string() const {
    std::ostringstream oss;
    oss << "Cercle [couleur=" << couleur
        << ", centre=" << (std::string)centre
        << ", rayon=" << rayon << "]";
    return oss.str();
}
