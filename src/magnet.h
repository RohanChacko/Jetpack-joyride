#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    double speed_y;
    float rotation;
    int active_magnet;
    int active_time;
    struct bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

private:
    VAO *object;
};

#endif // MAGNET_H
