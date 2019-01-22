#include "firebeam.h"
#include "main.h"
#include <iostream>

Firebeam::Firebeam(float x, float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_y = 0.15;
    active_firebeam = 0;
    active_time = 0;

    this->box.height = 0.15;
    this->box.width = 0.15;
    this->box.y = y;
    this->box.x = x;

    static const GLfloat vertex_buffer_data[] = {
        -0.25f,-0.25f,-0.25f, // 1st row 1st box
        -0.25f,-0.25f, 0.25f, // triangle 1 : begin
        -0.25f, 0.25f, 0.25f, // triangle 1 : end
        0.25f, 0.25f,-0.25f, // triangle 2 : begin
        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f,-0.25f, // triangle 2 : end
        0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,
        -0.25f,-0.25f,-0.25f,

        -0.25f + 7.0f,-0.25f ,-0.25f , // 1st row 2nd box
        -0.25f + 7.0f,-0.25f , 0.25f , // triangle 1 : begin
        -0.25f + 7.0f, 0.25f , 0.25f , // triangle 1 : end
        0.25f + 7.0f, 0.25f ,-0.25f , // triangle 2 : begin
        -0.25f + 7.0f,-0.25f ,-0.25f ,
        -0.25f + 7.0f, 0.25f ,-0.25f , // triangle 2 : end
        0.25f + 7.0f,-0.25f , 0.25f ,
        -0.25f + 7.0f,-0.25f ,-0.25f ,
        0.25f + 7.0f,-0.25f ,-0.25f ,
        0.25f + 7.0f, 0.25f ,-0.25f ,
        0.25f + 7.0f,-0.25f ,-0.25f ,
        -0.25f + 7.0f,-0.25f ,-0.25f,

        -0.25f,-0.25f - 0.95f,-0.25f, // 2nd row 1st box
        -0.25f,-0.25f - 0.95f, 0.25f, // triangle 1 : begin
        -0.25f, 0.25f - 0.95f, 0.25f, // triangle 1 : end
        0.25f, 0.25f - 0.95f, -0.25f, // triangle 2 : begin
        -0.25f,-0.25f - 0.95f, -0.25f,
        -0.25f, 0.25f - 0.95f, -0.25f, // triangle 2 : end
        0.25f,-0.25f - 0.95f, 0.25f,
        -0.25f,-0.25f - 0.95f, -0.25f,
        0.25f,-0.25f - 0.95f, -0.25f,
        0.25f, 0.25f - 0.95f, -0.25f,
        0.25f,-0.25f - 0.95f, -0.25f,
        -0.25f,-0.25f - 0.95f, -0.25f,

        -0.25f + 7.0f,-0.25f - 0.95f,-0.25f, // 2nd row 2nd box
        -0.25f + 7.0f,-0.25f - 0.95f, 0.25f, // triangle 1 : begin
        -0.25f + 7.0f, 0.25f - 0.95f, 0.25f, // triangle 1 : end
        0.25f + 7.0f, 0.25f - 0.95f, -0.25f, // triangle 2 : begin
        -0.25f + 7.0f,-0.25f - 0.95f, -0.25f,
        -0.25f + 7.0f, 0.25f - 0.95f, -0.25f, // triangle 2 : end
        0.25f + 7.0f,-0.25f - 0.95f, 0.25f,
        -0.25f + 7.0f,-0.25f - 0.95f, -0.25f,
        0.25f + 7.0f,-0.25f - 0.95f, -0.25f,
        0.25f + 7.0f, 0.25f - 0.95f, -0.25f,
        0.25f + 7.0f,-0.25f - 0.95f, -0.25f,
        -0.25f + 7.0f,-0.25f - 0.95f, -0.25f

    };

    static const GLfloat color_buffer_data[] = {
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,
    COLOR_ORANGE.r/256.0f, COLOR_ORANGE.g/256.0f, COLOR_ORANGE.b/256.0f,

};

    this->object = create3DObject(GL_TRIANGLES, 4*3*4, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube around which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam::tick() {

  if(active_firebeam == 1)
  {
    active_time++;
    std::cout<<"active: "<<active_time<<"\n";
    if(this->box.y + this->box.height >= 3.5 )
    {
      this->position.y -= speed_y;
    }
    else
    {
      // Activate functionality: Kills rider on contact
      firebeam_vel(speed_y, 1);
    }

    this->box.x = this->position.x;
    this->box.y = this->position.y;
  }
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
