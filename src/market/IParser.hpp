#pragma once

#include "market/Events.hpp"

#include <cstdint>
#include <span>
#include <vector>

namespace market::parser
{
    class IParser
    {
    public:
        virtual bool parse(std::uint8_t venueId,
                           std::span<const std::uint8_t> payload,
                           market::events::Timestamp receiveTimestamp_ns,
                           std::vector<market::events::Event>& out) = 0;
    };
}