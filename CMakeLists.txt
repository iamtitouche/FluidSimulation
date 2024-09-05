cmake_minimum_required(VERSION 3.29)
project(FluidSimulation)

set(CMAKE_CXX_STANDARD 20)


add_executable(FluidSimulation main.cpp
        src/audio_signal.cpp
        src/particle.cpp
        src/particle.hpp
        src/space2D.cpp
        src/space2D.hpp
)
