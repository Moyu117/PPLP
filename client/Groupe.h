#ifndef GROUPE_H
#define GROUPE_H

#include "Forme.h"
#include <vector>

class Groupe : public Forme {
private:
    std::vector<Forme*> formes;

public:
    Groupe(const std::string& couleur = "black");
    virtual ~Groupe();

    void ajouterForme(Forme* f);

    double aire() const override;
    void dessiner(DrawVisitor& visitor) const override;
    void sauvegarder(SauvegardeVisitor& visitor) const override;
    void appliquerTransformation(const Transformation& t) override;

    operator std::string() const override;

    const std::vector<Forme*>& getFormes() const { return formes; }
};

#endif
