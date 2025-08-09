#pragma once

#include <cstdint>
#include <string>

struct Venue
{
    uint8_t id;
    std::string name;
    std::string multicast;
    uint16_t port;
    double fee;
    double rebate;
    uint32_t latency_us; // Simulated latency in microseconds
};