#include "SauvegardeTexteVisitor.h"
#include "Point.h"
#include "Segment.h"
#include "Polygone.h"
#include "Groupe.h"
#include "Cercle.h"

SauvegardeTexteVisitor::SauvegardeTexteVisitor(std::ofstream& ofs)
    : out(ofs)
{}

void SauvegardeTexteVisitor::visit(const Point& p) {
    //  Point x y color
    out << "Point "
        << p.getPosition().x << " "
        << p.getPosition().y << " "
        << p.getCouleur() << std::endl;
}

void SauvegardeTexteVisitor::visit(const Segment& s) {
    //  Segment x1 y1 x2 y2 color
    out << "Segment "
        << s.getP1().x << " " << s.getP1().y << " "
        << s.getP2().x << " " << s.getP2().y << " "
        << s.getCouleur() << std::endl;
}

void SauvegardeTexteVisitor::visit(const Polygone& poly) {
    //  Polygone n x1 y1 ... xn yn color
    auto& pts = poly.getPoints();
    out << "Polygone " << pts.size();
    for (auto& pt : pts) {
        out << " " << pt.x << " " << pt.y;
    }
    out << " " << poly.getCouleur() << std::endl;
}

void SauvegardeTexteVisitor::visit(const Groupe& g) {
    out << "Groupe " << g.getFormes().size() << " "
        << g.getCouleur() << std::endl;
    for (auto f : g.getFormes()) {
        f->sauvegarder(*this);
    }
    out << "EndGroupe" << std::endl;
}

//cercle: CERCLE x y R color
void SauvegardeTexteVisitor::visit(const Cercle& c) {
    out << "CERCLE " << c.getCentre().x << " " << c.getCentre().y << " " << c.getRayon() << " " << c.getCouleur() << std::endl;
}
