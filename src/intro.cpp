#include <SFML/Graphics.hpp>

#include "UFOS/ufo.hpp"
#include "UFOS/player.hpp"

void intro(const float& delta, sf::RenderWindow& window, bool& game_has_started, const sf::Sprite& bg, const UFOS::Player& player, const sf::Font& font) {
    for (sf::Event e; window.pollEvent(e);) {
        if (e.type == sf::Event::Closed) window.close(); return;
    }

    static float countdown = 24.5f;
    
    sf::Text text_countdown("Game starts in " + std::to_string(static_cast<uint32_t>(countdown)) + "s", font, 45u);
    text_countdown.setPosition(600u - text_countdown.getLocalBounds().width / 2.0f, 400u - text_countdown.getLocalBounds().height / 2.0f);

    countdown -= delta;

    if (countdown <= .0f) game_has_started = true;

    window.clear(sf::Color(0, 0, 3));

    window.draw(bg);
    window.draw(player);
    window.draw(text_countdown);

    window.display();
}