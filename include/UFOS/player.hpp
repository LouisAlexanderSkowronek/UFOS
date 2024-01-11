#pragma once

#include <SFML/Graphics.hpp>

#include <random>
#include <vector>

#include "ufo.hpp"

namespace UFOS {

    class Player : public sf::Drawable {
        const sf::Texture* m_texture_ptr;
        bool m_is_shooting;
        float t_end_shooting;
        sf::Vector2f m_pos;
        sf::Color m_laser_color;

        const std::array<sf::Color, 5u> m_laser_colors = {
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Magenta
        };

    public:

        Player(const sf::Texture* texture_ptr = nullptr, const sf::Vector2f& position = sf::Vector2f());

        inline void set_position_x(const float& x) { m_pos.x = x; }
        inline void move_x(const float& offset_x) { if (!m_is_shooting) m_pos.x += offset_x; }

        inline float get_position_x() const { return m_pos.x; }
        inline float get_size_x() const { return m_texture_ptr->getSize().x; }

        uint32_t update(const float& delta, std::vector<UFOS::UFO>& ufos);
        
        void shoot(std::mt19937& randint);

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    };

} // namespace UFOS