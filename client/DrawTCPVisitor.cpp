#include "DrawTCPVisitor.h"
#include "Point.h"
#include "Segment.h"
#include "Polygone.h"
#include "Groupe.h"
#include "Cercle.h"
#include "NetworkInitializer.h"



#include <iostream>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

DrawTCPVisitor::DrawTCPVisitor()
    : sockFd(-1), connected(false)
{
    NetworkInitializer::getInstance();
    connected = connectToServer("127.0.0.1", 12345);
}

DrawTCPVisitor::~DrawTCPVisitor() {
    closeConnection();
}

bool DrawTCPVisitor::connectToServer(const std::string& host, int port) {
#ifdef _WIN32
    sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd == INVALID_SOCKET) {
        std::cerr << "[DrawTCPVisitor] Error creating socket\n";
        return false;
    }
    sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    srv.sin_addr.s_addr = inet_addr(host.c_str());

    if (::connect(sockFd, (sockaddr*)&srv, sizeof(srv)) == SOCKET_ERROR) {
        std::cerr << "[DrawTCPVisitor] Connect failed\n";
        closesocket(sockFd);
        sockFd = -1;
        return false;
    }
#else
    sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        std::cerr << "[DrawTCPVisitor] Error creating socket\n";
        return false;
    }
    sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    srv.sin_addr.s_addr = inet_addr(host.c_str());

    if (::connect(sockFd, (sockaddr*)&srv, sizeof(srv)) < 0) {
        std::cerr << "[DrawTCPVisitor] Connect failed\n";
        ::close(sockFd);
        sockFd = -1;
        return false;
    }
#endif
    std::cout << "[DrawTCPVisitor] Connected to server.\n";
    return true;
}

void DrawTCPVisitor::closeConnection() {
    if (connected) {
#ifdef _WIN32
        closesocket(sockFd);
#else
        ::close(sockFd);
#endif
        connected = false;
        std::cout << "[DrawTCPVisitor] Connection closed.\n";
    }
}

void DrawTCPVisitor::sendToServer(const std::string& msg) {
    if (!connected) {
        std::cerr << "[DrawTCPVisitor] Not connected, cannot send.\n";
        return;
    }
#ifdef _WIN32
    ::send(sockFd, msg.c_str(), (int)msg.size(), 0);
    ::send(sockFd, "\n", 1, 0);
#else
    ::send(sockFd, msg.c_str(), msg.size(), 0);
    ::send(sockFd, "\n", 1, 0);
#endif
    std::cout << "[TCP SEND] " << msg << std::endl;
}

// point:"DRAW_POINT x y color"
void DrawTCPVisitor::visit(const Point& p) {
    std::string cmd = "DRAW_POINT "
        + std::to_string(p.getPosition().x) + " "
        + std::to_string(p.getPosition().y) + " "
        + p.getCouleur();
    sendToServer(cmd);
}

//segment:"DRAW_SEGMENT x1 y1 x2 y2 color"
void DrawTCPVisitor::visit(const Segment& s) {
    std::string cmd = "DRAW_SEGMENT "
        + std::to_string(s.getP1().x) + " "
        + std::to_string(s.getP1().y) + " "
        + std::to_string(s.getP2().x) + " "
        + std::to_string(s.getP2().y) + " "
        + s.getCouleur();
    sendToServer(cmd);
}

// polygone: "DRAW_POLYGONE n x1 y1 x2 y2 ... xn yn color"
void DrawTCPVisitor::visit(const Polygone& poly) {
    const auto& pts = poly.getPoints();
    std::string cmd = "DRAW_POLYGONE " + std::to_string(pts.size());
    for (const auto& pt : pts) {
        cmd += " " + std::to_string(pt.x) + " " + std::to_string(pt.y);
    }
    cmd += " " + poly.getCouleur();
    sendToServer(cmd);
}

//Groupe, mettre coleur
void DrawTCPVisitor::visit(const Groupe& g) {
    for (auto f : g.getFormes()) {
        std::string oldC = f->getCouleur();
        f->setCouleur(g.getCouleur());
        f->dessiner(*this);
        f->setCouleur(oldC);
    }
}


//cercle: DRAW_CERCLE x y R couleur
void DrawTCPVisitor::visit(const Cercle& c) {
    std::string cmd = "DRAW_CERCLE "
        + std::to_string(c.getCentre().x) + " "
        + std::to_string(c.getCentre().y) + " "
        + std::to_string(c.getRayon()) + " "
        + c.getCouleur();
    sendToServer(cmd);
}