#ifndef SEGMENT_H
#define SEGMENT_H

#include "Forme.h"
#include "Vecteur2D.h"
#include <string>

class Segment : public Forme {
private:
    Vecteur2D p1, p2;

public:
    Segment(const Vecteur2D& p1, const Vecteur2D& p2,
        const std::string& couleur = "black");
    virtual ~Segment();

    double aire() const override;
    void dessiner(DrawVisitor& visitor) const override;
    void sauvegarder(SauvegardeVisitor& visitor) const override;
    void appliquerTransformation(const Transformation& t) override;

    operator std::string() const override;

    // getter / setter
    const Vecteur2D& getP1() const { return p1; }
    const Vecteur2D& getP2() const { return p2; }
    void setP1(const Vecteur2D& v) { p1 = v; }
    void setP2(const Vecteur2D& v) { p2 = v; }
};

#endif
