#include <SFML/Graphics.hpp>
#include "Card.h"
#include "Meta.h"

Card::Card() {
    init(SUIT_BLANK, 1);
    color = 0;
    state = CARD_FACE_UP;
}

Card::Card(int suit, int value, sf::Texture &t) {
    init(suit, value);
    init_texture(t);
}

void Card::init(int suit, int value) {
    this->suit = suit;
    this->value = value;
    if (suit == SUIT_DIAMONDS || suit == SUIT_HEARTS) {
        color = SUIT_RED;
    } else {
        color = SUIT_BLACK;
    }
    state = CARD_FACE_DOWN;
}

void Card::init_texture(sf::Texture &t) {
    s.setTexture(t);
    sf::IntRect r((value - 1) * CARD_SPRITE_WIDTH, suit * CARD_SPRITE_HEIGHT, CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
    s.setTextureRect(r);
    s.setOrigin(CARD_SPRITE_WIDTH / 2, CARD_SPRITE_HEIGHT / 2);
}

void Card::set_state(int val) { state = val; }
void Card::set_texture(sf::Texture &t) {
    init_texture(t);
}

int Card::get_suit() { return suit; }
int Card::get_value() { return value; }
int Card::get_color() { return color; }
int Card::get_state() { return state; }
sf::Vector2f Card::get_loc() { return loc; }

void Card::set_scale(float scale) { s.setScale(sf::Vector2f(scale, 1.0f)); }
float Card::get_scale() { return s.getScale().x; }
sf::Sprite Card::get_sprite() { return s; }


void Card::set_position(sf::Vector2f pos) {
    loc = pos;
    s.setPosition(sf::Vector2f(loc.x + CARD_SPRITE_WIDTH / 2, loc.y + CARD_SPRITE_HEIGHT / 2));
}

void Card::set_center_position(sf::Vector2f pos) {
    s.setPosition(pos);
    loc.x = pos.x - CARD_SPRITE_WIDTH / 2;
    loc.y = pos.y - CARD_SPRITE_HEIGHT / 2;
}

void Card::set_top_position(sf::Vector2f pos) {
    set_center_position(pos);
    s.setPosition(sf::Vector2f(pos.x, pos.y + (CARD_SPRITE_HEIGHT - VERT_CARD_SPACING) / 2.0f));
}

void Card::set_size(sf::Vector2f shape_size) {
    //todo implement me
}

sf::Vector2f Card::get_top_left() { return sf::Vector2f(get_left(), get_top()); }
sf::Vector2f Card::get_top_right() { return sf::Vector2f(get_right(), get_top()); }
sf::Vector2f Card::get_top_center() { return sf::Vector2f(get_center_x(), get_top()); }
sf::Vector2f Card::get_bottom_left() { return sf::Vector2f(get_left(), get_bottom()); }
sf::Vector2f Card::get_bottom_right() { return sf::Vector2f(get_right(), get_bottom()); }
sf::Vector2f Card::get_center() { return sf::Vector2f(get_center_x(), get_center_y()); }
float Card::get_center_x() { return loc.x + get_width() / 2; }
float Card::get_center_y() { return loc.y + get_height() / 2; }
float Card::get_left() { return loc.x; }
float Card::get_right() { return loc.x + get_width(); }
float Card::get_top() { return loc.y; }
float Card::get_bottom() { return loc.y + get_height(); }
float Card::get_width() { return CARD_SPRITE_WIDTH; }
float Card::get_height() { return CARD_SPRITE_HEIGHT; }
