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
 * 解析 sommets.txt
 * 格式示例：
 * 178
 * 20 ( 0.574299, 4.33274)
 * 19 ( 0.89098, 4.17736)
 * ...
 * 读取后创建 Point 对象
 */
vector<Forme*> parseSommets(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n; // 文件首行：点的数量
    for (int i = 0; i < n; i++) {
        int id;
        double x, y;
        fin >> id; // 形如 20
        char c;
        fin >> c; // '('
        fin >> x;
        char comma;
        fin >> comma; // ','
        fin >> y;
        fin >> c; // ')'

        // 用Point表示
        Point* p = new Point(Vecteur2D(x, y), "red");
        result.push_back(p);
    }
    return result;
}

/**
 * 解析 aretes.txt
 * 格式示例：
 * 216
 * 45 ( 0.574299, 4.33274) ( 0.248653, 4.46715)
 * ...
 * 读取后创建 Segment
 */
vector<Forme*> parseAretes(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n; // 条数
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
 * 解析 faces.txt
 * 格式示例：
 * 39
 * 126 6 ( 0.930505, 5.19997) ( 1.20103, 5.67341) ...
 * ...
 * 读取后创建 Polygone
 */
vector<Forme*> parseFaces(const string& filename) {
    vector<Forme*> result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        return result;
    }
    int n;
    fin >> n; // 面的数量
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
    // 1. 解析三个文件
    vector<Forme*> sommets = parseSommets("../serpent/sommets.txt");
    vector<Forme*> aretes = parseAretes("../serpent/aretes.txt");
    vector<Forme*> faces = parseFaces("../serpent/faces.txt");

    // 2. 将所有形状放入一个Groupe
    Groupe* allShapes = new Groupe("red");
    for (auto f : sommets) allShapes->ajouterForme(f);
    for (auto f : aretes)  allShapes->ajouterForme(f);
    for (auto f : faces)   allShapes->ajouterForme(f);

    // 3. 查看总面积(点和线段都是0面积，只有多边形有面积)
    cout << "Total area = " << allShapes->aire() << endl;

    // 4. 平移一下
    Translation tr(Vecteur2D(1.0, 1.0));
    allShapes->appliquerTransformation(tr);

    // 5. 绘制到Java服务器
    {
        DrawTCPVisitor visitor;
        allShapes->dessiner(visitor);
    }

    // 6. 保存到本地文件
    {
        ofstream fout("output.txt");
        SauvegardeTexteVisitor stv(fout);
        allShapes->sauvegarder(stv);
        fout.close();
    }

    // 7. 清理
    delete allShapes;
    sommets.clear(); // 里面指针已delete
    aretes.clear();
    faces.clear();

    return 0;
}
