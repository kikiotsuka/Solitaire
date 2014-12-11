#ifndef PATH_H
#define PATH_H

class Path {
private:
    sf::Vector2f start_pos, end_pos;
    sf::Vector2f current_pos;
    sf::Vector2f v;
    float frames;
    bool done;
public:
    Path(sf::Vector2f start_pos, sf::Vector2f end_pos, float frames);
    sf::Vector2f next();
    sf::Vector2f finish();
    bool get_done();
};

#endif // PATH_H