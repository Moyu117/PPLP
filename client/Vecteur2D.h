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

    // תΪ�ַ���
    operator std::string() const;

    // ��ӡ
    friend std::ostream& operator << (std::ostream& os, const Vecteur2D& u);

    // ����ʽ(���ڶ����/�������������)
    static double determinant(const Vecteur2D& u, const Vecteur2D& v);
};

#endif
