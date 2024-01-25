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