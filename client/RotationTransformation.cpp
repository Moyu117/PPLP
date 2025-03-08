#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "RotationTransformation.h"
#include "Point.h"
#include "Segment.h"
#include "Polygone.h"
#include "Groupe.h"
#include "Cercle.h"

RotationTransformation::RotationTransformation(const Vecteur2D& c, double angleDeg)
    : center(c), angleRad(angleDeg* M_PI / 180.0) {}  // angle

// **rotation point**
void RotationTransformation::appliquer(Point& p) const {
    Vecteur2D pos = p.getPosition();
    double x = pos.x - center.x;
    double y = pos.y - center.y;

    double newX = x * cos(angleRad) - y * sin(angleRad);
    double newY = x * sin(angleRad) + y * cos(angleRad);

    p.setPosition(Vecteur2D(center.x + newX, center.y + newY));
}

// **rotation ligne**
void RotationTransformation::appliquer(Segment& s) const {
    s.setP1(Vecteur2D(
        center.x + (s.getP1().x - center.x) * cos(angleRad) - (s.getP1().y - center.y) * sin(angleRad),
        center.y + (s.getP1().x - center.x) * sin(angleRad) + (s.getP1().y - center.y) * cos(angleRad)
    ));

    s.setP2(Vecteur2D(
        center.x + (s.getP2().x - center.x) * cos(angleRad) - (s.getP2().y - center.y) * sin(angleRad),
        center.y + (s.getP2().x - center.x) * sin(angleRad) + (s.getP2().y - center.y) * cos(angleRad)
    ));
}

// **rotation poly**
void RotationTransformation::appliquer(Polygone& poly) const {
    auto& pts = poly.getPoints();
    for (auto& pt : pts) {
        double x = pt.x - center.x;
        double y = pt.y - center.y;
        double newX = x * cos(angleRad) - y * sin(angleRad);
        double newY = x * sin(angleRad) + y * cos(angleRad);
        pt = Vecteur2D(center.x + newX, center.y + newY);
    }
}

void RotationTransformation::appliquer(Cercle& c) const {
    Vecteur2D centre = c.getCentre();
    double x = centre.x - this->center.x;
    double y = centre.y - this->center.y;
    double newX = x * cos(angleRad) - y * sin(angleRad);
    double newY = x * sin(angleRad) + y * cos(angleRad);
    c.setCentre(Vecteur2D(this->center.x + newX, this->center.y + newY));
}



// **rotation group**
void RotationTransformation::appliquer(Groupe& g) const {
    for (auto f : g.getFormes()) {
        f->appliquerTransformation(*this);
    }
}
