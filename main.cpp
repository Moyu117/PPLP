#include "Forme.h"
#include "Visiteur.h"
#include "NetworkManager.h"
#include "FileParser.h"
#include <vector>
#include <memory>
#include <iostream>

std::vector<std::shared_ptr<Forme>> loadShapesFromFiles() {
    std::cout << "开始加载文件..." << std::endl;
    auto sommets = FileParser::parseSommets("data/sommets.txt");
    std::cout << "已加载 " << sommets.size() << " 个顶点" << std::endl;

    auto aretes = FileParser::parseAretes("data/aretes.txt");
    std::cout << "已加载 " << aretes.size() << " 条边" << std::endl;

    auto faces = FileParser::parseFaces("data/faces.txt");
    std::cout << "已加载 " << faces.size() << " 个面" << std::endl;

    std::vector<std::shared_ptr<Forme>> shapes;

    for (const auto& arete : aretes) {
        shapes.push_back(std::make_shared<Segment>(arete.start, arete.end, Couleur::BLACK));
    }
    std::cout << "已将边转换为线段" << std::endl;

    for (const auto& face : faces) {
        shapes.push_back(std::make_shared<Polygone>(face.vertices, Couleur::GREEN));
    }
    std::cout << "已将面转换为多边形" << std::endl;

    return shapes;
}

int main() {
    auto shapes = loadShapesFromFiles();
    std::cout << "已加载 " << shapes.size() << " 个形状" << std::endl;

    DessinVisiteur visitor;
    for (const auto& shape : shapes) {
        shape->accept(visitor);
    }
    std::cout << "已生成绘图指令" << std::endl;

    std::string commands = visitor.getCommands();
    std::cout << "生成的绘图指令内容:\n" << commands << std::endl;

    auto* network = NetworkManager::getInstance();
    std::cout << "正在连接服务器 127.0.0.1:8080..." << std::endl;
    SOCKET sock = network->connectToServer("127.0.0.1", 8080);
    std::cout << "连接服务器成功，发送指令..." << std::endl;
    send(sock, commands.c_str(), commands.size(), 0);
    closesocket(sock);
    std::cout << "指令已发送，程序正常退出" << std::endl;
    return 0;
}