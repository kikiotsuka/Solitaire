#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Card.h"
#include "Meta.h"

class Game {
private:
    int master_state, detailed_state;
    std::vector<std::vector<std::vector<Card> > > field;
    std::vector<std::vector<sf::RectangleShape> > field_rect;
    //use for storing cards in animation, cursor moving
    std::vector<Card> transit, cursor;
    int frame_counter, card_counter;
    sf::Vector2i col_tracker;
    bool skip, mouse_down;
    sf::Texture texture;
    Card backside;
    //initialization
    std::vector<Card> populate_deck();
    void init_rect();
    bool valid_placement(int status, int group, int column, int row);
    int locate_card(sf::Vector2f coord, int &group, int &column, int &row);
    //animation sequence
    void anim_move_card();
    void anim_flip_card();
    void anim_return_card();

    float to_frame(float time);
public:
    Game();
    void reset_game();
    void update();
    void mouse_pressed(sf::Vector2f coord);
    void mouse_released(sf::Vector2f coord);
    void mouse_moved(sf::Vector2f coord);
    void mouse_left();
    void draw(sf::RenderWindow &window);
};

#endif // GAME_H