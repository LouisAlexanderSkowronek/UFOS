cmake_minimum_required(VERSION 3.0)

project(UFOS)

add_executable(
    UFOS
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/ufos_game.cpp"
    "${CMAKE_SOURCE_DIR}/src/ufo.cpp"
    "${CMAKE_SOURCE_DIR}/src/player.cpp"
)

target_include_directories(UFOS PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(UFOS sfml-system sfml-window sfml-graphics sfml-audio)