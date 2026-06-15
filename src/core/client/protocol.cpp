#include "core/client/protocol.hpp"
#include <string>
#include <cstring>

namespace Protocol
{
    // I really dont understand how this shit work 
    static void writeFixMap(std::vector<uint8_t>& buf, int n) 
    {
        buf.push_back(0x80 | (n & 0x0f));
    }

    static void writeFixStr(std::vector<uint8_t>& buf, const std::string& s) 
    {
        buf.push_back(0xa0 | (s.size() & 0x1f));
        buf.insert(buf.end(), s.begin(), s.end());
    }

    static void writeInt(std::vector<uint8_t>& buf, int v) 
    {
        buf.push_back(static_cast<uint8_t>(v));
    }

    static void writeBool(std::vector<uint8_t>& buf, bool v) 
    {
        buf.push_back(v ? 0xc3 : 0xc2);
    }

    static bool readFixMap(const uint8_t*& p, const uint8_t* end, int& n) 
    {
        if (p >= end || (*p & 0xf0) != 0x80) return false;

        n = *p & 0x0f;
        p++;

        return true;
    }

    static bool readFixStr(const uint8_t*& p, const uint8_t* end, std::string& s) 
    {
        if (p >= end || (*p & 0xe0) != 0xa0) return false;

        int len = *p & 0x1f;
        p++;

        if (p + len > end) return false;
        s.assign(reinterpret_cast<const char*>(p), len);
        p += len;

        return true;
    }

    static bool readInt(const uint8_t*& p, const uint8_t* end, int& v) 
    {
        if (p >= end) return false;
        if ((*p & 0x80) == 0) 
        {
            v = *p;
            p++;
            return true;
        }

        return false;
    }
    
    static bool readByte(const uint8_t*& p, const uint8_t* end, uint8_t& v)
    {
        if (p >= end) return false;
        if ((*p & 0x80) == 0) 
        {
            v = *p;
            p++;
            return true;
        }

        return false;
    }

    static bool readFloat(const uint8_t*& p, const uint8_t* end, float& v)
    {
        if (p >= end) return false;

        if (*p == 0xca) 
        {
            p++;
            if (p + 4 > end) return false;

            uint8_t tmp[4] = {p[3], p[2], p[1], p[0]};
            std::memcpy(&v, tmp, 4);
            p += 4;

            return true;
        }

        if (*p == 0xcb) 
        {
            p++;
            if (p + 8 > end) return false;

            double d;
            uint8_t tmp[8] = {p[7], p[6], p[5], p[4], p[3], p[2], p[1], p[0]};

            std::memcpy(&d, tmp, 8);
            v = static_cast<float>(d);
            p += 8;

            return true;
        }

        return false;
    }


    std::vector<uint8_t> encodeConnect() 
    {
        std::vector<uint8_t> buf;
        writeFixMap(buf, 1);
        writeFixStr(buf, "type");
        writeInt(buf, 1);
        return buf;
    }

    std::vector<uint8_t> encodeInput(bool up, bool down, bool left, bool right, bool sprint) 
    {
        std::vector<uint8_t> buf;
        writeFixMap(buf, 2);
        writeFixStr(buf, "type");

        writeInt(buf, 3);
        writeFixStr(buf, "keys");
        
        writeFixMap(buf, 5);
        writeFixStr(buf, "up");     writeBool(buf, up);
        writeFixStr(buf, "down");   writeBool(buf, down);
        writeFixStr(buf, "left");   writeBool(buf, left);
        writeFixStr(buf, "right");  writeBool(buf, right);
        writeFixStr(buf, "sprint"); writeBool(buf, sprint);
        return buf;
    }

    bool decodePacket(const uint8_t* data, size_t len, ServerState& state, std::string& player_id) 
    {
        const uint8_t* p = data;
        const uint8_t* end = data + len;

        int mapSize;
        if (!readFixMap(p, end, mapSize)) return false;

        int packetType = -1;

        for (int i = 0; i < mapSize; i++) 
        {
            std::string key;
            if (!readFixStr(p, end, key)) return false;

            if (key == "type") 
            {
                if (!readInt(p, end, packetType)) return false;
            } 
            else if (key == "player_id") 
            {
                if (!readFixStr(p, end, player_id)) return false;
            } 
            else if (key == "players") 
            {
                int playersMapSize;
                if (!readFixMap(p, end, playersMapSize)) return false;

                for (int j = 0; j < playersMapSize; j++) 
                {
                    std::string pid;
                    if (!readFixStr(p, end, pid)) return false;

                    int playerMapSize;
                    if (!readFixMap(p, end, playerMapSize)) return false;

                    PlayerState ps;
                    for (int k = 0; k < playerMapSize; k++) 
                    {
                        std::string field;
                        if (!readFixStr(p, end, field)) return false;
                        if (field == "x") 
                        {
                            if (!readFloat(p, end, ps.x)) return false;
                        } 
                        else if (field == "y") 
                        {
                            if (!readFloat(p, end, ps.y)) return false;
                        }
                    }
                    state.players[pid] = ps;
                }
            } 
            else 
            {
                return false;
            }
        }

        return packetType == 4 || packetType == 5;
    }
};