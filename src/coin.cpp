#include "coin.h"
#include "main.h"
#include <iostream>

Coin::Coin(float x, float y,color_t color, int value) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_x = 0.1;
    this->colo = color;
    this->val = value;
    //num_triangles: Specify the roundness of the coin shape
    num_triangles = 50;

    this->box.height = 0.15;
    this->box.width = 0.15;

    static GLfloat vertex_buffer_data[500];
    static GLfloat vertex_buffer_data1[] = {

      -0.15f,-0.15f, 0.0f, // 1st row fire
      -0.15f, 0.15f, 0.0f, // triangle 1 : begin
      0.15f , 0.15f, 0.0f, // triangle 1 : end

      -0.15f, -0.15f, 0.0f, // triangle 2 : begin
      0.15f , -0.15f, 0.0f,
      0.15f, 0.15f, 0.0f // triangle 2 : end

    };


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

    if(this->val == 1000 || this->val == 5000)
      this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data1, this->colo, GL_FILL);
    else
      this->object = create3DObject(GL_TRIANGLES, 3*num_triangles, vertex_buffer_data, this->colo, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
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

void Coin::tick() {
  this->position.x -= speed_x;
  this->box.x = this->position.x;
  this->box.y = this->position.y;
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
