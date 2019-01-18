#include "main.h"
#include "coin.h"
#include "magnet.h"
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
    void draw(glm::mat4 VP, Magnet& magnet);
    void set_position(float x, float y);
    void generate_object(Magnet& magnet);
    void destroy_object();
    void collision_checker(struct bounding_box_t player_box);
    void tick(Magnet& magnet);

private:
    VAO *object;
};

#endif // OBJECTS_H
