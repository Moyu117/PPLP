#ifndef VECTEUR2D_H
#define VECTEUR2D_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <sstream>
#include <string>

class Vecteur2D
{
public:
    double x, y;

    explicit Vecteur2D(double x = 0, double y = 0);
    Vecteur2D(const char* s);

    Vecteur2D operator+(const Vecteur2D& u) const;
    Vecteur2D operator*(double a) const;
    Vecteur2D operator-() const;

    // 转为字符串
    operator std::string() const;

    // 打印
    friend std::ostream& operator << (std::ostream& os, const Vecteur2D& u);

    // 行列式(用于多边形/三角形面积计算)
    static double determinant(const Vecteur2D& u, const Vecteur2D& v);
};

#endif
