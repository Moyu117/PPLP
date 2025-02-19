#ifndef FORME_H
#define FORME_H

#include <string>

// ǰ������
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

    // �������
    virtual double aire() const = 0;

    // ͨ�������߽��л���
    virtual void dessiner(DrawVisitor& visitor) const = 0;

    // ͨ�������߽��б���
    virtual void sauvegarder(SauvegardeVisitor& visitor) const = 0;

    // ʩ�Ӽ��α任
    virtual void appliquerTransformation(const Transformation& t) = 0;

    // תΪ�ַ���
    virtual operator std::string() const = 0;
};

#endif
