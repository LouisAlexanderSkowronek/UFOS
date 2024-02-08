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

namespace UFOS {

    class UFO : public sf::Drawable {
        sf::Sprite sprite;
        sf::Vector2f m_vel;

    public:

        UFO(const sf::Texture& texture, const sf::Vector2f& m_pos, const sf::Vector2f& velocity);

        void update(const float delta) { sprite.move(m_vel * delta); }

        sf::Vector2f get_position() const { return sprite.getPosition(); }
        sf::FloatRect get_global_bounds() const { return sprite.getGlobalBounds(); }

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
    };
} // namespace UFOS
