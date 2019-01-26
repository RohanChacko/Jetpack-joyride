#include "main.h"

#ifndef WBALLOON_H
#define WBALLOON_H


class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double speed_x;
    int num_triangles;
    int active_balloon;
    int timer;
    struct bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int move, glm::vec3 position);

private:
    VAO *object;
};

#endif // WBALLOON_H
