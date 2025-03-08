#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Point;
class Segment;
class Polygone;
class Groupe;
class Cercle;

/**
 * si ajouter d'autre forme,ajouter ici
 */

class Transformation {
public:
    virtual ~Transformation() {}

    virtual void appliquer(Point& p) const = 0;
    virtual void appliquer(Segment& s) const = 0;
    virtual void appliquer(Polygone& p) const = 0;
    virtual void appliquer(Groupe& g) const = 0;
    virtual void appliquer(Cercle& g) const = 0;
    //ajouter fonction
};

#endif
