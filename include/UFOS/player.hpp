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

#include <SFML/Graphics.hpp>

#include <random>
#include <vector>

#include "ufo.hpp"

namespace UFOS {

    class Player : public sf::Drawable
    {
        sf::Texture texture;
        sf::Sprite sprite;
        bool m_is_shooting;
        float t_end_shooting;
        sf::Color m_laser_color;

        const std::array<sf::Color, 5u> m_laser_colors = {
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Magenta
        };

    public:

        Player(const std::string& texture_path, const sf::Vector2f& position);

        void set_position_x(const float x)
        {
            const float y = sprite.getPosition().y;
            sprite.setPosition(x, y);
        }

        void move_x(const float& offset_x)
        {
            if (!m_is_shooting) { sprite.move(offset_x, .0f); }
        }

        float get_position_x() const { return sprite.getPosition().x; }
        float get_size_x() const { return texture.getSize().x; }

        unsigned update(const float& delta, std::vector<UFOS::UFO>& ufos);
        
        void shoot(std::mt19937& randint);

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
    };

} // namespace UFOS
