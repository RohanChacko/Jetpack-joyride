#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H


class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, float angle);
    glm::vec3 position;
    double speed_x;
    float rotation;
    int active_fireline;
    int active_time;

    struct bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

private:
    VAO *object;
};

#endif // FIRELINE_H
