#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Point;
class Segment;
class Polygone;
class Groupe;

/**
 * �������Cercle�ȣ�Ҳ��Ҫ�ڴ�����
 */

class Transformation {
public:
    virtual ~Transformation() {}

    virtual void appliquer(Point& p) const = 0;
    virtual void appliquer(Segment& s) const = 0;
    virtual void appliquer(Polygone& p) const = 0;
    virtual void appliquer(Groupe& g) const = 0;

    // ������������״(�� Cercle), �������Ӧ����
};

#endif
