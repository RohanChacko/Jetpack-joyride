#include "main.h"
#include <vector>

#ifndef DISPLAY_H
#define DISPLAY_H


class Display {
public:
    Display():disp(7) {}
    Display(float x, float y);
    glm::vec3 position;
    float rotation;
    float angle;
    int score;
    std::vector<std::vector<GLfloat> > disp;
    // struct bounding_box_t box;
    void draw(glm::mat4 VP, int score);
    void set_position(float x, float y);
    void tick();

private:
    VAO *object;
    VAO *object1;
};

#endif // DISPLAY_H
