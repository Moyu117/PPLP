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

// **控制是否只发送点**
bool onlySendPoints = false;  // 默认发送所有形状

/**
 * 解析 sommets.txt
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
 * 解析 aretes.txt
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
 * 解析 faces.txt
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
    // 1. 解析三个文件
    vector<Forme*> sommets = parseSommets("../serpent/sommets.txt");
    vector<Forme*> aretes = parseAretes("../serpent/aretes.txt");
    vector<Forme*> faces = parseFaces("../serpent/faces.txt");

    // 2. 创建 Groupe
    Groupe* allShapes = new Groupe("red");
    for (auto f : sommets) allShapes->ajouterForme(f);
    for (auto f : aretes)  allShapes->ajouterForme(f);
    for (auto f : faces)   allShapes->ajouterForme(f);

    // 3. **应用缩放**
    double scaleFactor = 100.0;  // 放大 100 倍
    ScaleTransformation scale(scaleFactor);
    allShapes->appliquerTransformation(scale);

    // 4. **应用平移**
    Vecteur2D translation(0.0, 0.0);  // 平移 (0,0)
    Translation trans(translation);
    allShapes->appliquerTransformation(trans);

    // 5. **应用旋转**
    Vecteur2D rotationCenter(0.0, 0.0);  // **旋转中心 (0,0)**
    double rotationAngle = 45.0;  // **旋转角度 45°**
    RotationTransformation rotate(rotationCenter, rotationAngle);
    allShapes->appliquerTransformation(rotate);

    // 6. **发送到服务器**
    {
        DrawTCPVisitor visitor;

        if (onlySendPoints) {
            cout << "Mode: Only sending points" << endl;
            for (auto f : sommets) {
                f->dessiner(visitor);  // **只发送点**
            }
        }
        else {
            cout << "Mode: Sending all shapes" << endl;
            allShapes->dessiner(visitor);  // **发送所有形状**
        }
    }

    // 7. **保存到本地**
    {
        ofstream fout("output.txt");
        SauvegardeTexteVisitor stv(fout);
        allShapes->sauvegarder(stv);
        fout.close();
    }

    // 8. **释放内存**
    delete allShapes;
    sommets.clear();
    aretes.clear();
    faces.clear();

    return 0;
}
