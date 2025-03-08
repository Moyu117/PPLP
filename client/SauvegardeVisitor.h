#ifndef SAUVEGARDEVISITOR_H
#define SAUVEGARDEVISITOR_H

class Point;
class Segment;
class Polygone;
class Groupe;
class Cercle;

class SauvegardeVisitor {
public:
    virtual ~SauvegardeVisitor() {}

    virtual void visit(const Point& p) = 0;
    virtual void visit(const Segment& s) = 0;
    virtual void visit(const Polygone& p) = 0;
    virtual void visit(const Groupe& g) = 0;
    virtual void visit(const Cercle& g) = 0;
};

#endif
