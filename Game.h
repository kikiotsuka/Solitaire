#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <iostream>
#include <cstdio>
#include "Card.h"
#include "Meta.h"

class Game {
private:
    int master_state, detailed_state;
    std::vector<std::vector<std::vector<Card> > > field;
    std::vector<std::vector<sf::RectangleShape> > field_rect;
    std::vector<int> ace_locations;
    //use for storing cards in animation, cursor moving
    std::vector<Card> transit, cursor;
    int frame_counter, card_counter;
    float frame_delay;
    sf::Vector2i col_tracker;
    bool skip, mouse_down;
    bool three_card_rule;
    bool won, solvable;
    bool kill; //for failure to load things
    sf::Texture texture;
    Card backside;
    //text for information
    sf::Font font;
    sf::Text info_text, won_text, solvable_text;
    //initialization
    std::vector<Card> populate_deck();
    void init_rect();
    void init_text();
    bool valid_placement(int status, int group, int column, int row);
    int locate_card(sf::Vector2f coord, int &group, int &column, int &row);
    //animation sequence
    void anim_move_card();
    void anim_flip_card();
    void anim_return_card();
    void anim_move_and_flip_card();
    void anim_flip_deck();
    //game state checking
    bool has_won();
    bool is_solvable();

    float to_frame(float time);
public:
    Game();
    void reset_game();
    void update();
    void mouse_pressed(sf::Vector2f coord);
    void mouse_released(sf::Vector2f coord);
    void mouse_moved(sf::Vector2f coord);
    void mouse_left();
    void flip_draw_mode();
    void auto_solve();
    bool get_kill();
    void draw(sf::RenderWindow &window);
};

#endif // GAME_H