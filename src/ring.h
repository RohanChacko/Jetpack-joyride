#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double speed_x;
    int num_triangles;
    int num_circles;
    int active_ring;
    struct bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

private:
    VAO *object;
};

#endif // RING_H
