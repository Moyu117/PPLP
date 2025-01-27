#include "FileParser.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>

std::unordered_map<int, Vecteur2D> FileParser::parseSommets(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[错误] 无法打开顶点文件: " << filename << std::endl;
        exit(1);
    }

    std::unordered_map<int, Vecteur2D> sommets;
    std::string line;
    std::regex headerPattern(R"(^\d+$)");          // 匹配首行的顶点总数（纯数字）
    std::regex vertexPattern(R"(\s*(\d+)\s*\(\s*(-?\d+\.?\d*)\s*,\s*(-?\d+\.?\d*)\s*\)\s*)"); // 匹配顶点行

    // 第一步：读取并跳过首行（顶点总数）
    std::getline(file, line);
    if (!std::regex_match(line, headerPattern)) {
        std::cerr << "[错误] 文件首行格式错误，应为顶点总数: " << line << std::endl;
        exit(1);
    }

    // 第二步：从第二行开始解析顶点数据
    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;

        std::smatch match;
        if (std::regex_match(line, match, vertexPattern)) {
            int id = std::stoi(match[1]);
            double x = std::stod(match[2]);
            double y = std::stod(match[3]);
            sommets[id] = Vecteur2D(x, y);
        }
        else {
            std::cerr << "[警告] 忽略无效行（行号 " << lineNumber << "）: " << line << std::endl;
        }
    }

    if (sommets.empty()) {
        std::cerr << "[错误] 文件未包含有效顶点数据: " << filename << std::endl;
        exit(1);
    }

    return sommets;
}

// FileParser.cpp
std::vector<AreteData> FileParser::parseAretes(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[错误] 无法打开边文件: " << filename << std::endl;
        exit(1);
    }

    std::vector<AreteData> aretes;
    std::string line;
    std::regex headerPattern(R"(^\d+$)"); // 匹配首行的边总数
    std::regex aretePattern(R"(\s*(\d+)\s*\(\s*(-?\d+\.?\d*)\s*,\s*(-?\d+\.?\d*)\s*\)\s*\(\s*(-?\d+\.?\d*)\s*,\s*(-?\d+\.?\d*)\s*\)\s*)"); // 匹配边数据

    // 跳过首行（边总数）
    std::getline(file, line);
    if (!std::regex_match(line, headerPattern)) {
        std::cerr << "[错误] 边文件首行格式错误: " << line << std::endl;
        exit(1);
    }

    // 解析边数据
    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;

        std::smatch match;
        if (std::regex_match(line, match, aretePattern)) {
            AreteData arete;
            arete.id = std::stoi(match[1]);
            arete.start = Vecteur2D(std::stod(match[2]), std::stod(match[3]));
            arete.end = Vecteur2D(std::stod(match[4]), std::stod(match[5]));
            aretes.push_back(arete);
        }
        else {
            std::cerr << "[警告] 忽略无效边行（行号 " << lineNumber << "）: " << line << std::endl;
        }
    }

    return aretes;
}

// FileParser.cpp
std::vector<FaceData> FileParser::parseFaces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[错误] 无法打开面文件: " << filename << std::endl;
        exit(1);
    }

    std::vector<FaceData> faces;
    std::string line;
    std::regex headerPattern(R"(^\d+$)"); // 匹配首行的面总数
    std::regex facePattern(R"(\s*(\d+)\s+(\d+)\s+(.*))"); // 匹配面数据

    // 跳过首行（面总数）
    std::getline(file, line);
    if (!std::regex_match(line, headerPattern)) {
        std::cerr << "[错误] 面文件首行格式错误: " << line << std::endl;
        exit(1);
    }

    // 解析面数据
    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;

        std::smatch match;
        if (std::regex_match(line, match, facePattern)) {
            FaceData face;
            face.id = std::stoi(match[1]);
            int vertexCount = std::stoi(match[2]);
            std::string verticesStr = match[3];

            // 解析顶点坐标
            std::regex vertexPattern(R"(\(\s*(-?\d+\.?\d*)\s*,\s*(-?\d+\.?\d*)\s*\))");
            std::sregex_iterator iter(verticesStr.begin(), verticesStr.end(), vertexPattern);
            std::sregex_iterator end;

            while (iter != end) {
                std::smatch vertexMatch = *iter;
                double x = std::stod(vertexMatch[1]);
                double y = std::stod(vertexMatch[2]);
                face.vertices.emplace_back(x, y);
                ++iter;
            }

            if (face.vertices.size() == vertexCount) {
                faces.push_back(face);
            }
            else {
                std::cerr << "[警告] 面 " << face.id << " 顶点数量不匹配，预期 " << vertexCount << "，实际 " << face.vertices.size() << std::endl;
            }
        }
        else {
            std::cerr << "[警告] 忽略无效面行（行号 " << lineNumber << "）: " << line << std::endl;
        }
    }

    return faces;
}