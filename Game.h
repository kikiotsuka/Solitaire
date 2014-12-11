#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Card.h"
#include "Path.h"
#include "Flip.h"
#include "Meta.h"

class Game {
private:
    const int CARD_NUMBER = 52;
    int master_state;
    int detailed_state;
    std::vector<Card> deck, deck_flipped;
    std::vector<std::vector<Card> > field;
    std::vector<std::vector<Card> > home;
    std::vector<std::pair<sf::Vector2i, Path> > to_move;
    std::vector<std::pair<sf::Vector2i, Flip> > to_flip;
    std::vector<sf::Vector2i> cursor_move;
    int frame_counter;
    int card_counter;
    sf::Vector2i col_tracker;
    bool skip;
    bool board_initialized;
    bool mouse_down;
    //draw card place locations
    sf::RectangleShape deck_rect;
    std::vector<sf::RectangleShape> field_rect;
    std::vector<sf::RectangleShape> home_rect;
    sf::Texture texture;
    Card backside;
    void populate_deck();
    void init_card_home();
    float to_frame(float time);
public:
    Game();
    void reset_game();
    void update();
    void mouse_pressed(sf::Vector2f coord);
    void mouse_released(sf::Vector2f coord);
    void mouse_moved(sf::Vector2f coord);
    void draw(sf::RenderWindow &window);
};

#endif // GAME_H