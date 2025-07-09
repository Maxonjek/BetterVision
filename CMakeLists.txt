cmake_minimum_required(VERSION 3.28)
project(BetterVision)

set(CMAKE_CXX_STANDARD 20)

message("CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_CXX_COMPILER_VERSION=${CMAKE_CXX_COMPILER_VERSION}")

file(GLOB_RECURSE interfaces_H
Interfaces/*.h)

file(GLOB_RECURSE CORE_FILES
Core/*.h
Core/*.cpp)



add_executable(BetterVision main.cpp
        ${interfaces_H}
        ${CORE_FILES}
)


target_include_directories(BetterVision PRIVATE
    Interfaces/
    Interfaces/FIleManagement/
    Interfaces/Sensors/
    Interfaces/Plugins/
    Interfaces/Codecs/
    Interfaces/Transmission/EventBus/
    Interfaces/Transmission/MessageBus/
    Interfaces/Transmission/Observers/
    Interfaces/DataHolder/
        Core/
        Core/DataHolder/headers
        GUI/


)