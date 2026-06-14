#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UDPClient {
public:
    UDPClient();
    ~UDPClient();

    bool connect(const std::string& host, int port);
    void disconnect();

    bool send(const std::vector<uint8_t>& data);
    bool receive(std::vector<uint8_t>& data, size_t maxSize = 1024);

private:
    int sock = -1;
    sockaddr_in serverAddr{};
};
