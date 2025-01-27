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
    // 顶点解析
    static std::unordered_map<int, Vecteur2D> parseSommets(const std::string& filename);

    // 边解析（新增）
    static std::vector<AreteData> parseAretes(const std::string& filename);

    // 面解析（新增）
    static std::vector<FaceData> parseFaces(const std::string& filename);
};