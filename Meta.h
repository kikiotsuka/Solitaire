#ifndef META_H
#define META_H

#include <SFML/Graphics.hpp>

//game data
extern const int S_WIDTH;
extern const int S_HEIGHT;
extern const int FPS;

//card data
extern const int CARD_SPRITE_WIDTH;
extern const int CARD_SPRITE_HEIGHT;

extern const int CARD_FACE_DOWN;
extern const int CARD_FACE_UP;

extern const int SUIT_CLUBS;
extern const int SUIT_DIAMONDS;
extern const int SUIT_HEARTS;
extern const int SUIT_SPADES;
extern const int SUIT_BLANK;

extern const int SUIT_RED;
extern const int SUIT_BLACK;

//master state
extern const int STATE_ANIMATION;
extern const int STATE_PLAYING;

//detailed state
extern const int STATE_ANIMATION_INITIALIZING_DECK;
extern const int STATE_ANIMATION_RETURN_CARD;
extern const int STATE_ANIMATION_MOVE_AND_FLIP_CARD;
extern const int STATE_ANIMATION_MOVING_CARD;
extern const int STATE_ANIMATION_FLIP_CARD;
extern const int STATE_ANIMATION_FLIP_DECK;
extern const int STATE_ANIMATION_SOLVE_DECK;

//spacing the cards
extern const float VERT_CARD_SPACING;
extern const float HORZ_CARD_SPACING;

//group identifiers
extern const int DECK;
extern const int HOME;
extern const int PLAY_FIELD;
extern const int EMPTY_SPOT;

#endif // META_H
