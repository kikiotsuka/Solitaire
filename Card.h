#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include "Meta.h"

class Card {
private:
    int suit;
    int value;
    int color;
    int state;
    sf::Vector2f loc;
    sf::Sprite s;
    void init(int suit, int value);
    void init_texture(sf::Texture &t);
public:
    Card();
    Card(int suit, int value, sf::Texture &t);
    //set if card is facing up, flipping, or down
    void set_state(int val);
    void set_texture(sf::Texture &t);

    int get_suit();
    int get_value();
    int get_color();
    int get_state();
    sf::Vector2f get_loc();

    void set_scale(float scale);
    float get_scale();
    sf::Sprite get_sprite();

    //position related methods
    void set_position(sf::Vector2f pos);
    void set_center_position(sf::Vector2f pos);
    void set_size(sf::Vector2f shape_size);
    sf::Vector2f get_top_left();
    sf::Vector2f get_top_right();
    sf::Vector2f get_top_center();
    sf::Vector2f get_bottom_left();
    sf::Vector2f get_bottom_right();
    sf::Vector2f get_center();
    float get_center_x();
    float get_center_y();
    float get_left();
    float get_right();
    float get_top();
    float get_bottom();
    float get_width();
    float get_height();
};

#endif // CARD_H
