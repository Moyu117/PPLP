#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Vecteur2D.h"
#include "Point.h"
#include "Segment.h"
#include "Polygone.h"
#include "Cercle.h"
#include "Groupe.h"
#include "Translation.h"
#include "ScaleTransformation.h"
#include "RotationTransformation.h"
#include "DrawTCPVisitor.h"
#include "SauvegardeTexteVisitor.h"

using namespace std;

// **controle si seuls les points sont envoyes**
bool onlySendPoints = true;  

/**
 * sommets.txt
 */
vector<Forme*> parseSommets(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        int id;
        double x, y;
        fin >> id;
        char c;
        fin >> c >> x >> c >> y >> c;

        Point* p = new Point(Vecteur2D(x, y), "red");
        result.push_back(p);
    }
    return result;
}

/**
 *  aretes.txt
 */
vector<Forme*> parseAretes(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        int id;
        double x1, y1, x2, y2;
        fin >> id;
        char c;
        fin >> c >> x1 >> c >> y1 >> c;
        fin >> c >> x2 >> c >> y2 >> c;

        Segment* seg = new Segment(Vecteur2D(x1, y1), Vecteur2D(x2, y2), "blue");
        result.push_back(seg);
    }
    return result;
}

/**
 *  faces.txt
 */
vector<Forme*> parseFaces(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        int faceId, nbPts;
        fin >> faceId;
        fin >> nbPts;
        vector<Vecteur2D> pts;
        pts.reserve(nbPts);
        for (int j = 0; j < nbPts; j++) {
            char c;
            double x, y;
            fin >> c >> x >> c >> y >> c;
            pts.push_back(Vecteur2D(x, y));
        }
        Polygone* poly = new Polygone(pts, "cyan");
        result.push_back(poly);
    }
    return result;
}

/**
 *  cercles.txt
 */
vector<Forme*> parseCercles(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        int id;
        double x, y, r;
        fin >> id;
        char c;
        fin >> c >> x >> c >> y >> c >> r >> c;

        Cercle* cercle = new Cercle(Vecteur2D(x, y), r, "green");
        result.push_back(cercle);
    }
    return result;
}

int main() {
    // 1. analyser ficher
    vector<Forme*> sommets = parseSommets("../serpent/sommets.txt");
    vector<Forme*> aretes = parseAretes("../serpent/aretes.txt");
    vector<Forme*> faces = parseFaces("../serpent/faces.txt");
    vector<Forme*> cercles = parseCercles("../serpent/cercles.txt");

    // 2. creer Groupe
    Groupe* allShapes = new Groupe("red");
    for (auto f : sommets) allShapes->ajouterForme(f);
    for (auto f : aretes)  allShapes->ajouterForme(f);
    for (auto f : faces)   allShapes->ajouterForme(f);
    for (auto f : cercles) allShapes->ajouterForme(f);

    // 3. **calcul surface initiale**
    double totalArea = allShapes->aire();
    cout << "Original Area: " << totalArea << endl;

    // 4. **zoom**
    double scaleFactor = 100.0;  // x100
    ScaleTransformation scale(scaleFactor);
    allShapes->appliquerTransformation(scale);

    // 5. **calculer apres zoom**
    double scaledArea = totalArea * scaleFactor * scaleFactor;
    cout << "Scaled Area (Factor " << scaleFactor << "): " << scaledArea << endl;

    // 6. **translation**
    Vecteur2D translation(0.0, 0.0);  // (0,0)
    Translation trans(translation);
    allShapes->appliquerTransformation(trans);

    // 7. **rotation**
    Vecteur2D rotationCenter(0.0, 0.0);  // **centre (0,0)**
    double rotationAngle = 45.0;  // **angle 45бу**
    RotationTransformation rotate(rotationCenter, rotationAngle);
    allShapes->appliquerTransformation(rotate);

    // 8. **envoyer a serveur**
    {
        DrawTCPVisitor visitor;

        if (onlySendPoints) {
            cout << "Mode: Only sending points" << endl;
            for (auto f : sommets) {
                f->dessiner(visitor);
            }
        }
        else {
            cout << "Mode: Sending all shapes" << endl;
            allShapes->dessiner(visitor);
        }
    }

    // 9. **stoker info**
    {
        ofstream fout("output.txt");
        SauvegardeTexteVisitor stv(fout);
        allShapes->sauvegarder(stv);
        fout << "Original Area: " << totalArea << endl;
        fout << "Scaled Area (Factor " << scaleFactor << "): " << scaledArea << endl;
        fout.close();
    }

    // 10. **clean **
    delete allShapes;
    sommets.clear();
    aretes.clear();
    faces.clear();
    cercles.clear();

    return 0;
}
