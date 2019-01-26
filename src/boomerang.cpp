#include "boomerang.h"
#include "main.h"
#include <iostream>

Boomerang::Boomerang(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_x = 0.1;
    speed_y = 0.0010; //Not required
    turn_bit = 0;
    active_boomerang = 0;
    active_time = 0;

    this->box.height = 0.30;
    this->box.width = 0.25;
    this->box.y = y;
    this->box.x = x;

    static GLfloat vertex_buffer_data[] = {
        -0.30f,-0.25f, 0.0f, // triangle 1 : begin
        -0.30f, 0.25f, 0.0f,
         0.30f, 0.25f, 0.0f, // triangle 1 : end

        -0.30f, -0.25f, 0.0f, // triangle 2 : begin
        -0.30f, 0.25f, 0.0f,
         0.30f, -0.25f, 0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * (M_PI / 180.0f)), glm::vec3(0, 0, 1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::tick() {

  if(active_boomerang == 1)
  {
    this->position.x -= speed_x;

    this->position.y = 2.0f * sqrtf(0.18*abs(this->position.x + 4));

    if(this->position.x <= -4.0 && turn_bit == 0)
      {
        speed_x*=-1;
        turn_bit = 1;
        this->rotation = 180;
      }

    if(turn_bit == 1)
    {
      this->position.y *=-1;
    }

    boomerang_kill();
    // std::cout<<"pos: "<<this->position.x<<" "<<this->position.y<<"\n";
    this->box.x = this->position.x;
    this->box.y = this->position.y;
  }
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
