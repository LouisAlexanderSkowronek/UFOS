#pragma once

#include <map>
#include <random>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "player.hpp"
#include "ufo.hpp"


class UFOSGame
{
public:

    UFOSGame();

    void intro();

    void loop();


private:

    void poll_events();

    void update(const float delta);

    void draw();

    void load_font(const std::string& filepath);

    void load_music(const std::string& filepath);

    void load_textures(const std::string& filepath_texture_list);

    void create_background_texture();




private:

    sf::RenderWindow window;
    sf::Clock clock;
    std::mt19937 randint;

    std::map<sf::Keyboard::Key, bool> pressed_keys;

    sf::Font font;
    sf::Music music;
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    std::vector<sf::Texture> ufo_textures;

    sf::Text fps_text;
    sf::Text score_text;

    float remaining_seconds_until_next_fps_update = .1f;
    float remaining_seconds_until_game_starts = 24.0f;
    float remaining_seconds_until_next_ufo_spawns;

    UFOS::Player player;
    std::vector<UFOS::UFO> ufos;

    unsigned score = 0;
};