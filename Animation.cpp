#include "Animation.h"

Animation::Animation(int frames) {
    this->frames = frames;
    frame_counter = 0;
    done = false;
}

sf::Vector2f Animation::next() { }

sf::Vector2f Animation::finish() {
    frame_counter = frames;
    return next();
}

bool Animation::get_done() { return done; }
int Animation::get_frames() { return frames; }