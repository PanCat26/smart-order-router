#pragma once

#include "model/venue.hpp"

#include <string>
#include <vector>

std::vector<Venue> loadVenues(const std::string& filepath);

void validateVenues(const std::vector<Venue>& venues);
