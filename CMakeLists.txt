cmake_minimum_required(VERSION 3.14)
project(FluidSimulation)

set(CMAKE_CXX_STANDARD 20)

# Find the Qt libraries
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Ajout des fichiers sources et d'en-têtes
add_executable(FluidSimulation
        main.cpp
        src/particle.cpp
        src/space2D.cpp
        src/utils.cpp
)

# Lier Qt aux fichiers exécutables
target_link_libraries(FluidSimulation Qt5::Widgets)
