#ifndef ROTATIONTRANSFORMATION_H
#define ROTATIONTRANSFORMATION_H

#include "Transformation.h"
#include "Vecteur2D.h"
#include <cmath>

class RotationTransformation : public Transformation {
private:
    Vecteur2D center; //centre de rotation
    double angleRad;  // angle de rotation
public:
    RotationTransformation(const Vecteur2D& center, double angleDeg);

    void appliquer(Point& p) const override;
    void appliquer(Segment& s) const override;
    void appliquer(Polygone& p) const override;
    void appliquer(Cercle& p) const override;
    void appliquer(Groupe& g) const override;
};

#endif
