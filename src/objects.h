#include "main.h"
#include "coin.h"
#include <vector>

#ifndef OBJECTS_H
#define OBJECTS_H


class Objects {
public:
    Objects();

    std::vector<Coin> coins;
    std::vector<Coin>::iterator i;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void generate_object();
    void destroy_object();
    void tick();

private:
    VAO *object;
};

#endif // OBJECTS_H
