#include "objects.h"
#include "main.h"
#include <iostream>
#include <stdlib.h>

Objects::Objects() {

}

void Objects::draw(glm::mat4 VP) {

  for(i = this->coins.begin(); i !=this->coins.end(); ++i )
  {
    (*i).draw(VP);
  }
}

void Objects::generate_object() {

    int random = rand();

    if(random % 500 == 0)
    {
      this->coins.push_back(Coin(4, rand()% 2 + 1,COLOR_GOLD));
    }
}

void Objects::tick() {

  for(i = this->coins.begin(); i !=this->coins.end(); ++i )
  {
    (*i).tick();
  }
}

void Objects::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Objects::destroy_object() {

  for(i = this->coins.begin(); i !=this->coins.end(); ++i )
  {
    if( (*i).position.x < -3.6 ) {

      coins.erase(i);
      --i;
    }
  }
}
