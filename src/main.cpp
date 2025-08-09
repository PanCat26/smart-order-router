#include "venue-utility.hpp"

#include <spdlog/spdlog.h>

#include <vector>

int main()
{
    try
    {
        std::vector<Venue> venues = loadVenues("config/venues.json");

        validateVenues(venues);

        spdlog::info("Loaded {} venues:", venues.size());
        for (const Venue& v : venues)
        {
            spdlog::info("id={} name={} multicast={}:{} fee=${:.4f} rebate=${:.4f} latency={}us",
                         v.id, v.name, v.multicast, v.port, v.fee, v.rebate, v.latency_us);
        }

    } catch (const std::exception& e)
    {
        spdlog::error("Config error: {}", e.what());

        return 1;
    }

    return 0;
}