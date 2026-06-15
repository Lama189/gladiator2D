#pragma once

#include "core/client/udpclient.hpp"
#include "core/client/protocol.hpp"
#include <memory>

class Player;

class NetworkManager
{
public:
    ~NetworkManager() = default;

    void init();
    void cleanup();

    void update(float dt, Player& player);

    void sendInput(
        bool up, bool down,
        bool left, bool right,
        bool sprint, bool attack
    );

    const std::string& getPlayerId() const;
    const Protocol::ServerState& getLastState() const;

private:
    std::unique_ptr<UDPClient> client;
    Protocol::ServerState lastState;

    std::string playerId;
    bool connected = false;
};