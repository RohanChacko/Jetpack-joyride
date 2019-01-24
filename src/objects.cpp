#include "objects.h"
#include "main.h"
#include <iostream>
#include <stdlib.h>

Objects::Objects() {

}

void Objects::draw(glm::mat4 VP, Magnet& magnet, Firebeam& firebeam, Fireline& fireline, Boomerang& boomerang) {

  // Coin
  for(i = this->coins.begin(); i !=this->coins.end(); ++i )
  {
    (*i).draw(VP);
  }

  // Magnet
  if(magnet.active_magnet == 1)
    magnet.draw(VP);

  // Firebeam
  if(firebeam.active_firebeam == 1)
    firebeam.draw(VP);

  // Fireline
  if(fireline.active_fireline == 1)
    fireline.draw(VP);

  // Boomerang
  if(boomerang.active_boomerang == 1)
    boomerang.draw(VP);
}

void Objects::generate_object(Magnet &magnet, Firebeam& firebeam, Fireline& fireline, Boomerang& boomerang) {

    int random = rand();

    // Coins
    if(random % 500 == 0)
    {
      this->coins.push_back(Coin(4.0, rand()%2 + 1.0,COLOR_GOLD));
    }

    // // Magnet
    // if(random % 600 == 0)
    // {
    //   magnet.active_magnet = 1;
    // }
    //
    // // Firebeam
    // else if(random % 1000 == 0)
    // {
    //   firebeam.active_firebeam = 1;
    // }
    //
    // // Fireline
    // else if(random % 100 == 0)
    // {
    //   fireline.active_fireline = 1;
    // }
    //
    // // else if(random % 50 == 0)
    // {
    //   boomerang.active_boomerang = 1;
    // }
}

void Objects::tick() {

  // Coins
  for(i = this->coins.begin(); i !=this->coins.end(); ++i )
  {
    (*i).tick();
  }
}

void Objects::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Objects::destroy_object() {

  // Coins
  for(i = this->coins.begin(); i !=this->coins.end(); ++i )
  {
    if( (*i).position.x < -3.6 ) {

      coins.erase(i);
      --i;
    }
  }
}

void Objects::collision_checker(struct bounding_box_t player_box) {

  // Coins
  for(i = this->coins.begin(); i !=this->coins.end(); ++i )
  {
    // bool ans = detect_collision((*i).box, player_box);
    if(detect_collision((*i).box, player_box)) {
      coins.erase(i);
      --i;
    }
  }
}
