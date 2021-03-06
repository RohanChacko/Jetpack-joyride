#include "main.h"
#include "coin.h"
#include "magnet.h"
#include "firebeam.h"
#include "fireline.h"
#include "boomerang.h"
#include "ring.h"
#include "wballoon.h"
#include <vector>

#ifndef OBJECTS_H
#define OBJECTS_H


class Objects {
public:
    Objects();
    std::vector<Coin>coins;
    std::vector<Coin>::iterator i;
    glm::vec3 position;
    float rotation;
    int counter;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void generate_object(Magnet& magnet, Firebeam& firebeam, Fireline& fireline, Boomerang& boomerang, Ring& ring);
    void destroy_object();
    int collision_checker(struct bounding_box_t& player_box, Balloon& balloon);
    void tick();

private:
    VAO *object;
};

#endif // OBJECTS_H
