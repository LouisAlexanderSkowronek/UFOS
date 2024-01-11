#include "UFOS/ufo.hpp"

using namespace UFOS;

UFO::UFO(const sf::Texture* texture_ptr, const sf::Vector2f& position, const sf::Vector2f& velocity) : m_texture_ptr(texture_ptr), m_pos(position), m_vel(velocity) {}

void UFO::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (m_texture_ptr == nullptr) return;

    sf::Sprite sprite(*m_texture_ptr);
    sprite.setPosition(m_pos);

    window.draw(sprite, states);
}