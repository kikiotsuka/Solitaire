#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
protected:
    int frames, frame_counter;
    bool done;
public:
    Animation(int frames);
    virtual sf::Vector2f next();
    sf::Vector2f finish();
    bool get_done();
    int get_frames();
};

#endif // ANIMATION_H
