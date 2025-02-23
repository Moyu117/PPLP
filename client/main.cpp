#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Vecteur2D.h"
#include "Point.h"
#include "Segment.h"
#include "Polygone.h"
#include "Groupe.h"
#include "Translation.h"
#include "ScaleTransformation.h"
#include "RotationTransformation.h"
#include "DrawTCPVisitor.h"
#include "SauvegardeTexteVisitor.h"

using namespace std;

// **�����Ƿ�ֻ���͵�**
bool onlySendPoints = false;  // Ĭ�Ϸ���������״

/**
 * ���� sommets.txt
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
 * ���� aretes.txt
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
 * ���� faces.txt
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

int main() {
    // 1. ���������ļ�
    vector<Forme*> sommets = parseSommets("../serpent/sommets.txt");
    vector<Forme*> aretes = parseAretes("../serpent/aretes.txt");
    vector<Forme*> faces = parseFaces("../serpent/faces.txt");

    // 2. ���� Groupe
    Groupe* allShapes = new Groupe("red");
    for (auto f : sommets) allShapes->ajouterForme(f);
    for (auto f : aretes)  allShapes->ajouterForme(f);
    for (auto f : faces)   allShapes->ajouterForme(f);

    // 3. **Ӧ������**
    double scaleFactor = 100.0;  // �Ŵ� 100 ��
    ScaleTransformation scale(scaleFactor);
    allShapes->appliquerTransformation(scale);

    // 4. **Ӧ��ƽ��**
    Vecteur2D translation(0.0, 0.0);  // ƽ�� (0,0)
    Translation trans(translation);
    allShapes->appliquerTransformation(trans);

    // 5. **Ӧ����ת**
    Vecteur2D rotationCenter(0.0, 0.0);  // **��ת���� (0,0)**
    double rotationAngle = 45.0;  // **��ת�Ƕ� 45��**
    RotationTransformation rotate(rotationCenter, rotationAngle);
    allShapes->appliquerTransformation(rotate);

    // 6. **���͵�������**
    {
        DrawTCPVisitor visitor;

        if (onlySendPoints) {
            cout << "Mode: Only sending points" << endl;
            for (auto f : sommets) {
                f->dessiner(visitor);  // **ֻ���͵�**
            }
        }
        else {
            cout << "Mode: Sending all shapes" << endl;
            allShapes->dessiner(visitor);  // **����������״**
        }
    }

    // 7. **���浽����**
    {
        ofstream fout("output.txt");
        SauvegardeTexteVisitor stv(fout);
        allShapes->sauvegarder(stv);
        fout.close();
    }

    // 8. **�ͷ��ڴ�**
    delete allShapes;
    sommets.clear();
    aretes.clear();
    faces.clear();

    return 0;
}
