#ifndef FORME_H
#define FORME_H

#include <string>


class DrawVisitor;
class SauvegardeVisitor;
class Transformation;

class Forme {
protected:
    std::string couleur;

public:
    Forme(const std::string& couleur = "black") : couleur(couleur) {}
    virtual ~Forme() {}

    void setCouleur(const std::string& c) { couleur = c; }
    std::string getCouleur() const { return couleur; }

    // calcul surface
    virtual double aire() const = 0;

    // dessiner par visiteur
    virtual void dessiner(DrawVisitor& visitor) const = 0;

    // stock par visiteur
    virtual void sauvegarder(SauvegardeVisitor& visitor) const = 0;

    // ajouter trans
    virtual void appliquerTransformation(const Transformation& t) = 0;

    // trans en caractere
    virtual operator std::string() const = 0;
};

#endif
