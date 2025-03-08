#ifndef SAUVEGARDETEXTEVISITOR_H
#define SAUVEGARDETEXTEVISITOR_H

#include "SauvegardeVisitor.h"
#include <fstream>

class SauvegardeTexteVisitor : public SauvegardeVisitor {
private:
    std::ofstream& out;
public:
    SauvegardeTexteVisitor(std::ofstream& ofs);

    void visit(const Point& p) override;
    void visit(const Segment& s) override;
    void visit(const Polygone& p) override;
    void visit(const Cercle& g) override;
    void visit(const Groupe& g) override;
};

#endif
