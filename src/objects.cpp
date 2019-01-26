#include "objects.h"
#include "main.h"
#include <iostream>
#include <stdlib.h>
#include <string>
Objects::Objects() {
  counter = 0;
}

void Objects::draw(glm::mat4 VP) {

        // Coin
        for(i = this->coins.begin(); i !=this->coins.end(); ++i )
        {
                (*i).draw(VP);
        }
}

void Objects::generate_object(Magnet &magnet, Firebeam& firebeam, Fireline& fireline, Boomerang& boomerang, Ring& ring) {

        int random = rand();
        std::vector<color_t> color(3);
        color[0] = COLOR_GOLD;
        color[1] = COLOR_PURPLE;
        color[2] = COLOR_PINK;

        int vals[] ={5, 10, 15};

        // Coins
        if(random % 50 == 0)
        {
                this->coins.push_back(Coin(4.0, rand()%2 + 1.0,color[rand()%3], vals[rand()%3]));
        }

        if(magnet.active_magnet)
          counter++;
        else
          counter--;
        if(firebeam.active_firebeam)
          counter++;
        else
          counter--;
        if(fireline.active_fireline)
          counter++;
        else
          counter--;
        if(boomerang.active_boomerang)
          counter++;
        else
          counter--;
        if(ring.active_ring)
          counter++;
        else
          counter--;

        if(counter <= 2)
        {
        // Magnet
        if(random % 1097 == 0)
        {
          magnet.active_magnet = 1;
        }

        // Firebeam
        else if(random % 1097 == 1)
        {
          firebeam.active_firebeam = 1;
        }

        // Fireline
        else if(random % 1097 == 2)
        {
          fireline.active_fireline = 1;
        }

        else if(random % 1097 == 3)
        {
          boomerang.active_boomerang = 1;
        }

        else if(random % 1097 == 4)
        {
                ring.active_ring = 1;
        }

      }
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

int Objects::collision_checker(struct bounding_box_t& b) {
        int count = 0;
        // Coins
        for(i = this->coins.begin(); i !=this->coins.end(); ++i )
        {
                // bool ans = detect_collision((*i).box, player_box);
                if((abs((*i).box.x - b.x) * 2 < ((*i).box.width + b.width)) &&
                       (abs((*i).box.y - b.y) * 2 < ((*i).box.height + b.height))) {
                      // std::cout<<(*i).box.x<<" "<<(*i).box.y<<" "<<player_box.x<<" "<<player_box.y<<"\n";
                        count+=(*i).val;
                        coins.erase(i);
                        --i;
                }
        }

        return count;
}
