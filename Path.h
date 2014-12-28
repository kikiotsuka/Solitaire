#ifndef PATH_H
#define PATH_H

#include "Animation.h"

class Path : public Animation {
private:
    sf::Vector2f start_pos, end_pos;
    sf::Vector2f current_pos;
    sf::Vector2f v;
public:
    Path(sf::Vector2f start_pos, sf::Vector2f end_pos, int frames);
    sf::Vector2f next();
};

#endif // PATH_H
