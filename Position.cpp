#include "Position.h"

Position::Position() {
    init();
}

Position::Position(sf::Vector3i origin_loc) {
    init();
    loc.first = origin_loc;
}

Position::Position(sf::Vector2f destination_coord, sf::Vector3i origin_loc, sf::Vector3i destination_loc) {
    init();
    coord.second = destination_coord;
    loc.first = origin_loc;
    loc.second = destination_loc;
}

void Position::init() {
    coord.first = coord.second = sf::Vector2f(-1, -1);
    loc.first = loc.second = sf::Vector3i(-1, -1, -1);
}
