#pragma once
#include <winsock2.h>

class NetworkManager {
private:
    static NetworkManager* instance;
    WSADATA wsaData;
    NetworkManager();
public:
    static NetworkManager* getInstance();
    SOCKET connectToServer(const char* ip, int port);
};