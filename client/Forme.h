#ifndef FORME_H
#define FORME_H

#include <string>

// 前置声明
class DrawVisitor;
class SauvegardeVisitor;
class Transformation;

class Forme {
protected:
    std::string couleur;

public:
    Forme(const std::string& couleur = "black") : couleur(couleur) {}
    virtual ~Forme() {}

    void setCouleur(const std::string& c) { couleur = c; }
    std::string getCouleur() const { return couleur; }

    // 计算面积
    virtual double aire() const = 0;

    // 通过访问者进行绘制
    virtual void dessiner(DrawVisitor& visitor) const = 0;

    // 通过访问者进行保存
    virtual void sauvegarder(SauvegardeVisitor& visitor) const = 0;

    // 施加几何变换
    virtual void appliquerTransformation(const Transformation& t) = 0;

    // 转为字符串
    virtual operator std::string() const = 0;
};

#endif
