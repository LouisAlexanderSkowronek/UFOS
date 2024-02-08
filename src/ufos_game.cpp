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

#include "UFOS/copyright_limitations.hpp"

#include "UFOS/ufos_game.hpp"

#include <fstream>
#include <iostream>

UFOSGame::UFOSGame() :
    window(sf::VideoMode(1200u, 800u), "UFOS - UFOS From Outer Space", sf::Style::Close),
    randint(time(nullptr)),
    player("../assets/textures/planet.png", sf::Vector2f(600.0f, 680.0f)),
    remaining_seconds_until_next_ufo_spawns((randint() % 60u) / 10.0f)
{
    font.loadFromFile("../assets/fonts/FreeSans.ttf");

    music.openFromFile("../assets/musics/kleiner_satellit.ogg");
    music.setLoop(true);
    music.play();

    load_textures("../assets/textures/textures.txt");

    create_background_texture();

    fps_text.setFont(font);
    fps_text.setPosition(.0f, 20.0f);
    fps_text.setStyle(sf::Text::Style::Regular);

    score_text.setFont(font);
    score_text.setPosition(1000.0f, 20.0f);
    score_text.setStyle(sf::Text::Style::Bold);

    pressed_keys.emplace(std::make_pair(sf::Keyboard::Left, false));
    pressed_keys.emplace(std::make_pair(sf::Keyboard::Right, false));
    pressed_keys.emplace(std::make_pair(sf::Keyboard::Space, false));

    ufos.reserve(8);
}


void UFOSGame::loop()
{
    while (window.isOpen())
    {
        const float delta = clock.restart().asSeconds();

        poll_events();

        update(delta);

        draw();
    }
}


void UFOSGame::poll_events()
{
     for (sf::Event e; window.pollEvent(e);) {
        switch (e.type) {
            case sf::Event::Closed:
                window.close();
                return;

            case sf::Event::KeyPressed:
                pressed_keys[e.key.code] = true;
                break;

            case sf::Event::KeyReleased:
                pressed_keys[e.key.code] = false;
                break;
        
            default: break;
        }
    }
}


void UFOSGame::update(const float delta)
{
    if (pressed_keys[sf::Keyboard::Left]) {
        player.move_x(-400.0f * delta);

        if (player.get_position_x() - player.get_size_x()/2.0f < .0f) { player.set_position_x(player.get_size_x()/2.0f); }
    }

    if (pressed_keys[sf::Keyboard::Right]) {
        player.move_x(400.0f * delta);
        if (player.get_position_x() + player.get_size_x()/2.0f > 1200.0f) { player.set_position_x(1200.0f - player.get_size_x()/2.0f); }
    }

    if (pressed_keys[sf::Keyboard::Space]) { player.shoot(randint); }

    score += player.update(delta, ufos);

    score_text.setString("Score: " + std::to_string(score));

    remaining_seconds_until_next_fps_update -= delta;
    if (remaining_seconds_until_next_fps_update <= .0f)
    {
        fps_text.setString(std::to_string(static_cast<uint32_t>(1.0f / delta)) + " fps"); remaining_seconds_until_next_fps_update = .1f;
    }

    remaining_seconds_until_next_ufo_spawns -= delta;

    if (remaining_seconds_until_next_ufo_spawns <= .0f) {
        ufos.emplace_back(
            ufo_textures[randint() % ufo_textures.size()], // Texture
            sf::Vector2f(static_cast<float>(200u + randint() % 800u), -200.0f), // Position
            sf::Vector2f(.0f, static_cast<float>(50u + randint() % 200)) // Velocity
        );

        remaining_seconds_until_next_ufo_spawns = (randint() % 60u) / 10.0f;
    }

    for (std::vector<UFOS::UFO>::iterator it = std::begin(ufos); it != std::end(ufos); )
    {
        it->update(delta);

        if (it->get_position().y > 800u) { it = ufos.erase(it); }
        else
        {
            it++;
        }
    }
}


void UFOSGame::draw()
{
    window.clear();

    window.draw(background_sprite);

    for (const UFOS::UFO& ufo : ufos) { window.draw(ufo); }

    window.draw(player);

    window.draw(score_text);
    window.draw(fps_text);

    window.display();
}


void UFOSGame::load_textures(const std::string& filepath_texture_list)
{
    std::ifstream file_texture_paths(filepath_texture_list);

    if (!file_texture_paths.is_open()) {
        std::cerr << "Couldn't open file: " << filepath_texture_list << std::endl;
    }

    std::string filepath;
    std::vector<std::string> filepaths;
    while (std::getline(file_texture_paths, filepath)) { filepaths.push_back(filepath); }

    const unsigned n_textures = filepaths.size();
    ufo_textures.resize(n_textures);

    for (unsigned i = 0; i < n_textures; i++) { ufo_textures[i].loadFromFile(filepaths[i]); }
}


void UFOSGame::create_background_texture()
{
    sf::RenderTexture rt;
    rt.create(1200u, 800u);

    std::array<sf::Vertex, 4u> bg_vertices = {
        sf::Vertex(sf::Vector2f(.0f, .0f), sf::Color(3, 3, 30)),
        sf::Vertex(sf::Vector2f(1200.0f, .0f), sf::Color(3, 3, 30)),
        sf::Vertex(sf::Vector2f(1200.0f, 800.0f), sf::Color(0, 0, 3)),
        sf::Vertex(sf::Vector2f(.0f, 800.0f), sf::Color(0, 0, 3))
    };

    rt.draw(bg_vertices.data(), bg_vertices.size(), sf::PrimitiveType::Quads);

    register uint32_t n = 1069u + randint() % 568u;

    sf::Vertex* vertices = new sf::Vertex[n];

    for (register uint32_t i = 0u; i < n; i++) {
        vertices[i].position = sf::Vector2f(static_cast<float>(randint() % 1200u), static_cast<float>(randint() % 600 + 200u));
    }

    rt.draw(vertices, n, sf::PrimitiveType::Points);

    delete[] vertices;

    n = 31 + randint() % 168;

    for (register uint32_t i = 0; i < n; i++) {
        sf::CircleShape star(.9f);
        star.setFillColor(sf::Color(0xCC, 0xCC, 0xFF));
        star.setPosition(static_cast<float>(randint() % 1200u), static_cast<float>(randint() % 150u));
        rt.draw(star);
    }

    n = 68 + randint() % 168;

    for (register uint32_t i = 0; i < n; i++) {
        sf::CircleShape star(.7f);
        star.setFillColor(sf::Color(0xCC, 0xCC, 0xFF));
        star.setPosition(static_cast<float>(randint() % 1200u), static_cast<float>(randint() % 100u + 125u));
        rt.draw(star);
    }

    n = 68 + randint() % 69;

    vertices = new sf::Vertex[n];

    for (register uint32_t i = 0u; i < n; i++) {
        vertices[i].position = sf::Vector2f(randint() % 1200u, randint() % 150u);
    }

    rt.draw(vertices, n, sf::PrimitiveType::Points);

    delete[] vertices;

    background_texture = rt.getTexture();

    background_sprite.setTexture(background_texture);
}
