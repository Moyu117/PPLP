#include "Groupe.h"
#include "DrawVisitor.h"
#include "SauvegardeVisitor.h"
#include "Transformation.h"
#include <sstream>

Groupe::Groupe(const std::string& coul)
    : Forme(coul)
{}

Groupe::~Groupe() {
    // 由Groupe管理其子Forme的生命周期
    for (Forme* f : formes) {
        delete f;
    }
    formes.clear();
}

void Groupe::ajouterForme(Forme* f) {
    formes.push_back(f);
}

double Groupe::aire() const {
    double total = 0.0;
    for (Forme* f : formes) {
        total += f->aire();
    }
    return total;
}

void Groupe::dessiner(DrawVisitor& visitor) const {
    visitor.visit(*this);
}

void Groupe::sauvegarder(SauvegardeVisitor& visitor) const {
    visitor.visit(*this);
}

void Groupe::appliquerTransformation(const Transformation& t) {
    t.appliquer(*this);
}

Groupe::operator std::string() const {
    std::ostringstream oss;
    oss << "Groupe [couleur=" << couleur << ", formes={";
    for (size_t i = 0; i < formes.size(); i++) {
        if (i > 0) oss << ", ";
        oss << (std::string)(*formes[i]);
    }
    oss << "}]";
    return oss.str();
}
