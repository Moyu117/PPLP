#ifndef SCALETRANSFORMATION_H
#define SCALETRANSFORMATION_H

#include "Transformation.h"
#include "Vecteur2D.h"

class ScaleTransformation : public Transformation {
private:
    double scaleFactor; // Ëõ·Å±¶Êý
public:
    explicit ScaleTransformation(double scale) : scaleFactor(scale) {}

    void appliquer(Point& p) const override;
    void appliquer(Segment& s) const override;
    void appliquer(Polygone& p) const override;
    void appliquer(Groupe& g) const override;
};

#endif
