/*
MIT License

Copyright (c) 2024 LouisAlexanderSkowronek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
