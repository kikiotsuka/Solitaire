#ifndef FLIP_H
#define FLIP_H

class Flip {
private:
    float scale;
    float speed;
    int frames;
    bool done;
    bool half_done;
public:
    Flip(int frames);
    float next();
    float finish();
    bool get_done();
    bool get_half_done();
};

#endif // FLIP_H
