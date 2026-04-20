cmake_minimum_required(VERSION 3.10)

project(WirelessDisplayDemo VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages (hypothetical example)
find_package(Miracast REQUIRED)
find_package(AirPlay REQUIRED)

# Include directories
include_directories(${Miracast_INCLUDE_DIRS} ${AirPlay_INCLUDE_DIRS})

# Add the executable for the wireless display demo
add_executable(wireless_display_demo main.cpp)

# Link libraries
target_link_libraries(wireless_display_demo ${Miracast_LIBRARIES} ${AirPlay_LIBRARIES})
