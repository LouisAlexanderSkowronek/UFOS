#include "UFOS/copyright_limitations.hpp"

#include "UFOS/ufo.hpp"

using namespace UFOS;

UFO::UFO(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& velocity) : sprite(texture), m_vel(velocity)
{
    sprite.setPosition(position);
}

void UFO::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(sprite, states);
}