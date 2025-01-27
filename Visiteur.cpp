#include "Visiteur.h"
#include "Forme.h"

void DessinVisiteur::visit(const Segment& s) {
    commands << "LINE " << s.start.x << "," << s.start.y << " "
        << s.end.x << "," << s.end.y << "\n";
}

void DessinVisiteur::visit(const Polygone& p) {
    commands << "POLYGON ";
    for (const auto& v : p.vertices) {
        commands << v.x << "," << v.y << " ";
    }
    commands << "\n";
}

std::string DessinVisiteur::getCommands() const {
    return commands.str();
}