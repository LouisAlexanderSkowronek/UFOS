#include "UFOS/loop.hpp"
#include "UFOS/init.hpp"

#include <cmath>

void UFOS::poll_events(sf::RenderWindow& window, std::array<bool, N_KEYS>& pressed_keys) {
    for (sf::Event e; window.pollEvent(e);) {
        switch (e.type) {
            case sf::Event::Closed: window.close(); return;
            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Left)  pressed_keys[0] = true;
                if (e.key.code == sf::Keyboard::Right) pressed_keys[1] = true;
                if (e.key.code == sf::Keyboard::Space) pressed_keys[2] = true; break;
            case sf::Event::KeyReleased:
                if (e.key.code == sf::Keyboard::Left)  pressed_keys[0] = false;
                if (e.key.code == sf::Keyboard::Right) pressed_keys[1] = false;
                if (e.key.code == sf::Keyboard::Space) pressed_keys[2] = false; break;
        
            default: break;
        }
    }
}

void UFOS::update(const float& delta, const std::array<bool, N_KEYS>& pressed_keys, sf::Text& text_fps, float& t_update_text_fps, uint32_t& score, sf::Text& text_score,
        UFOS::Player& player, std::vector<UFOS::UFO>& ufos, const sf::Texture* texture_ptr, std::mt19937& randint)
    {

    if (pressed_keys[0]) {
        player.move_x(-400.0f * delta);

        if (player.get_position_x() - player.get_size_x() / 2.0f < .0f) { player.set_position_x(player.get_size_x() / 2.0f); }
    }

    if (pressed_keys[1]) {
        player.move_x(400.0f * delta);
        if (player.get_position_x() + player.get_size_x() / 2.0f > 1200.0f) { player.set_position_x(1200.0f - player.get_size_x() / 2.0f); }
    }

    if (pressed_keys[2]) player.shoot(randint);

    score += player.update(delta, ufos);

    text_score.setString("Score: " + std::to_string(score));

    t_update_text_fps -= delta;
    if (t_update_text_fps <= .0f) { text_fps.setString(std::to_string(static_cast<uint32_t>(1.0f / delta)) + " fps"); t_update_text_fps = .1f; }

    UFOS::UFO::t_next_spawn -= delta;

    if (UFOS::UFO::t_next_spawn <= .0f) {
        ufos.emplace_back(
            &texture_ptr[randint() % (N_TEXTURES - 1)], // Texture
            sf::Vector2f(static_cast<float>(200u + randint() % 800u), -200.0f), // Position
            sf::Vector2f(.0f, static_cast<float>(50u + randint() % 200)) // Velocity
        );

        UFOS::UFO::t_next_spawn = (randint() % 60u) / 10.0f;
    }

    for (register uint32_t i = ufos.size() - 1u; i < ufos.size(); i--) {
        ufos[i].update(delta);

        if (ufos[i].get_position().y > 800u) ufos.erase(ufos.begin() + i);
    }
}

void UFOS::draw(sf::RenderWindow& window, const sf::Sprite& background, const sf::Text& text_fps, const sf::Text& text_score, const UFOS::Player& player, const std::vector<UFOS::UFO>& ufos) {

    window.clear();

    window.draw(background);

    for (register uint32_t i = 0; i < ufos.size(); i++) { window.draw(ufos[i]); }

    window.draw(player);

    window.draw(text_score);
    window.draw(text_fps);

    window.display();
}