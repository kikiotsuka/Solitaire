#include "Flip.h"

Flip::Flip(int frames) {
    this->frames = frames;
    //2 because scale goes from -1 to 1
    //positive scale indicates back side
    //negative scale indicates front side
    speed = 2.0f / frames;
    scale = 1.0f;
    done = false;
    half_done = false;
}

float Flip::next() {
    scale -= speed;
    frames--;
    if (frames <= 0) {
        scale = -1.0;
        done = true;
    }
    if (scale <= 0) {
        half_done = true;
    }
    return scale >= 0 ? scale : -scale;
}

float Flip::finish() {
    frames = 0;
    return next();
}

bool Flip::get_done() { return done; }
bool Flip::get_half_done() { return half_done; }