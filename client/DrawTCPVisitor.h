#ifndef DRAWTCPVISITOR_H
#define DRAWTCPVISITOR_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "DrawVisitor.h"
#include <string>

class DrawTCPVisitor : public DrawVisitor {
private:
    int sockFd;
    bool connected;

    // 发送字符串到服务器
    void sendToServer(const std::string& msg);

public:
    DrawTCPVisitor();
    virtual ~DrawTCPVisitor();

    void visit(const Point& p) override;
    void visit(const Segment& s) override;
    void visit(const Polygone& p) override;
    void visit(const Groupe& g) override;

private:
    bool connectToServer(const std::string& host, int port);
    void closeConnection();
};

#endif
