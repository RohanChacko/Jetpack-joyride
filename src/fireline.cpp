#include "fireline.h"
#include "main.h"
#include <iostream>

Fireline::Fireline(float x, float y,float angle) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_y = 0.15;
    active_fireline = 0;
    active_time = 0;
    angle *= (3.14159265/180);     //Converting from angle to radians
    this->box.height = 0.15;
    this->box.width = 0.15;
    this->box.y = y;
    this->box.x = x;

    static GLfloat vertex_buffer_data[] = {
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

        -0.25f + 2.0f,-0.25f ,-0.25f , // 1st row 2nd box
        -0.25f + 2.0f,-0.25f , 0.25f , // triangle 1 : begin
        -0.25f + 2.0f, 0.25f , 0.25f , // triangle 1 : end
        0.25f + 2.0f, 0.25f ,-0.25f , // triangle 2 : begin
        -0.25f + 2.0f,-0.25f ,-0.25f ,
        -0.25f + 2.0f, 0.25f ,-0.25f , // triangle 2 : end
        0.25f + 2.0f,-0.25f , 0.25f ,
        -0.25f + 2.0f,-0.25f ,-0.25f ,
        0.25f + 2.0f,-0.25f ,-0.25f ,
        0.25f + 2.0f, 0.25f ,-0.25f ,
        0.25f + 2.0f,-0.25f ,-0.25f ,
        -0.25f + 2.0f,-0.25f ,-0.25f,

        0.25f,-0.15f,-0.15f, // 1st row fire
        0.25f,-0.15f, 0.15f, // triangle 1 : begin
        0.25f, 0.15f, 0.15f, // triangle 1 : end
        0.30f + 1.45f, 0.15f,-0.15f, // triangle 2 : begin
        0.25f,-0.15f,-0.15f,
        0.25f, 0.15f,-0.15f, // triangle 2 : end
        0.30f ,-0.15f, 0.15f,
        0.25f,-0.15f,-0.15f,
        0.30f,-0.15f,-0.15f,
        0.30f + 1.45f, 0.15f,-0.15f,
        0.30f + 1.45f,-0.15f,-0.15f,
        0.25f,-0.15f,-0.15f
    };

    for(int i = 0;i<4*3*3*3;i+=3)
    {
      GLfloat temp = vertex_buffer_data[i];
      vertex_buffer_data[i] = vertex_buffer_data[i]* cosf(angle) + vertex_buffer_data[i+1]*sinf(angle);
      vertex_buffer_data[i+1] = -1*temp*sinf(angle) + vertex_buffer_data[i+1]*cosf(angle);
    }

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

    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,
    COLOR_RED.r/256.0f, COLOR_RED.g/256.0f, COLOR_RED.b/256.0f,

};

    this->object = create3DObject(GL_TRIANGLES, 4*3*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
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

void Fireline::tick() {

  if(active_fireline == 1)
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
      fireline_vel(speed_y, 1);
    }

    this->box.x = this->position.x;
    this->box.y = this->position.y;
  }
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
