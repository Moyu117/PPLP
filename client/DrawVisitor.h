#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

class Point;
class Segment;
class Polygone;
class Groupe;

class DrawVisitor {
public:
    virtual ~DrawVisitor() {}

    virtual void visit(const Point& p) = 0;
    virtual void visit(const Segment& s) = 0;
    virtual void visit(const Polygone& p) = 0;
    virtual void visit(const Groupe& g) = 0;
};

#endif
