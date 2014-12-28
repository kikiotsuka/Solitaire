#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Path.h"
#include "Flip.h"
#include "Position.h"
#include "Meta.h"

class Card {
private:
    //state vars
    int suit, value, color, flip_state, animation_state;
    sf::Sprite s;
    //animation
    Animation *animation;
    Position p;
    //for constructor use
    void init(int suit, int value);
    void init_texture(sf::Texture &t);
public:
    Card();
    Card(int suit, int value, sf::Texture &t);

    //animation
    //animation state will be flip, move, or flip and move
    //destination contains the coordinates of the destination
    //destination_loc is the coordinate of the destination
    void init_animation(int animation_state, Position p, float frames);
    void init_animation(int animation_state, float frames); //flipping
    void next();
    void finish();
    void set_position_data(Position p);
    Position get_position_data();
    bool animation_finish();

    void set_texture(sf::Texture &t);
    void set_flip_state(int flip_state);

    int get_suit();
    int get_value();
    int get_color();
    int get_flip_state();
    int get_animation_state();

    //scaling
    void set_scale(sf::Vector2f scale);
    sf::Vector2f get_scale();

    //position methods
    void set_top_left_position(sf::Vector2f pos);
    void set_center_position(sf::Vector2f pos);
    void set_cursor_hold_position(sf::Vector2f pos);
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

    sf::Sprite get_sprite();
    void draw(sf::RenderWindow &window, Card &backside);
};

#endif // CARD_H
