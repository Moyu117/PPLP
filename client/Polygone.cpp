#include "Polygone.h"
#include "DrawVisitor.h"
#include "SauvegardeVisitor.h"
#include "Transformation.h"
#include "Vecteur2D.h"
#include <sstream>
#include <cmath>

Polygone::Polygone(const std::vector<Vecteur2D>& pts, const std::string& couleur)
    : Forme(couleur), points(pts)
{}

Polygone::~Polygone() {}

double Polygone::aire() const {
    // 常见Shoelace Formula (卷线公式)
    double area = 0.0;
    int n = (int)points.size();
    if (n < 3) return 0.0;

    for (int i = 0; i < n; i++) {
        const Vecteur2D& p1 = points[i];
        const Vecteur2D& p2 = points[(i + 1) % n];
        area += (p1.x * p2.y - p1.y * p2.x);
    }
    area = std::fabs(area) * 0.5;
    return area;
}

void Polygone::dessiner(DrawVisitor& visitor) const {
    visitor.visit(*this);
}

void Polygone::sauvegarder(SauvegardeVisitor& visitor) const {
    visitor.visit(*this);
}

void Polygone::appliquerTransformation(const Transformation& t) {
    t.appliquer(*this);
}

Polygone::operator std::string() const {
    std::ostringstream oss;
    oss << "Polygone [couleur=" << couleur << ", points={";
    for (size_t i = 0; i < points.size(); i++) {
        if (i > 0) oss << ", ";
        oss << (std::string)points[i];
    }
    oss << "}]";
    return oss.str();
}
