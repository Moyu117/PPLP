#ifndef POINT_H
#define POINT_H

#include "Forme.h"
#include "Vecteur2D.h"
#include <string>

/**
 * Point : 表示一个 2D 点.
 */
class Point : public Forme {
private:
    Vecteur2D position;

public:
    Point(const Vecteur2D& pos, const std::string& couleur = "black");
    virtual ~Point();

    double aire() const override;
    void dessiner(DrawVisitor& visitor) const override;
    void sauvegarder(SauvegardeVisitor& visitor) const override;
    void appliquerTransformation(const Transformation& t) override;

    operator std::string() const override;

    // getter / setter
    const Vecteur2D& getPosition() const { return position; }
    void setPosition(const Vecteur2D& p) { position = p; }
};

#endif
