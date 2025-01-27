#include "Forme.h"
#include "Visiteur.h"
#include "NetworkManager.h"
#include "FileParser.h"
#include <vector>
#include <memory>
#include <iostream>

std::vector<std::shared_ptr<Forme>> loadShapesFromFiles() {
    std::cout << "��ʼ�����ļ�..." << std::endl;
    auto sommets = FileParser::parseSommets("data/sommets.txt");
    std::cout << "�Ѽ��� " << sommets.size() << " ������" << std::endl;

    auto aretes = FileParser::parseAretes("data/aretes.txt");
    std::cout << "�Ѽ��� " << aretes.size() << " ����" << std::endl;

    auto faces = FileParser::parseFaces("data/faces.txt");
    std::cout << "�Ѽ��� " << faces.size() << " ����" << std::endl;

    std::vector<std::shared_ptr<Forme>> shapes;

    for (const auto& arete : aretes) {
        shapes.push_back(std::make_shared<Segment>(arete.start, arete.end, Couleur::BLACK));
    }
    std::cout << "�ѽ���ת��Ϊ�߶�" << std::endl;

    for (const auto& face : faces) {
        shapes.push_back(std::make_shared<Polygone>(face.vertices, Couleur::GREEN));
    }
    std::cout << "�ѽ���ת��Ϊ�����" << std::endl;

    return shapes;
}

int main() {
    auto shapes = loadShapesFromFiles();
    std::cout << "�Ѽ��� " << shapes.size() << " ����״" << std::endl;

    DessinVisiteur visitor;
    for (const auto& shape : shapes) {
        shape->accept(visitor);
    }
    std::cout << "�����ɻ�ͼָ��" << std::endl;

    std::string commands = visitor.getCommands();
    std::cout << "���ɵĻ�ͼָ������:\n" << commands << std::endl;

    auto* network = NetworkManager::getInstance();
    std::cout << "�������ӷ����� 127.0.0.1:8080..." << std::endl;
    SOCKET sock = network->connectToServer("127.0.0.1", 8080);
    std::cout << "���ӷ������ɹ�������ָ��..." << std::endl;
    send(sock, commands.c_str(), commands.size(), 0);
    closesocket(sock);
    std::cout << "ָ���ѷ��ͣ����������˳�" << std::endl;
    return 0;
}