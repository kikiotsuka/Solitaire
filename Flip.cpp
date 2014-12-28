#include "Flip.h"

Flip::Flip(int frames) : Animation(frames) {
    //2 because scale goes from -1 to 1
    //positive scale indicates back side
    //negative scale indicates front side
    speed = 2.0f / frames;
    scale = 1.0f;
}

sf::Vector2f Flip::next() {
    scale -= speed;
    frame_counter++;
    if (frame_counter >= frames) {
        scale = -1.0;
        done = true;
    }
    return sf::Vector2f(scale, 1.0f);
}
