#include "NetworkInitializer.h"
#include <iostream>

NetworkInitializer* NetworkInitializer::getInstance() {
    static NetworkInitializer instance;
    return &instance;
}

NetworkInitializer::NetworkInitializer() {
#ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
    }
#endif
    std::cout << "[NetworkInitializer] Network initialized.\n";
}

NetworkInitializer::~NetworkInitializer() {
#ifdef _WIN32
    WSACleanup();
#endif
    std::cout << "[NetworkInitializer] Network cleaned up.\n";
}
