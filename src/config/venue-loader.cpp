#include "models/venue.hpp"
#include "config/venue-loader.hpp"

#include "nlohmann/json.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

using nlohmann::json;

static std::string slurp(const std::string& filepath)
{
    std::ifstream fs(filepath, std::ios::binary);
    if (!fs)
        throw std::runtime_error("Could not open file: " + filepath);

    std::ostringstream ss;
    ss << fs.rdbuf();

    return ss.str();
}

std::vector<Venue> loadVenues(const std::string& filepath) {
    std::string text = slurp(filepath);
    auto list = json::parse(text);

    if (!list.is_array())
        throw std::runtime_error("Venues file must be a JSON array");

    std::vector<Venue> out;
    out.reserve(list.size());

    for (const auto& object : list)
    {
        Venue venue{
                object.at("id").get<uint8_t>(),
                object.at("name").get<std::string>(),
                object.at("multicast").get<std::string>(),
                object.at("port").get<uint16_t>(),
                object.at("fee").get<double>(),
                object.at("rebate").get<double>(),
                object.at("latency_us").get<uint32_t>()
        };

        out.push_back(std::move(venue));
    }

    return out;
}

void validateVenues(const std::vector<Venue>& venues)
{
    if (venues.empty())
        throw std::runtime_error("No venues configured");

    std::unordered_set<uint8_t> ids;
    std::unordered_set<std::string> multicastAddresses;

    for (const auto& venue : venues)
    {
        if (ids.find(venue.id) != ids.end())
            throw std::runtime_error("Duplicate venue id: " + std::to_string(venue.id));
        ids.insert(venue.id);

        if (multicastAddresses.find(venue.multicast) != multicastAddresses.end())
            throw std::runtime_error("Duplicate multicast address: " + venue.multicast);
        multicastAddresses.insert(venue.multicast);

        if (venue.port < 1024)
            throw std::runtime_error("Port too low for venue: " + venue.name);

        if (venue.fee < 0.0 || venue.rebate < 0.0)
            throw std::runtime_error("Negative fee/rebate for venue: " + venue.name);

        if (venue.latency_us == 0)
            throw std::runtime_error("Latency cannot be 0 for venue: " + venue.name);
    }

    for (std::size_t want = 0; want < venues.size(); ++want)
    {
        auto id = static_cast<uint8_t>(want);

        if (ids.find(id) == ids.end())
            throw std::runtime_error("Venue ids must be contiguous 0..n-1 and " + std::to_string(want) + " is missing");
    }
}
