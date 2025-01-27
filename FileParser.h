// FileParser.h
#pragma once
#include "Vecteur2D.h"
#include <vector>
#include <unordered_map>

struct AreteData {
    int id;
    Vecteur2D start, end;
};

struct FaceData {
    int id;
    std::vector<Vecteur2D> vertices;
};

class FileParser {
public:
    // �������
    static std::unordered_map<int, Vecteur2D> parseSommets(const std::string& filename);

    // �߽�����������
    static std::vector<AreteData> parseAretes(const std::string& filename);

    // �������������
    static std::vector<FaceData> parseFaces(const std::string& filename);
};