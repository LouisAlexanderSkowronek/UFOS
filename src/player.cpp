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

#include "UFOS/player.hpp"

#include <iostream>

UFOS::Player::Player(const std::string& texture_path, const sf::Vector2f& position) : m_is_shooting(false)
{
    texture.loadFromFile(texture_path);
    sprite.setTexture(texture);

    const auto texture_size = texture.getSize();

    sprite.setOrigin(texture_size.x / 2.0f, texture_size.y / 2.0f);
    sprite.setPosition(position);
}

void UFOS::Player::shoot(std::mt19937& randint) {
    if (m_is_shooting) return;
    
    m_is_shooting = true;
    t_end_shooting = .3f;

    do {
        m_laser_color = m_laser_colors[randint() % m_laser_colors.size()];
    } while (m_laser_color == sf::Color::Black);
}

unsigned UFOS::Player::update(const float& delta, std::vector<UFOS::UFO>& ufos) {

    t_end_shooting -= delta;
    if (t_end_shooting <= .0f) m_is_shooting = false;

    if (!m_is_shooting) return 0u;

    const sf::FloatRect bounds = sprite.getGlobalBounds();

    sf::RectangleShape laser_beam(sf::Vector2f(5.0f, 800.0f));
    laser_beam.setOrigin(2.5f, 800.0f);
    laser_beam.setPosition(sf::Vector2f(bounds.left + bounds.width/2.0f - 10.0f, bounds.top));

    register uint32_t additional_score = 0u;

    for (register uint32_t i = ufos.size() - 1; i < ufos.size(); i--) {
        if (laser_beam.getGlobalBounds().intersects(ufos[i].get_global_bounds())) { ufos.erase(ufos.begin() + i); additional_score++; }
    }

    return additional_score;
}

void UFOS::Player::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    const sf::Vector2f position = sprite.getPosition();

    if (m_is_shooting) {
        sf::RectangleShape laser_beam(sf::Vector2f(5.0f, 800.0f));
        laser_beam.setFillColor(m_laser_color);
        laser_beam.setOrigin(2.5f, 800.0f);
        laser_beam.setPosition(sf::Vector2f(position.x - 10.0f, position.y - texture.getSize().y/2.0f));
        window.draw(laser_beam);
    }

    window.draw(sprite, states);
}
