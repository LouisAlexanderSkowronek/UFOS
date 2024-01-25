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