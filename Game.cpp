#include "Game.h"

#include <iostream> //TODO remove me

Game::Game() {
    srand(time(NULL));
    if (!texture.loadFromFile("solitaire_sprite_sheet.png")) {
        std::cerr << "Fatal error: Could not load sprite sheet" << "\n";
    }
    texture.setSmooth(true);
    backside.set_texture(texture);
    init_rect();
    reset_game();
}

void Game::reset_game() {
    //state vars
    master_state = STATE_ANIMATION;
    detailed_state = STATE_ANIMATION_INITIALIZING_DECK;
    //field handlers
    field.clear();
    std::vector<Card> populated_deck = populate_deck();
    std::vector<std::vector<Card> > deck;
    deck.push_back(populated_deck); //add face down deck
    deck.push_back(std::vector<Card>()); //add flipped deck
    std::vector<std::vector<Card> > home(4, std::vector<Card>()); //add empty homes
    std::vector<std::vector<Card> > play_field(7, std::vector<Card>()); //add empty fields
    //Reminder: field representation
    //field[0] = deck -> field[0][0][X] = face down deck; field[0][1][X] = face up deck
    //field[1] = home
    //field[2] = play field
    field.push_back(deck);
    field.push_back(home);
    field.push_back(play_field);

    transit.clear();
    cursor.clear();

    frame_counter = card_counter = 0;
    col_tracker = sf::Vector2i(0, 0);
    frame_delay = 0.05f;
    skip = mouse_down = false;
}

std::vector<Card> Game::populate_deck() {
    std::vector<Card> shuffle_deck, ret;
    //add all the cards
    for (int i = SUIT_CLUBS; i <= SUIT_SPADES; i++) {
        for (int j = 1; j <= 13; j++) {
            shuffle_deck.push_back(Card(i, j, texture));
        }
    }
    //randomly pull cards from sotrted deck
    while (shuffle_deck.size() != 0) {
        int index = rand() % shuffle_deck.size();
        shuffle_deck[index].set_center_position(field_rect[0][0].getPosition());
        ret.push_back(shuffle_deck[index]);
        shuffle_deck.erase(shuffle_deck.begin() + index);
    }
    return ret;
}

void Game::init_rect() {
    float spacer = 17.643f;
    float top_spacer = 30.179f; //space between deck and play field
    float card_spacer = 114.286f;
    sf::RectangleShape r(sf::Vector2f(CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT));
    r.setOrigin(CARD_SPRITE_WIDTH / 2.0f, CARD_SPRITE_HEIGHT / 2.0f);
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineThickness(-1.0f);
    r.setOutlineColor(sf::Color::Black);
    std::vector<sf::RectangleShape> deck, home, play_field;
    for (int i = 0; i < 2; i++) {
        r.setPosition(sf::Vector2f(spacer + CARD_SPRITE_WIDTH / 2.0f + card_spacer * i,
                                    spacer + CARD_SPRITE_HEIGHT / 2.0f));
        deck.push_back(sf::RectangleShape(r));
    }
    for (int i = 3; i < 7; i++) {
        r.setPosition(sf::Vector2f(spacer + CARD_SPRITE_WIDTH / 2.0f + card_spacer * i,
                                    spacer + CARD_SPRITE_HEIGHT / 2.0f));
        home.push_back(sf::RectangleShape(r));
    }
    for (int i = 0; i < 7; i++) {
        r.setPosition(sf::Vector2f(spacer + CARD_SPRITE_WIDTH / 2.0f + card_spacer * i,
            spacer + CARD_SPRITE_HEIGHT * 1.5f + top_spacer));
        play_field.push_back(sf::RectangleShape(r));
    }
    field_rect.push_back(deck);
    field_rect.push_back(home);
    field_rect.push_back(play_field);
}

void Game::update() {
    if (master_state == STATE_ANIMATION) {
        frame_counter++;
        if (skip || frame_counter >= to_frame(frame_delay)) {
            frame_counter = 0;
            if (detailed_state == STATE_ANIMATION_INITIALIZING_DECK) {
                if (card_counter <= 27) {
                    //destination of card
                    int col = col_tracker.x;
                    sf::Vector2f destination = field_rect[PLAY_FIELD][col].getPosition();
                    destination.y += VERT_CARD_SPACING * col_tracker.y;
                    int animation_type = STATE_ANIMATION_MOVING_CARD;
                    if (col == col_tracker.y) {
                        animation_type = STATE_ANIMATION_MOVE_AND_FLIP_CARD;
                    }
                    Position p(destination, sf::Vector3i(DECK, 0, field[DECK][0].size()), sf::Vector3i(PLAY_FIELD, col, col_tracker.y));
                    field[DECK][0].back().init_animation(animation_type, p, to_frame(0.3f));
                    transit.push_back(field[DECK][0].back());
                    field[DECK][0].pop_back();
                    card_counter++;
                    col_tracker.y++;
                    if (col_tracker.y > col_tracker.x) {
                        col_tracker.x++;
                        col_tracker.y = 0;
                    }
                }
            } else if (detailed_state == STATE_ANIMATION_RETURN_CARD) {
                if (!cursor.empty()) {
                    Card c = cursor.front();
                    Position p = c.get_position_data();
                    p.coord.second = p.coord.first;
                    p.loc.second = p.loc.first;
                    c.init_animation(STATE_ANIMATION_MOVING_CARD, p, to_frame(0.2f));
                    transit.push_back(c);
                    cursor.erase(cursor.begin());
                }
            } else if (detailed_state == STATE_ANIMATION_FLIP_DECK) {
                if (!field[DECK][1].empty()) {
                    Card c = field[DECK][1].back();
                    Position p = c.get_position_data();
                    p.coord.second = field_rect[DECK][0].getPosition();
                    p.loc.second = sf::Vector3i(DECK, 0, field[DECK][0].size());
                    c.init_animation(STATE_ANIMATION_MOVING_CARD, p, to_frame(0.3f));
                    transit.push_back(c);
                    field[DECK][1].pop_back();
                }
            } else if (detailed_state == STATE_ANIMATION_SOLVE_DECK) {
                //TODO implement solving deck
            }
        }
        //update aimations
        for (int i = 0; i < transit.size(); i++) {
            if (skip) {
                transit[i].finish();
            } else {
                transit[i].next();
            }
            if (transit[i].animation_finish()) {
                Position p = transit[i].get_position_data();
                sf::Vector3i loc = p.loc.second;
                field[loc.x][loc.y].push_back(transit[i]);
                transit.erase(transit.begin() + i--);
                if (transit.empty()) {
                    if (detailed_state == STATE_ANIMATION_INITIALIZING_DECK) {
                        if (card_counter > 27) {
                            master_state = STATE_PLAYING;
                        }
                    } else if (detailed_state == STATE_ANIMATION_FLIP_DECK) {
                        if (field[DECK][1].empty()) {
                            master_state = STATE_PLAYING;
                        }
                    }else if (cursor.empty()) {
                        master_state = STATE_PLAYING;
                    }
                }
            }
        }
    }
}

bool Game::valid_placement(int status, int group, int column, int row) {
    if (status == -1) return false;
    Card c = cursor.front();
    if (status == EMPTY_SPOT) {
        if (group == HOME && c.get_value() == 1 && cursor.size() == 1) {
            return true;
        } else {
            if (group == PLAY_FIELD && c.get_value() == 13) {
                return true;
            }
        }
    } else {
        Card above = field[group][column][row];
        if (status == HOME) {
            if (above.get_value() + 1 == c.get_value()) {
                return above.get_suit() == c.get_suit();
            }
        } else if (status == PLAY_FIELD) {
            if (above.get_value() == c.get_value() + 1) {
                return above.get_color() ^ c.get_color();
            }
        }
    }
    return false;
}

int Game::locate_card(sf::Vector2f coord, int &group, int &column, int &row) {
    group = column = row = -1;
    for (int i = DECK; i <= PLAY_FIELD; i++) {
        for (int j = 0; j < field[i].size(); j++) {
            for (int k = field[i][j].size() - 1; k >= 0; k--) {
                Card c = field[i][j][k];
                if (c.get_sprite().getGlobalBounds().contains(coord)) {
                    //record the location
                    group = i;
                    //note, these are flipped because of the flipped representation of solitaire field
                    row = k;
                    column = j;
                    return i; //return the group
                }
            }
        }
    }
    for (int i = 0; i < field_rect.size(); i++) {
        for (int j = 0; j < field_rect[i].size(); j++) {
            sf::RectangleShape r = field_rect[i][j];
            if (r.getGlobalBounds().contains(coord)) {
                group = i;
                column = j;
                row = -1;
                return EMPTY_SPOT; //empty location
            }
        }
    }
    return -1; //invalid loc
}

void Game::anim_move_card() {
    master_state = STATE_ANIMATION;
    detailed_state = STATE_ANIMATION_MOVING_CARD;
}

void Game::anim_flip_card() {
    master_state = STATE_ANIMATION;
    detailed_state = STATE_ANIMATION_FLIP_CARD;
}

void Game::anim_return_card() {
    master_state = STATE_ANIMATION;
    detailed_state = STATE_ANIMATION_RETURN_CARD;
    frame_delay = 0.05f;
}

void Game::anim_move_and_flip_card() {
    master_state = STATE_ANIMATION;
    detailed_state = STATE_ANIMATION_MOVE_AND_FLIP_CARD;
}

void Game::anim_flip_deck() {
    master_state = STATE_ANIMATION;
    detailed_state = STATE_ANIMATION_FLIP_DECK;
    frame_delay = 0.03f;
}

void Game::mouse_pressed(sf::Vector2f coord) {
    if (master_state == STATE_ANIMATION) {
        skip = true;
        while (master_state != STATE_PLAYING) {
            update();
        }
        skip = false;
        if (detailed_state != STATE_ANIMATION_FLIP_CARD && detailed_state != STATE_ANIMATION_MOVING_CARD) {
            return;
        }
    }
    int group, column, row;
    int status = locate_card(coord, group, column, row);
    if (status >= HOME && status <= PLAY_FIELD || status == DECK && column == 1) { //clicked some valid location on field
        //click on a face up card
        if (field[group][column][row].get_flip_state() == CARD_FACE_UP) { //add card to cursor
            mouse_down = true;
            for (int i = row; i < field[group][column].size(); i++) {
                Card c = field[group][column][i];
                Position p = c.get_position_data();
                p.coord.first = field[group][column][i].get_center();
                p.loc.first = sf::Vector3i(group, column, i);
                c.set_position_data(p);
                cursor.push_back(c);
                field[group][column].erase(field[group][column].begin() + i--);
                mouse_moved(coord);
            }
        } else { //card is face down, see if its at the front of the pile
            if (field[group][column].size() - 1 == row) {
                anim_flip_card();
                field[group][column][row].init_animation(STATE_ANIMATION_FLIP_CARD, to_frame(0.3f));
                transit.push_back(field[group][column][row]);
                field[group][column].pop_back();
            }
        }
    } else if (status == DECK || status == EMPTY_SPOT && group == DECK) { //if deck group was clicked
        if (field[DECK][0].empty()) { //deck is empty, return deck contents
            if (!field[DECK][1].empty()) {
                anim_flip_deck();
                for (int i = 0; i < field[DECK][1].size(); i++) {
                    field[DECK][1][i].set_flip_state(CARD_FACE_DOWN);
                }
            }
        } else if (status == DECK) { //move and flip card
            anim_move_card();
            Card c = field[DECK][0].back();
            c.set_flip_state(CARD_FACE_UP);
            Position p = c.get_position_data();
            p.coord.second = field_rect[DECK][1].getPosition();
            p.loc.second = sf::Vector3i(DECK, 1, field[DECK][1].size());
            c.init_animation(STATE_ANIMATION_MOVING_CARD, p, to_frame(0.25f));
            transit.push_back(c);
            field[DECK][0].pop_back();
        }
    }
}

void Game::mouse_released(sf::Vector2f coord) {
    if (mouse_down) {
        mouse_down = false;
        int group, column, row;
        int status = locate_card(coord, group, column, row);
        if (valid_placement(status, group, column, row)) { //move cards to new location if valid
            anim_move_card();
            for (int i = 0; i < cursor.size(); i++) {
                Position p = cursor[i].get_position_data();
                p.loc.second = sf::Vector3i(group, column, row + i + 1);
                p.coord.second = field_rect[group][column].getPosition();
                if (group != HOME) {
                    p.coord.second.y += VERT_CARD_SPACING * (row + i + 1);
                }
                cursor[i].init_animation(STATE_ANIMATION_MOVING_CARD, p, to_frame(0.1f));
                transit.push_back(cursor[i]);
            }
            cursor.clear();
        } else {
            anim_return_card();
        }
    }
}

void Game::mouse_moved(sf::Vector2f coord) {
    if (mouse_down) {
        for (int i = 0; i < cursor.size(); i++) {
            cursor[i].set_cursor_hold_position(sf::Vector2f(coord.x, coord.y + VERT_CARD_SPACING * i));
        }
    }
}

void Game::mouse_left() {
    if (mouse_down) {
        mouse_down = false;
        anim_return_card();
    }
}

void Game::draw(sf::RenderWindow &window) {
    //draw all rects
    for (int i = 0; i < field_rect.size(); i++) {
        for (int j = 0; j < field_rect[i].size(); j++) {
            window.draw(field_rect[i][j]);
        }
    }
    //draw deck if it't not empty
    if (!field[DECK][0].empty()) {
        field[DECK][0].back().draw(window, backside);
    }
    //draw cards on unflipped deck
    if (!field[DECK][1].empty()) {
        field[DECK][1].back().draw(window, backside);
    }
    //draw cards on home
    for (int i = 0; i < field[HOME].size(); i++) {
        if (!field[HOME][i].empty()) {
            field[HOME][i].back().draw(window, backside);
        }
    }
    //draw cards on field
    for (int i = 0; i < field[PLAY_FIELD].size(); i++) {
        for (int j = 0; j < field[PLAY_FIELD][i].size(); j++) {
            field[PLAY_FIELD][i][j].draw(window, backside);
        }
    }
    //draw cards in animation state
    for (int i = 0; i < transit.size(); i++) {
        transit[i].draw(window, backside);
    }
    //draw cards on cursor
    for (int i = 0; i < cursor.size(); i++) {
        cursor[i].draw(window, backside);
    }
}

//takes given time and calculates equivalent FPS value
float Game::to_frame(float time) {
    //1 second = 60 FPS
    return time * FPS;
}
