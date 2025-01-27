#pragma once
#include "Forme.h"

class VisiteurForme {
public:
    virtual void visit(const Segment& s) = 0;
    virtual void visit(const Polygone& p) = 0;
};

class DessinVisiteur : public VisiteurForme {
private:
    std::ostringstream commands;
public:
    void visit(const Segment& s) override;
    void visit(const Polygone& p) override;
    std::string getCommands() const;
};