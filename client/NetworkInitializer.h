#ifndef NETWORKINITIALIZER_H
#define NETWORKINITIALIZER_H

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close //pour linux
#endif

class NetworkInitializer {
private:
    NetworkInitializer();
    ~NetworkInitializer();

public:
    static NetworkInitializer* getInstance();

   
    NetworkInitializer(const NetworkInitializer&) = delete;
    NetworkInitializer& operator=(const NetworkInitializer&) = delete;
};

#endif
