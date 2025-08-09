#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Venue
{
    uint8_t     id;
    std::string name;
    std::string multicast;
    uint16_t    port;
    double      fee;
    double      rebate;
    uint32_t    latency_us; // Simulated latency in microseconds
};

std::vector<Venue> loadVenues(const std::string& filepath);

void validateVenues(const std::vector<Venue>& venues);
