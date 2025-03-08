#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "Transformation.h"
#include "Vecteur2D.h"

class Translation : public Transformation {
private:
    Vecteur2D deplacement;
public:
    explicit Translation(const Vecteur2D& dep) : deplacement(dep) {}

    void appliquer(Point& p) const override;
    void appliquer(Segment& s) const override;
    void appliquer(Polygone& p) const override;
    void appliquer(Groupe& g) const override;
    void appliquer(Cercle& c) const override;
};

#endif
