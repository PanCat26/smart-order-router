#include "venue-utility.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>

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
