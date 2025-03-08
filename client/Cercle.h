#ifndef CERCLE_H
#define CERCLE_H

#include "Forme.h"
#include "Vecteur2D.h"
#include <string>

class Cercle : public Forme {
private:
    Vecteur2D centre;
    double rayon;

public:
    Cercle(const Vecteur2D& c, double r, const std::string& couleur = "black");

    double aire() const override;
    void dessiner(DrawVisitor& visitor) const override;
    void sauvegarder(SauvegardeVisitor& visitor) const override;
    void appliquerTransformation(const Transformation& t) override;

    operator std::string() const override;

    //set
    const Vecteur2D& getCentre() const { return centre; }
    double getRayon() const { return rayon; }
    void setCentre(const Vecteur2D& c) { centre = c; }
    void setRayon(double r) { rayon = r; }
};

#endif
