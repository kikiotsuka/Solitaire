#ifndef FLIP_H
#define FLIP_H

#include "Animation.h"

class Flip : public Animation {
private:
    float scale;
    float speed;
public:
    Flip(int frames);
    sf::Vector2f next();
};

#endif // FLIP_H
