cmake_minimum_required(VERSION 3.0)

project(UFOS)

add_executable(
    UFOS
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/init.cpp"
    "${CMAKE_SOURCE_DIR}/src/loop.cpp"
    "${CMAKE_SOURCE_DIR}/src/ufo.cpp"
    "${CMAKE_SOURCE_DIR}/src/player.cpp"
    "${CMAKE_SOURCE_DIR}//src/intro.cpp"
)

target_include_directories(UFOS PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(UFOS sfml-system sfml-window sfml-graphics sfml-audio)
