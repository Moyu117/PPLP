#pragma once
#include "Vecteur2D.h"
#include <memory>
#include <vector>

enum class Couleur { BLACK, BLUE, RED, GREEN, YELLOW, CYAN };

class VisiteurForme;

class Forme {
public:
    Couleur couleur;
    explicit Forme(Couleur c = Couleur::BLACK); // 关键修改：显式声明构造函数
    virtual ~Forme() = default;
    virtual void accept(VisiteurForme& visitor) = 0;
    virtual void translation(const Vecteur2D& delta) = 0;
    virtual operator std::string() const = 0;
};

class Segment : public Forme {
public:
    Vecteur2D start, end;
    Segment(const Vecteur2D& s, const Vecteur2D& e, Couleur c);
    void accept(VisiteurForme& visitor) override;
    void translation(const Vecteur2D& delta) override;
    operator std::string() const override;
};

class Polygone : public Forme {
public:
    std::vector<Vecteur2D> vertices;
    Polygone(const std::vector<Vecteur2D>& v, Couleur c);
    void accept(VisiteurForme& visitor) override;
    void translation(const Vecteur2D& delta) override;
    operator std::string() const override;
};