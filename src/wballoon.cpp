#include "wballoon.h"
#include "main.h"
#include <iostream>

Balloon::Balloon(float x, float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_x = 0.1;
    active_balloon = 0;
    timer = 0;

    //num_triangles: Specify the roundness of the coin shape
    num_triangles = 50;

    this->box.height = 0.15;
    this->box.width = 0.15;

    static GLfloat vertex_buffer_data[500];

    for(int i = 0;i<num_triangles;i++)
    {
      vertex_buffer_data[9*i] = 0.0f;
      vertex_buffer_data[9*i+1] = 0.0f;
      vertex_buffer_data[9*i+2] = 0.0f;
      vertex_buffer_data[9*i+3] = 0.15f*cosf(2*3.14159265*i/num_triangles);
      vertex_buffer_data[9*i+4] = 0.15f*sinf(2*3.14159265*i/num_triangles);
      vertex_buffer_data[9*i+5] = 0.0f;
      vertex_buffer_data[9*i+6] = 0.15f*cosf((2*3.14159265*(i+1))/num_triangles);
      vertex_buffer_data[9*i+7] = 0.15f*sinf((2*3.14159265*(i+1))/num_triangles);
      vertex_buffer_data[9*i+8] = 0.0f;
    };

    this->object = create3DObject(GL_TRIANGLES, 3*num_triangles, vertex_buffer_data, color, GL_FILL);
}

void Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Balloon::tick(int move, glm::vec3 position) {

  if(move == 2)
  {
      active_balloon = 1;
      this->position.x = position.x;
      this->position.y = position.y;
  }

  if(active_balloon)
  {
    timer++;
    this->position.x += 0.085;
    this->position.y -= 0.005*timer;
  }

  if(this->position.y <= -3.5)
  {
    active_balloon = 0;
    timer = 0;
  }

  this->box.x = this->position.x;
  this->box.y = this->position.y;

  this->box.x1 = this->position.x;
  this->box.x2 = this->position.x;
  this->box.y1 = this->position.y + this->box.height;
  this->box.y2 = this->position.y - this->box.height;

  //collision detection

  balloon_kill();

  // std::cout<<this->position.x<<" "<<this->position.y<<"\n";
}

void Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
