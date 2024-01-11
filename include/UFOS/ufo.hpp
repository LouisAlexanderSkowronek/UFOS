#pragma once

#include <SFML/Graphics.hpp>

namespace UFOS {

    class UFO : public sf::Drawable {
        const sf::Texture* m_texture_ptr;
        sf::Vector2f m_pos;
        sf::Vector2f m_vel;

    public:

        static float t_next_spawn;

        UFO(const sf::Texture* texture_ptr = nullptr, const sf::Vector2f& m_pos = sf::Vector2f(), const sf::Vector2f& velocity = sf::Vector2f());

        inline void update(const float& delta) { m_pos += m_vel * delta; }

        inline sf::Vector2f get_position() const { return m_pos; }
        inline sf::FloatRect get_global_bounds() const { sf::Sprite sprite(*m_texture_ptr); sprite.setPosition(m_pos); return sprite.getGlobalBounds(); }

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    };
} // namespace UFOS