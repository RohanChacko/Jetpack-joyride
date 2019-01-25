#include "ring.h"
#include "main.h"
#include <iostream>

Ring::Ring(float x, float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    active_ring = 0;
    speed_x = 0.04;

    //num_triangles: Specify the roundness of the ring shape
    num_triangles = 50;
    num_circles = 13;
    this->box.height = 1.5;
    this->box.width = 1.625;

    static GLfloat vertex_buffer_data[7000];

    for(int j = 0;j<num_circles;++j)
    {
      // std::cout<<0.0f + (float)j*0.25f<<" "<<0.0f + fabs(4.0f - ((float)j*0.25f - 2.0f)*((float)j*0.25f - 2.0f))<<"\n";

      for(int i = 0;i<num_triangles;++i)
      {
        vertex_buffer_data[9*i+j*9*num_triangles] = 0.0f + (float)j*0.25f;
        vertex_buffer_data[9*i+1+j*9*num_triangles] = 0.0f + sqrtf(fabs(2.25f - ((float)j*0.25f - 1.5f)*((float)j*0.25f - 1.5f))) ;
        vertex_buffer_data[9*i+2+j*9*num_triangles] = 0.0f ;
        vertex_buffer_data[9*i+3+j*9*num_triangles] = 0.15f*cosf(2*3.14159265*i/num_triangles) + (float)j*0.25f;
        vertex_buffer_data[9*i+4+j*9*num_triangles] = 0.15f*sinf(2*3.14159265*i/num_triangles) + sqrtf(fabs(2.25f - ((float)j*0.25f - 1.5f)*((float)j*0.25 - 1.5f)));
        vertex_buffer_data[9*i+5+j*9*num_triangles] = 0.0f;
        vertex_buffer_data[9*i+6+j*9*num_triangles] = 0.15f*cosf((2*3.14159265*(i+1))/num_triangles) + (float)j*0.25f;
        vertex_buffer_data[9*i+7+j*9*num_triangles] = 0.15f*sinf((2*3.14159265*(i+1))/num_triangles) + sqrtf(fabs(2.25f - ((float)j*0.25 - 1.5f)*((float)j*0.25 - 1.5f)));
        vertex_buffer_data[9*i+8+j*9*num_triangles] = 0.0f;
      };
    }

    this->object = create3DObject(GL_TRIANGLES, 3*num_triangles*num_circles, vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
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

void Ring::tick() {

  if(active_ring == 1)
  {
    this->position.x -= speed_x;
    this->box.x = this->position.x;
    this->box.y = this->position.y;
    ring_attract();
  }
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
