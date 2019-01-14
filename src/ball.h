#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int move);
    double speed_x;
    double speed_y;
    double set_jump_height;
    int height;
    int width;

private:
    VAO *object;
};

#endif // BALL_H
