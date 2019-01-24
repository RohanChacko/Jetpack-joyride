#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y);
    glm::vec3 position;
    double speed_x;
    double speed_y;
    float rotation;
    int active_boomerang;
    int active_time;
    int turn_bit;
    struct bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

private:
    VAO *object;
};

#endif // BOOMERANG_H
