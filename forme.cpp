#include "Forme.h"
#include "Visiteur.h"

// 基类构造函数实现
Forme::Forme(Couleur c) : couleur(c) {}

// Segment 类实现
Segment::Segment(const Vecteur2D& s, const Vecteur2D& e, Couleur c)
    : Forme(c), start(s), end(e) {}

void Segment::accept(VisiteurForme& visitor) {
    visitor.visit(*this);
}

void Segment::translation(const Vecteur2D& delta) {
    start = start + delta;
    end = end + delta;
}

Segment::operator std::string() const {
    return "Segment: " + static_cast<std::string>(start) + " -> " + static_cast<std::string>(end);
}

// Polygone 类实现
Polygone::Polygone(const std::vector<Vecteur2D>& v, Couleur c)
    : Forme(c), vertices(v) {}

void Polygone::accept(VisiteurForme& visitor) {
    visitor.visit(*this);
}

void Polygone::translation(const Vecteur2D& delta) {
    for (auto& v : vertices) {
        v = v + delta;
    }
}

Polygone::operator std::string() const {
    std::ostringstream os;
    os << "Polygone with " << vertices.size() << " vertices: ";
    for (const auto& v : vertices) {
        os << static_cast<std::string>(v) << " ";
    }
    return os.str();
}