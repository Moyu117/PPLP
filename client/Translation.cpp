#include "Translation.h"
#include "Point.h"
#include "Segment.h"
#include "Polygone.h"
#include "Groupe.h"

void Translation::appliquer(Point& p) const {
    p.setPosition(p.getPosition() + deplacement);
}

void Translation::appliquer(Segment& s) const {
    s.setP1(s.getP1() + deplacement);
    s.setP2(s.getP2() + deplacement);
}

void Translation::appliquer(Polygone& poly) const {
    auto& pts = poly.getPoints();
    for (auto& pt : pts) {
        pt = pt + deplacement;
    }
}

void Translation::appliquer(Groupe& g) const {
    for (auto f : g.getFormes()) {
        f->appliquerTransformation(*this);
    }
}
