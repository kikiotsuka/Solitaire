#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Game.h"

#include <iostream> //TODO remove me

/*
MASTER TODO:
CENTER ALL ORIGINS
*/

Game::Game() {
    srand(time(NULL));
    if (!texture.loadFromFile("solitaire_sprite_sheet.png")) {
        master_state = -1;
        detailed_state = -1;
    }
    texture.setSmooth(true);
    backside.set_texture(texture);
    init_card_home();
    reset_game();
}

void Game::reset_game() {
    deck.clear();
    deck_flipped.clear();
    field.clear();
    home.clear();
    cursor_move.clear();
    populate_deck();
    master_state = STATE_ANIMATION;
    detailed_state = STATE_ANIMATION_INITIALIZING_DECK;
    frame_counter = 0;
    card_counter = 0;
    col_tracker = sf::Vector2i(0, 0);
    skip = false;
    board_initialized = false;
    mouse_down = false;
}

/*
idea: use frame_counter to time distribution times
use card counter to track number of cards distributed, also to calculate relative positions
create path class that recalculates position based on (start, end, time), where velocity is function of time
0  1  2  3  4  5  6

1  2  3  4  5  6  7
   8  9 10 11 12 13
     14 15 16 17 18
        19 20 21 22
           23 24 25
              26 27
                 28

for (int i = 0; i < 7; i++)
    for (int j = 0; j <= i; j++)
*/
void Game::update() {
    if (master_state == STATE_ANIMATION) {
        frame_counter++;
        if (detailed_state == STATE_ANIMATION_INITIALIZING_DECK && card_counter <= 27) {
            if (skip || frame_counter >= to_frame(0.05f)) { //move card every 0.3 seconds
                //reset frame counter
                frame_counter = 0;
                //track card location
                //right to left one card at a time
                int col = col_tracker.x;
                col_tracker.y++;
                if (col_tracker.y > col_tracker.x) {
                    col_tracker.x++;
                    col_tracker.y = 0;
                }
                //obtain destination and offset height
                sf::Vector2f destination = field_rect[col].getPosition();
                destination.y += VERT_CARD_SPACING * field[col].size();
                //create path of card
                Path path(DECK_LOC, destination, to_frame(0.3f));
                sf::Vector2i pile(col, field[col].size());
                std::pair<sf::Vector2i, Path> moving_card(pile, path);
                //add to list of cards to move
                to_move.push_back(moving_card);
                //move card
                field[col].push_back(deck.back());
                deck.pop_back();
                card_counter++;
            }
        } else if (detailed_state == STATE_ANIMATION_MOVE_AND_FLIP_CARD) {

        } else if (detailed_state == STATE_ANIMATION_MOVING_CARD) {

        } else if (detailed_state == STATE_ANIMATION_FLIP_CARD) {

        } else if (detailed_state == STATE_ANIMATION_SOLVE_DECK) {

        } else {
            board_initialized = true;
        }
    }
    //animation updates
    if (master_state == STATE_ANIMATION) {
        //card mover
        for (int i = 0; i < to_move.size(); i++) {
            sf::Vector2i loc = to_move[i].first;
            if (skip) {
                field[loc.x][loc.y].set_position(to_move[i].second.finish());
            } else {
                field[loc.x][loc.y].set_position(to_move[i].second.next());
            }
            if (to_move[i].second.get_done()) {
                //field is full
                if (loc.y == loc.x && detailed_state == STATE_ANIMATION_INITIALIZING_DECK) {
                    if (skip) {
                        field[loc.x][loc.y].set_state(CARD_FACE_UP);
                    } else {
                        to_flip.push_back(std::pair<sf::Vector2i, Flip>(to_move[i].first, Flip(to_frame(0.3f))));
                    }
                }
                to_move.erase(to_move.begin() + i--);
            }
        }
        //card flipper
        for (int i = 0; i < to_flip.size(); i++) {
            sf::Vector2i loc = to_flip[i].first;
            if (skip) {
                field[loc.x][loc.y].set_scale(to_flip[i].second.finish());
                field[loc.x][loc.y].set_state(CARD_FACE_UP);
            } else {
                field[loc.x][loc.y].set_scale(to_flip[i].second.next());
                if (to_flip[i].second.get_half_done()) {
                    field[loc.x][loc.y].set_state(CARD_FACE_UP);
                }
            }
            if (to_flip[i].second.get_done()) {
                to_flip.erase(to_flip.begin() + i--);
            }
        }
        if (to_move.empty() && to_flip.empty() && board_initialized) {
            std::cout << "Animation sequence finished" << "\n";
            skip = false;
            master_state = STATE_PLAYING;
        }
    }
}

void Game::mouse_pressed(sf::Vector2f coord) {
    if (master_state == STATE_ANIMATION) {
        skip = true;
        while (skip) {
            update();
        }
    } else if (master_state == STATE_PLAYING) {
        int col;
        for (col = 0; col < 7; col++) {
            sf::RectangleShape r = field_rect[col];
            if (coord.x >= r.getPosition().x && coord.x <= r.getPosition().x + r.getSize().x)
                break;
        }
        int row;
        for (row = field[col].size() - 1; row >= 0; row--) {
            if (field[col][row].get_sprite().getGlobalBounds().contains(coord)) {
                if (true || field[col][row].get_state() == CARD_FACE_UP) {
                    std::cout << field[col][row].get_suit() << " " << field[col][row].get_value() << "\n";
                    break;
                } else {
                    row = -1;
                    break;
                }
            }
        }
        //check if clicked on home location
        if (row == -1) {
            if (col == 1) {

            }
            //check if clicked on home locations
        } else if (col != -1 && row != -1) { //card is valid to move
            mouse_down = true;
            for (int i = row; i < field[col].size(); i++) {
                cursor_move.push_back(sf::Vector2i(col, i));
            }
        } else { //card is flipped down, can't move it
            std::cout << "Card is flipped down, access to card is denied" << "\n";
        }
    }
}

void Game::mouse_released(sf::Vector2f coord) {
    if (mouse_down) { //validate card release location is valid or not

    }
}

void Game::mouse_moved(sf::Vector2f coord) {
    if (mouse_down) {
        for (int i = 0; i < cursor_move.size(); i++) {
            sf::Vector2i loc = cursor_move[i];
            field[loc.x][loc.y].set_center_position(sf::Vector2f(coord.x, coord.y + VERT_CARD_SPACING * i));
        }
    }
}

void Game::draw(sf::RenderWindow &window) {
    //draw boxes for card placable areas
    window.draw(deck_rect);
    for (int i = 0; i < field_rect.size(); i++) {
        window.draw(field_rect[i]);
    }
    for (int i = 0; i < home_rect.size(); i++) {
        window.draw(home_rect[i]);
    }
    //draw deck
    if (deck.size() > 0) {
        backside.set_position(DECK_LOC);
        backside.set_scale(1.0f);
        window.draw(backside.get_sprite());
    }
    //draw face up cards
    if (deck_flipped.size() > 0) {
        window.draw(deck_flipped.back().get_sprite());
    }
    //draw faceup sprites last
    std::vector<sf::Vector2i> faceups;
    //draw the cards on the field
    for (int i = 0; i < field.size(); i++) {
        for(int j = 0; j < field[i].size(); j++) {
            if (field[i][j].get_state() == CARD_FACE_DOWN) {
                backside.set_position(field[i][j].get_top_left());
                backside.set_scale(field[i][j].get_scale());
                window.draw(backside.get_sprite());
            } else if (field[i][j].get_state() == CARD_FACE_UP) {
                faceups.push_back(sf::Vector2i(i, j));
                //window.draw(field[i][j].get_sprite());
            }
        }
    }
    //draw faceup cards last as major priority
    for (int i = 0; i < faceups.size(); i++) {
        window.draw(field[faceups[i].x][faceups[i].y].get_sprite());
    }
}

void Game::populate_deck() {
    std::vector<Card> tmp_deck;
    for (int i = SUIT_CLUBS; i <= SUIT_SPADES; i++) {
        for (int j = 1; j <= 13; j++) {
            tmp_deck.push_back(Card(i, j, texture));
        }
    }
    while (tmp_deck.size() != 0) {
        int index = rand() % tmp_deck.size();
        tmp_deck[index].set_position(DECK_LOC);
        deck.push_back(tmp_deck[index]);
        tmp_deck.erase(tmp_deck.begin() + index);
    }
    for (int i = 0; i < 7; i++) {
        field.push_back(std::vector<Card>());
    }
}

void Game::init_card_home() {
    sf::RectangleShape r(sf::Vector2f((float) CARD_SPRITE_WIDTH, (float) CARD_SPRITE_HEIGHT));
    r.setPosition(DECK_LOC);
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineThickness(-1);
    r.setOutlineColor(sf::Color::Black);
    deck_rect = r;
    r.setPosition(HOME_LOC);
    for (int i = 0; i < 4; i++) {
        home_rect.push_back(r);
        r.setPosition(HOME_LOC.x + (i + 1) * (CARD_SPRITE_WIDTH + HORZ_CARD_SPACING), HOME_LOC.y);
    }
    float w = S_WIDTH / 7 - CARD_SPRITE_WIDTH;
    for (int i = 0; i < 7; i++) {
        r.setPosition(i * CARD_SPRITE_WIDTH + (i + 1) * w * 0.9, CARD_SPRITE_HEIGHT + 50);
        field_rect.push_back(r);
    }
}

//takes given time and calculates equivalent FPS value
float Game::to_frame(float time) {
    //1 second = 60 FPS
    return time * FPS;
}
