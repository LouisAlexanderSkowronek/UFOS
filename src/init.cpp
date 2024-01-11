#include "UFOS/init.hpp"

#include <fstream>
#include <string>
#include <random>
#include <iostream>

std::array<sf::Texture, N_TEXTURES> UFOS::load_textures(const char* filename) {
    std::ifstream file_texture_paths(filename);
    std::array<sf::Texture, N_TEXTURES> loaded_textures;

    if (!file_texture_paths.is_open()) {
        std::cerr << "Couldn't open file: " << filename << std::endl;
        return loaded_textures;
    }

    std::string filepath;
    for (register uint32_t i = 0u; std::getline(file_texture_paths, filepath) && i < N_TEXTURES; i++) { loaded_textures[i].loadFromFile(filepath); }

    return loaded_textures;
}

std::array<sf::Font, N_FONTS> UFOS::load_fonts(const char* filename) {
    std::ifstream file_font_paths(filename);
    std::array<sf::Font, N_FONTS> loaded_fonts;

    if (!file_font_paths.is_open()) {
        std::cerr << "Couldn't open file: " << filename << std::endl;
        return loaded_fonts;
    }

    std::string filepath;
    for (register uint32_t i = 0u; std::getline(file_font_paths, filepath) && i < N_FONTS; i++) { loaded_fonts[i].loadFromFile(filepath); }

    return loaded_fonts;
}

std::array<sf::Music, N_MUSICS>& UFOS::load_musics(const char* filename) {
    std::ifstream file_music_paths(filename);
    static std::array<sf::Music, N_MUSICS> loaded_musics;

    if (!file_music_paths.is_open()) {
        std::cerr << "Couldn't open file: " << filename << std::endl;
        return loaded_musics;
    }

    std::string filepath;
    for (register uint32_t i = 0u; std::getline(file_music_paths, filepath) && i < N_MUSICS; i++) { loaded_musics[i].openFromFile(filepath); }

    return loaded_musics;
}

sf::Sprite UFOS::render_background(std::mt19937& randint) {

    sf::RenderTexture texture;
    texture.create(1200u, 800u);

    std::array<sf::Vertex, 4u> bg_vertices = {
        sf::Vertex(sf::Vector2f(.0f, .0f), sf::Color(3, 3, 30)),
        sf::Vertex(sf::Vector2f(1200.0f, .0f), sf::Color(3, 3, 30)),
        sf::Vertex(sf::Vector2f(1200.0f, 800.0f), sf::Color(0, 0, 3)),
        sf::Vertex(sf::Vector2f(.0f, 800.0f), sf::Color(0, 0, 3))
    };

    texture.draw(bg_vertices.data(), bg_vertices.size(), sf::PrimitiveType::Quads);

    register uint32_t n = 1069u + randint() % 568u;

    sf::Vertex* vertices = new sf::Vertex[n];

    for (register uint32_t i = 0u; i < n; i++) {
        vertices[i].position = sf::Vector2f(static_cast<float>(randint() % 1200u), static_cast<float>(randint() % 600 + 200u));
    }

    texture.draw(vertices, n, sf::PrimitiveType::Points);

    delete[] vertices;

    n = 31 + randint() % 168;

    for (register uint32_t i = 0; i < n; i++) {
        sf::CircleShape star(.9f);
        star.setFillColor(sf::Color(0xCC, 0xCC, 0xFF));
        star.setPosition(static_cast<float>(randint() % 1200u), static_cast<float>(randint() % 150u));
        texture.draw(star);
    }

    n = 68 + randint() % 168;

    for (register uint32_t i = 0; i < n; i++) {
        sf::CircleShape star(.7f);
        star.setFillColor(sf::Color(0xCC, 0xCC, 0xFF));
        star.setPosition(static_cast<float>(randint() % 1200u), static_cast<float>(randint() % 100u + 125u));
        texture.draw(star);
    }

    n = 68 + randint() % 69;

    vertices = new sf::Vertex[n];

    for (register uint32_t i = 0u; i < n; i++) {
        vertices[i].position = sf::Vector2f(randint() % 1200u, randint() % 150u);
    }

    texture.draw(vertices, n, sf::PrimitiveType::Points);

    delete[] vertices;

    static sf::Texture rendered_texture = texture.getTexture();

    return sf::Sprite(rendered_texture);;
}