#include <SFML/Graphics.hpp>
#include "Path.h"

Path::Path(sf::Vector2f start_pos, sf::Vector2f end_pos, int frames)
        : Animation(frames) {
    this->start_pos = start_pos;
    this->end_pos = end_pos;
    current_pos = start_pos;
    float dx = (end_pos.x - start_pos.x) / (float)frames;
    float dy = (end_pos.y - start_pos.y) / (float)frames;
    v.x = dx;
    v.y = dy;
}

sf::Vector2f Path::next() {
    current_pos.x += v.x;
    current_pos.y += v.y;
    frame_counter++;
    if (frame_counter >= frames) {
        current_pos.x = end_pos.x;
        current_pos.y = end_pos.y;
        done = true;
    }
    return current_pos;
}
