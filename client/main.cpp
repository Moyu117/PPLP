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
#include "DrawTCPVisitor.h"
#include "SauvegardeTexteVisitor.h"

using namespace std;

/**
 * ���� sommets.txt
 * ��ʽʾ����
 * 178
 * 20 ( 0.574299, 4.33274)
 * 19 ( 0.89098, 4.17736)
 * ...
 * ��ȡ�󴴽� Point ����
 */
vector<Forme*> parseSommets(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n; // �ļ����У��������
    for (int i = 0; i < n; i++) {
        int id;
        double x, y;
        fin >> id; // ���� 20
        char c;
        fin >> c; // '('
        fin >> x;
        char comma;
        fin >> comma; // ','
        fin >> y;
        fin >> c; // ')'

        // ��Point��ʾ
        Point* p = new Point(Vecteur2D(x, y), "red");
        result.push_back(p);
    }
    return result;
}

/**
 * ���� aretes.txt
 * ��ʽʾ����
 * 216
 * 45 ( 0.574299, 4.33274) ( 0.248653, 4.46715)
 * ...
 * ��ȡ�󴴽� Segment
 */
vector<Forme*> parseAretes(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n; // ����
    for (int i = 0; i < n; i++) {
        int id;
        double x1, y1, x2, y2;
        fin >> id;

        char c;
        fin >> c; // '('
        fin >> x1;
        char comma;
        fin >> comma; // ','
        fin >> y1;
        fin >> c; // ')'

        fin >> c; // '('
        fin >> x2;
        fin >> comma;
        fin >> y2;
        fin >> c; // ')'

        Segment* seg = new Segment(Vecteur2D(x1, y1), Vecteur2D(x2, y2), "blue");
        result.push_back(seg);
    }
    return result;
}

/**
 * ���� faces.txt
 * ��ʽʾ����
 * 39
 * 126 6 ( 0.930505, 5.19997) ( 1.20103, 5.67341) ...
 * ...
 * ��ȡ�󴴽� Polygone
 */
vector<Forme*> parseFaces(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n; // �������
    for (int i = 0; i < n; i++) {
        int faceId, nbPts;
        fin >> faceId;
        fin >> nbPts;
        vector<Vecteur2D> pts;
        pts.reserve(nbPts);
        for (int j = 0; j < nbPts; j++) {
            char c;
            fin >> c; // '('
            double x, y;
            char comma;
            fin >> x >> comma >> y;
            fin >> c; // ')'
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

    // 2. ��������״����һ��Groupe
    Groupe* allShapes = new Groupe("red");
    for (auto f : sommets) allShapes->ajouterForme(f);
    for (auto f : aretes)  allShapes->ajouterForme(f);
    for (auto f : faces)   allShapes->ajouterForme(f);

    // 3. �鿴�����(����߶ζ���0�����ֻ�ж���������)
    cout << "Total area = " << allShapes->aire() << endl;

    // 4. ƽ��һ��
    Translation tr(Vecteur2D(1.0, 1.0));
    allShapes->appliquerTransformation(tr);

    // 5. ���Ƶ�Java������
    {
        DrawTCPVisitor visitor;
        allShapes->dessiner(visitor);
    }

    // 6. ���浽�����ļ�
    {
        ofstream fout("output.txt");
        SauvegardeTexteVisitor stv(fout);
        allShapes->sauvegarder(stv);
        fout.close();
    }

    // 7. ����
    delete allShapes;
    sommets.clear(); // ����ָ����delete
    aretes.clear();
    faces.clear();

    return 0;
}
