#include "ScaleTransformation.h"
#include "Point.h"
#include "Segment.h"
#include "Polygone.h"
#include "Groupe.h"

void ScaleTransformation::appliquer(Point& p) const {
    p.setPosition(p.getPosition() * scaleFactor);
}

void ScaleTransformation::appliquer(Segment& s) const {
    s.setP1(s.getP1() * scaleFactor);
    s.setP2(s.getP2() * scaleFactor);
}

void ScaleTransformation::appliquer(Polygone& poly) const {
    auto& pts = poly.getPoints();
    for (auto& pt : pts) {
        pt = pt * scaleFactor;
    }
}

void ScaleTransformation::appliquer(Groupe& g) const {
    for (auto f : g.getFormes()) {
        f->appliquerTransformation(*this);
    }
}
