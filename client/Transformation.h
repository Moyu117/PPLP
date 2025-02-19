#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Point;
class Segment;
class Polygone;
class Groupe;

/**
 * 如果还有Cercle等，也需要在此声明
 */

class Transformation {
public:
    virtual ~Transformation() {}

    virtual void appliquer(Point& p) const = 0;
    virtual void appliquer(Segment& s) const = 0;
    virtual void appliquer(Polygone& p) const = 0;
    virtual void appliquer(Groupe& g) const = 0;

    // 若还有其他形状(如 Cercle), 亦需加相应函数
};

#endif
