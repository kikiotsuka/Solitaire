#include "Card.h"

Card::Card() {
    init(SUIT_BLANK, 1);
    color = 0;
    flip_state = CARD_FACE_UP;
}

Card::Card(int suit, int value, sf::Texture &t) {
    init(suit, value);
    set_texture(t);
}

void Card::init(int suit, int value) {
    this->suit = suit;
    this->value = value;
    if (suit == SUIT_DIAMONDS || suit == SUIT_HEARTS) {
        color = SUIT_RED;
    } else {
        color = SUIT_BLACK;
    }
    flip_state = CARD_FACE_DOWN;
    animation_state = -1;
    animation = NULL;
}

void Card::init_animation(int animation_state, Position p, float frames) { //moving
    this->animation_state = animation_state;
    this->p = p;
    p.coord.first = get_center();
    animation = new Path(p.coord.first, p.coord.second, frames);
}

void Card::init_animation(int animation_state, float frames) { //flipping
    this->animation_state = animation_state;
    animation = new Flip(frames);
    //no need to change the destination/coordinates because it's already there
}

void Card::next() {
    if (animation != NULL) {
        sf::Vector2f next_frame = animation->next();
        if (animation_state == STATE_ANIMATION_MOVE_AND_FLIP_CARD ||
            animation_state == STATE_ANIMATION_MOVING_CARD) {
            set_center_position(next_frame);
        } else if (animation_state == STATE_ANIMATION_FLIP_CARD) {
            if (flip_state == CARD_FACE_DOWN && next_frame.x < 0) {
                flip_state = CARD_FACE_UP;
            }
            if (next_frame.x < 0) next_frame.x = -next_frame.x;
            set_scale(next_frame);
        }
        if (animation->get_done()) {
            if (animation_state == STATE_ANIMATION_MOVE_AND_FLIP_CARD) {
                init_animation(STATE_ANIMATION_FLIP_CARD, animation->get_frames());
            } else {
                delete animation;
                animation = NULL;
            }
        }
    }
}

void Card::finish() {
    if (animation != NULL) {
        sf::Vector2f final_frame = animation->finish();
        if (animation_state == STATE_ANIMATION_MOVE_AND_FLIP_CARD ||
            animation_state == STATE_ANIMATION_MOVING_CARD) {
            set_center_position(final_frame);
        } else if (animation_state == STATE_ANIMATION_FLIP_CARD) {
            flip_state = CARD_FACE_UP;
            if (final_frame.x < 0) final_frame.x = -final_frame.x;
            set_scale(final_frame);
        }
        if (animation_state == STATE_ANIMATION_MOVE_AND_FLIP_CARD) {
            init_animation(STATE_ANIMATION_FLIP_CARD, animation->get_frames());
            animation->finish(); //this will make animation null in the next call
        } else {
            delete animation;
            animation = NULL;
        }
    }
}

void Card::set_position_data(Position p) {
    this->p = p;
}

Position Card::get_position_data() {
    return p;
}

bool Card::animation_finish() {
    return animation == NULL;
}

void Card::set_texture(sf::Texture &t) {
    s.setTexture(t);
    sf::IntRect r((value - 1) * CARD_SPRITE_WIDTH, suit * CARD_SPRITE_HEIGHT, CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT);
    s.setTextureRect(r);
    s.setOrigin(CARD_SPRITE_WIDTH / 2, CARD_SPRITE_HEIGHT / 2);
}

void Card::set_flip_state(int flip_state) { this->flip_state = flip_state; }

int Card::get_suit() { return suit; }
int Card::get_value() { return value; }
int Card::get_color() { return color; }
int Card::get_flip_state() { return flip_state; }
int Card::get_animation_state() { return animation_state; }

void Card::set_scale(sf::Vector2f scale) { s.setScale(scale); }
sf::Vector2f Card::get_scale() { return s.getScale(); }

void Card::set_top_left_position(sf::Vector2f pos) {
    pos.x -= CARD_SPRITE_WIDTH / 2;
    pos.y -= CARD_SPRITE_HEIGHT / 2;
    s.setPosition(pos);
}

void Card::set_center_position(sf::Vector2f pos) { s.setPosition(pos); }

void Card::set_cursor_hold_position(sf::Vector2f pos) {
    pos.y += (CARD_SPRITE_HEIGHT - VERT_CARD_SPACING) / 2.0f;
    s.setPosition(pos);
}

sf::Vector2f Card::get_top_left() { return sf::Vector2f(get_left(), get_top()); }
sf::Vector2f Card::get_top_right() { return sf::Vector2f(get_right(), get_top()); }
sf::Vector2f Card::get_top_center() { return sf::Vector2f(get_center_x(), get_top()); }
sf::Vector2f Card::get_bottom_left() { return sf::Vector2f(get_left(), get_bottom()); }
sf::Vector2f Card::get_bottom_right() { return sf::Vector2f(get_right(), get_bottom()); }
sf::Vector2f Card::get_center() { return sf::Vector2f(get_center_x(), get_center_y()); }
float Card::get_center_x() { return s.getPosition().x; }
float Card::get_center_y() { return s.getPosition().y; }
float Card::get_left() { return get_center_x() - CARD_SPRITE_WIDTH / 2; }
float Card::get_right() { return get_center_x() + CARD_SPRITE_WIDTH / 2; }
float Card::get_top() { return get_center_y() - CARD_SPRITE_HEIGHT / 2; }
float Card::get_bottom() { return get_center_y() + CARD_SPRITE_HEIGHT / 2; }
float Card::get_width() { return s.getTextureRect().width; }
float Card::get_height() { return s.getTextureRect().height; }

sf::Sprite Card::get_sprite() { return s; }
void Card::draw(sf::RenderWindow &window, Card &backside) {
    if (flip_state == CARD_FACE_UP) {
        window.draw(s);
    } else {
        backside.set_center_position(get_center());
        backside.set_scale(get_scale());
        window.draw(backside.get_sprite());
    }
}
