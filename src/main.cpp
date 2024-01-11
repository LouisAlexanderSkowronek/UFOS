#include <SFML/Graphics.hpp>

#include <array>
#include <vector>
#include <random>
#include <iostream>

#include "UFOS/init.hpp"
#include "UFOS/loop.hpp"
#include "UFOS/ufo.hpp"
#include "UFOS/player.hpp"

float UFOS::UFO::t_next_spawn;

extern void intro(const float& delta, sf::RenderWindow& window, bool& game_has_started, const sf::Sprite& bg, const UFOS::Player& player, const sf::Font& font);

int main() {
    sf::RenderWindow window(sf::VideoMode(1200u, 800u), "UFOS - UFOS From Outer Space", sf::Style::Close);

    std::mt19937 randint(time(nullptr));

    const std::array<sf::Font, N_FONTS>       fonts      = UFOS::load_fonts("../assets/fonts/fonts.txt");
    const std::array<sf::Texture, N_TEXTURES> textures   = UFOS::load_textures("../assets/textures/textures.txt");
    std::array<sf::Music, N_MUSICS>&          musics     = UFOS::load_musics("../assets/musics/musics.txt");
    const sf::Sprite                          background = UFOS::render_background(randint);

    musics[0].setLoop(true);
    musics[0].play();

    float t_update_text_fps = .1f;
    sf::Text text_fps("69 fps", fonts[0]);
    text_fps.setPosition(.0f, 20.0f);
    text_fps.setStyle(sf::Text::Style::Regular);

    sf::Text text_score("Score: 0", fonts[0]);
    text_score.setPosition(1000.0f, 20.0f);
    text_score.setStyle(sf::Text::Style::Bold);

    bool game_has_started = false;

    float countdown = 24.0f;

    sf::Clock clock;
    std::array<bool, N_KEYS> pressed_keys;
    pressed_keys.fill(false);

    UFOS::UFO::t_next_spawn = (randint() % 60u) / 10.0f;

    UFOS::Player player(&textures[5u], sf::Vector2f(600.0f, 680.0f));

    std::vector<UFOS::UFO> ufos;
    ufos.reserve(5u);

    uint32_t score = 0u;

    while (window.isOpen()) {
        const float&& elapsed_time = clock.restart().asSeconds();

        UFOS::poll_events(window, pressed_keys);

        if (!game_has_started) { intro(elapsed_time, window, game_has_started, background, player, fonts[0]); continue; }

        UFOS::update(elapsed_time, pressed_keys, text_fps, t_update_text_fps, score, text_score, player, ufos, textures.data(), randint);

        UFOS::draw(window, background, text_fps, text_score, player, ufos);
    }
}