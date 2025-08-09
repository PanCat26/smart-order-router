#include "models/venue.hpp"
#include "config/venue-loader.hpp"

#include <spdlog/spdlog.h>

#include <vector>

int main()
{
    try
    {
        std::vector<Venue> venues = loadVenues("config/venues.json");

        validateVenues(venues);

        spdlog::info("Loaded {} venues:", venues.size());
        for (const Venue& venue : venues)
        {
            spdlog::info("id={} name={} multicast={}:{} fee=${:.4f} rebate=${:.4f} latency={}us",
                         venue.id, venue.name, venue.multicast, venue.port, venue.fee, venue.rebate, venue.latency_us);
        }

    } catch (const std::exception& e)
    {
        spdlog::error("Config error: {}", e.what());

        return 1;
    }

    return 0;
}