#ifndef POLYGONE_H
#define POLYGONE_H

#include "Forme.h"
#include "Vecteur2D.h"
#include <vector>
#include <string>

class Polygone : public Forme {
private:
    std::vector<Vecteur2D> points; // ¶à±ßÐÎ¶¥µã

public:
    Polygone(const std::vector<Vecteur2D>& pts, const std::string& couleur = "black");
    virtual ~Polygone();

    double aire() const override;
    void dessiner(DrawVisitor& visitor) const override;
    void sauvegarder(SauvegardeVisitor& visitor) const override;
    void appliquerTransformation(const Transformation& t) override;

    operator std::string() const override;

    // getter / setter
    std::vector<Vecteur2D>& getPoints() { return points; }
    const std::vector<Vecteur2D>& getPoints() const { return points; }
};

#endif
