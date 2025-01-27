#include "FileParser.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>

std::unordered_map<int, Vecteur2D> FileParser::parseSommets(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[����] �޷��򿪶����ļ�: " << filename << std::endl;
        exit(1);
    }

    std::unordered_map<int, Vecteur2D> sommets;
    std::string line;
    std::regex headerPattern(R"(^\d+$)");          // ƥ�����еĶ��������������֣�
    std::regex vertexPattern(R"(\s*(\d+)\s*\(\s*(-?\d+\.?\d*)\s*,\s*(-?\d+\.?\d*)\s*\)\s*)"); // ƥ�䶥����

    // ��һ������ȡ���������У�����������
    std::getline(file, line);
    if (!std::regex_match(line, headerPattern)) {
        std::cerr << "[����] �ļ����и�ʽ����ӦΪ��������: " << line << std::endl;
        exit(1);
    }

    // �ڶ������ӵڶ��п�ʼ������������
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
            std::cerr << "[����] ������Ч�У��к� " << lineNumber << "��: " << line << std::endl;
        }
    }

    if (sommets.empty()) {
        std::cerr << "[����] �ļ�δ������Ч��������: " << filename << std::endl;
        exit(1);
    }

    return sommets;
}

// FileParser.cpp
std::vector<AreteData> FileParser::parseAretes(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[����] �޷��򿪱��ļ�: " << filename << std::endl;
        exit(1);
    }

    std::vector<AreteData> aretes;
    std::string line;
    std::regex headerPattern(R"(^\d+$)"); // ƥ�����еı�����
    std::regex aretePattern(R"(\s*(\d+)\s*\(\s*(-?\d+\.?\d*)\s*,\s*(-?\d+\.?\d*)\s*\)\s*\(\s*(-?\d+\.?\d*)\s*,\s*(-?\d+\.?\d*)\s*\)\s*)"); // ƥ�������

    // �������У���������
    std::getline(file, line);
    if (!std::regex_match(line, headerPattern)) {
        std::cerr << "[����] ���ļ����и�ʽ����: " << line << std::endl;
        exit(1);
    }

    // ����������
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
            std::cerr << "[����] ������Ч���У��к� " << lineNumber << "��: " << line << std::endl;
        }
    }

    return aretes;
}

// FileParser.cpp
std::vector<FaceData> FileParser::parseFaces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[����] �޷������ļ�: " << filename << std::endl;
        exit(1);
    }

    std::vector<FaceData> faces;
    std::string line;
    std::regex headerPattern(R"(^\d+$)"); // ƥ�����е�������
    std::regex facePattern(R"(\s*(\d+)\s+(\d+)\s+(.*))"); // ƥ��������

    // �������У���������
    std::getline(file, line);
    if (!std::regex_match(line, headerPattern)) {
        std::cerr << "[����] ���ļ����и�ʽ����: " << line << std::endl;
        exit(1);
    }

    // ����������
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

            // ������������
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
                std::cerr << "[����] �� " << face.id << " ����������ƥ�䣬Ԥ�� " << vertexCount << "��ʵ�� " << face.vertices.size() << std::endl;
            }
        }
        else {
            std::cerr << "[����] ������Ч���У��к� " << lineNumber << "��: " << line << std::endl;
        }
    }

    return faces;
}