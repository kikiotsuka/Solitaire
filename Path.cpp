#include <SFML/Graphics.hpp>
#include "Path.h"

Path::Path(sf::Vector2f start_pos, sf::Vector2f end_pos, float frames) {
    this->start_pos = start_pos;
    this->end_pos = end_pos;
    current_pos = start_pos;
    this->frames = frames;
    float dx = (end_pos.x - start_pos.x) / frames;
    float dy = (end_pos.y - start_pos.y) / frames;
    v.x = dx;
    v.y = dy;
    done = false;
}

sf::Vector2f Path::next() {
    current_pos.x += v.x;
    current_pos.y += v.y;
    frames--;
    if (frames <= 0) {
        current_pos.x = end_pos.x;
        current_pos.y = end_pos.y;
        done = true;
    }
    return current_pos;
}

sf::Vector2f Path::finish() {
    frames = 0;
    return next();
}

bool Path::get_done() { return done; }
