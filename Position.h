#ifndef POSITION_H
#define POSITION_H

#include <SFML/Graphics.hpp>
#include <utility>

class Position {
public:
    std::pair<sf::Vector2f, sf::Vector2f> coord;
    std::pair<sf::Vector3i, sf::Vector3i> loc;
    Position();
    Position(sf::Vector3i origin_loc);
    Position(sf::Vector2f destination_coord, sf::Vector3i origin_loc, sf::Vector3i destination_loc);
    void init();
};

#endif // POSITION_H
