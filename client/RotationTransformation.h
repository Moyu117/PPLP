#ifndef ROTATIONTRANSFORMATION_H
#define ROTATIONTRANSFORMATION_H

#include "Transformation.h"
#include "Vecteur2D.h"
#include <cmath>

class RotationTransformation : public Transformation {
private:
    Vecteur2D center; // 旋转中心
    double angleRad;  // 旋转角度（弧度）
public:
    RotationTransformation(const Vecteur2D& center, double angleDeg);

    void appliquer(Point& p) const override;
    void appliquer(Segment& s) const override;
    void appliquer(Polygone& p) const override;
    void appliquer(Groupe& g) const override;
};

#endif
