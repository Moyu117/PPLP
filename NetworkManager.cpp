#pragma comment(lib, "Ws2_32.lib")
#include "NetworkManager.h"
#include <WS2tcpip.h>
#include <iostream>

NetworkManager* NetworkManager::instance = nullptr;

NetworkManager::NetworkManager() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[´íÎó] WSAStartup ³õÊ¼»¯Ê§°Ü" << std::endl;
        exit(1);
    }
}

NetworkManager* NetworkManager::getInstance() {
    if (!instance) {
        instance = new NetworkManager();
    }
    return instance;
}

SOCKET NetworkManager::connectToServer(const char* ip, int port) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "[´íÎó] ´´½¨Ì×½Ó×ÖÊ§°Ü" << std::endl;
        WSACleanup();
        exit(1);
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serverAddr.sin_addr) <= 0) {
        std::cerr << "[´íÎó] IPµØÖ·×ª»»Ê§°Ü: " << ip << std::endl;
        closesocket(sock);
        WSACleanup();
        exit(1);
    }

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "[´íÎó] Á¬½Ó·þÎñÆ÷Ê§°Ü: " << ip << ":" << port << std::endl;
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
    return sock;
}