#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H


class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, color_t color);
    glm::vec3 position;
    double speed_y;
    float rotation;
    int active_firebeam;
    int active_time;
    int turn_bit;
    struct bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int side);

private:
    VAO *object;
};

#endif // FIREBEAM_H
