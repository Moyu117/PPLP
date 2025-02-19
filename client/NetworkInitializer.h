#ifndef NETWORKINITIALIZER_H
#define NETWORKINITIALIZER_H

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

class NetworkInitializer {
private:
    NetworkInitializer();
    ~NetworkInitializer();

public:
    static NetworkInitializer* getInstance();

    // ½û¿½±´
    NetworkInitializer(const NetworkInitializer&) = delete;
    NetworkInitializer& operator=(const NetworkInitializer&) = delete;
};

#endif
