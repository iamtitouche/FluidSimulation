cmake_minimum_required(VERSION 3.14)
project(FluidSimulation)

set(CMAKE_CXX_STANDARD 20)

include_directories(headers)

set(OpenCV_DIR "C:/opencv/build")
find_package(OpenCV REQUIRED)

# Ajout des fichiers sources et d'en-têtes
add_executable(FluidSimulation
        main.cpp
        src/audio_signal.cpp
        src/particle.cpp
        src/space2D.cpp
)

# Lier OpenCV aux fichiers exécutables
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
