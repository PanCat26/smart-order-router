#pragma once

#include <cstdint>
#include <variant>

namespace market::events
{
    using Instrument = std::uint32_t;
    using Timestamp = std::uint64_t;

    enum class EventKind : uint8_t { TopOfBook = 1, Trade = 2 };

    struct TopOfBook
    {
        Instrument symbol{};
        double bid{};
        double ask{};
        uint32_t bidSize{};
        uint32_t askSize{};
        Timestamp exchangeTimestamp_ns{}; // Exchange emission timestamp
        Timestamp receiveTimestamp_ns{}; // Local receive time
        uint8_t venueId{};
    };

    struct Trade
    {
        Instrument symbol{};
        double price{};
        uint32_t quantity{};
        bool isBuyAggressor{};
        Timestamp exchangeTimestamp_ns{};
        Timestamp receiveTimestamp_ns{};
        uint8_t venueId{};
    };

    using Event = std::variant<TopOfBook, Trade>;
}