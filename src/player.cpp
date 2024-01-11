#include "UFOS/player.hpp"

#include <iostream>

UFOS::Player::Player(const sf::Texture* texture_ptr, const sf::Vector2f& position) : m_texture_ptr(texture_ptr), m_is_shooting(false), m_pos(position) {}

void UFOS::Player::shoot(std::mt19937& randint) {
    if (m_is_shooting) return;
    
    m_is_shooting = true;
    t_end_shooting = .3f;

    do {
        m_laser_color = m_laser_colors[randint() % m_laser_colors.size()];
    } while (m_laser_color == sf::Color::Black);
}

uint32_t UFOS::Player::update(const float& delta, std::vector<UFOS::UFO>& ufos) {

    t_end_shooting -= delta;
    if (t_end_shooting <= .0f) m_is_shooting = false;

    if (!m_is_shooting) return 0u;

    sf::RectangleShape laser_beam(sf::Vector2f(5.0f, 800.0f));
    laser_beam.setOrigin(2.5f, 800.0f);
    laser_beam.setPosition(sf::Vector2f(m_pos.x - 10.0f, m_pos.y - m_texture_ptr->getSize().y / 2.0f));

    register uint32_t additional_score = 0u;

    for (register uint32_t i = ufos.size() - 1; i < ufos.size(); i--) {
        if (laser_beam.getGlobalBounds().intersects(ufos[i].get_global_bounds())) { ufos.erase(ufos.begin() + i); additional_score++; }
    }

    return additional_score;
}

void UFOS::Player::draw(sf::RenderTarget& window, sf::RenderStates states) const {

    if (m_texture_ptr == nullptr) return;

    if (m_is_shooting) {
        sf::RectangleShape laser_beam(sf::Vector2f(5.0f, 800.0f));
        laser_beam.setFillColor(m_laser_color);
        laser_beam.setOrigin(2.5f, 800.0f);
        laser_beam.setPosition(sf::Vector2f(m_pos.x - 10.0f, m_pos.y - m_texture_ptr->getSize().y / 2.0f));
        window.draw(laser_beam);
    }

    sf::Sprite sprite(*m_texture_ptr);
    sprite.setOrigin(m_texture_ptr->getSize().x / 2.0f, m_texture_ptr->getSize().y / 2.0f);
    sprite.setPosition(m_pos);

    window.draw(sprite, states);
}