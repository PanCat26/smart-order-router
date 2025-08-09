cmake_minimum_required(VERSION 3.28)
project(smart_order_router)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(lib)

add_executable(
        smart_order_router src/main.cpp
        src/config/venue-loader.cpp)

target_compile_definitions(smart_order_router PRIVATE ASIO_STANDALONE)

add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
