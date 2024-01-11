#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <array>
#include <random>

#define N_FONTS    1u
#define N_TEXTURES 6u
#define N_MUSICS   1u

namespace UFOS {

    std::array<sf::Font, N_FONTS>       load_fonts(const char* filename);
    std::array<sf::Texture, N_TEXTURES> load_textures(const char* filename);
    std::array<sf::Music, N_MUSICS>&    load_musics(const char* filename);

    sf::Sprite render_background(std::mt19937& randint);

} // namespace UFOS