#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Meta.h"
#include "Game.h"

#include <iostream> //TODO remove me

void handle_events(sf::RenderWindow &window, Game &game);

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(S_WIDTH, S_HEIGHT), "Solitaire - By Mitsuru Otsuka", sf::Style::Close, settings);

    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(FPS);

    Game game;

    while (window.isOpen()) {
        handle_events(window, game);
        //if user quit the game
        if (!window.isOpen()) break;
        game.update();

        window.clear(sf::Color(14, 142, 57));
        game.draw(window);
        window.display();
    }
}

void handle_events(sf::RenderWindow &window, Game &game) {
    sf::Event e;
    while (window.pollEvent(e)) {
        switch(e.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Q) {
                window.close();
                break;
            } else if (e.key.code == sf::Keyboard::F2) {
                game.reset_game();
                break;
            } else if (e.key.code == sf::Keyboard::S) {
                game.auto_solve();
                break;
            }
        case sf::Event::MouseButtonPressed:
            if (e.mouseButton.button == sf::Mouse::Left) {
                game.mouse_pressed(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (e.mouseButton.button == sf::Mouse::Left) {
                game.mouse_released(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        case sf::Event::MouseMoved:
            game.mouse_moved(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));
            break;
        case sf::Event::MouseLeft:
            game.mouse_left();
            break;
        }
    }
}
