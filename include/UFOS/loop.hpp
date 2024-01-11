#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <vector>
#include <random>

#include "ufo.hpp"
#include "player.hpp"

#define N_KEYS 3U

namespace UFOS {

    void poll_events(sf::RenderWindow& window, std::array<bool, N_KEYS>& pressed_keys);

    void update(const float& delta, const std::array<bool, N_KEYS>& pressed_keys, sf::Text& text_fps, float& t_text_fps, uint32_t& score, sf::Text& text_score,
        UFOS::Player& player, std::vector<UFOS::UFO>& ufos, const sf::Texture* texture_ptr, std::mt19937& random_generator
    );

    void draw(sf::RenderWindow& window, const sf::Sprite& background, const sf::Text& text_fps, const sf::Text& text_score, const UFOS::Player& player, const std::vector<UFOS::UFO>& ufos);

} // namespace UFOS