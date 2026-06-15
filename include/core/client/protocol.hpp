#pragma once

#include <vector>
#include <map>
#include <cstdint>
#include <string>

namespace Protocol
{
    struct PlayerState
    {
        float x;
        float y;
    };

    struct ServerState 
    {
        std::map<std::string, PlayerState> players; // WHY HERE STD::STRING?
    };

    std::vector<uint8_t> encodeConnect();
    std::vector<uint8_t> encodeInput(bool up, bool down, bool left, bool right, bool sprint, bool attack);
    bool decodePacket(const uint8_t* data, size_t len, ServerState& state, std::string& player_id);
}