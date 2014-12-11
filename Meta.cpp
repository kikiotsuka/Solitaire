#include "Meta.h"

extern const int S_WIDTH = 800;
extern const int S_HEIGHT = 600;
extern const int FPS = 60;

extern const int CARD_SPRITE_WIDTH = 79;
extern const int CARD_SPRITE_HEIGHT = 123;

extern const int CARD_FACE_DOWN = 0;
extern const int CARD_FLIPPING = 1;
extern const int CARD_FACE_UP = 2;

extern const int SUIT_CLUBS = 0;
extern const int SUIT_DIAMONDS = 1;
extern const int SUIT_HEARTS = 2;
extern const int SUIT_SPADES = 3;
extern const int SUIT_BLANK = 4;

extern const int SUIT_RED = 1;
extern const int SUIT_BLACK = 2;

extern const int STATE_ANIMATION = 0;
extern const int STATE_PLAYING = 1;

extern const int STATE_ANIMATION_INITIALIZING_DECK = 0;
extern const int STATE_ANIMATION_MOVE_AND_FLIP_CARD = 1;
extern const int STATE_ANIMATION_MOVING_CARD = 2;
extern const int STATE_ANIMATION_FLIP_CARD = 3;
extern const int STATE_ANIMATION_SOLVE_DECK = 4;

extern const float VERT_CARD_SPACING = 23.0f;
extern const float HORZ_CARD_SPACING = 20.0f;
extern const sf::Vector2f DECK_LOC((S_WIDTH / 7 - CARD_SPRITE_WIDTH) * 0.9, 20);
extern const sf::Vector2f HOME_LOC(S_WIDTH - 4.2 * (HORZ_CARD_SPACING + CARD_SPRITE_WIDTH), 20);
