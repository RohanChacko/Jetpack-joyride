#include "ball.h"
#include "main.h"
#include <iostream>

Ball::Ball(float x, float y, color_t color) {
        this->position = glm::vec3(x, y, 0);
        this->rotation = 0;
        speed_x = 0.1;
        speed_y = 0.42;
        score = 0;

        this->box.height = 0.5;
        this->box.width = 0.5;

        set_jump_height = INT_MIN;
        // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
        // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
        static const GLfloat vertex_buffer_data[] = {
                -0.5f,-0.5f,-0.0f, // triangle 1 : begin
                -0.5f,-0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f, // triangle 1 : end

                0.5f, 0.5f,-0.0f, // triangle 2 : begin
                -0.5f,-0.5f,-0.0f,
                -0.5f, 0.5f,-0.0f, // triangle 2 : end

                0.5f,-0.5f, 0.0f,
                -0.5f,-0.5f,-0.0f,
                0.5f,-0.5f,-0.0f,

                0.5f, 0.5f,-0.0f,
                0.5f,-0.5f,-0.0f,
                -0.5f,-0.5f,-0.0f,
        };

        this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position); // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
        this->position = glm::vec3(x, y, 0);
}

void Ball::tick(int move) {


        if(move == 1) {
                // this->rotation += speed_x;
                this->position.x += speed_x;

                if(this->position.x > 3.5)
                        this->position.x = 3.5;
                // std::cout<<"x: "<<this->position.x<<" y:"<<this->position.y<<"\n";
        }
        else if(move == -1) {
                this->position.x -= speed_x;

                if(this->position.x < -3.5)
                        this->position.x = -3.5;
                // std::cout<<this->position.x<<"\n";
        }
        else if(move == 0) {
                set_jump_height = this->position.y + 2;
        }
        // std::cout<<"x: "<<this->position.x<<" y:"<<this->position.y<<" set jmp height: "<<set_jump_height<<" speed_y: "<<speed_y<<"\n";
        //Character jumping logic
        if(set_jump_height != INT_MIN)
        {
                if (this->position.y < set_jump_height)
                {
                        if(this->position.y >= 3.5) //|| set_jump_height >= 3.5)
                        {
                                this->position.y = 3.5;
                                set_jump_height = 3.5;
                                timer = 0;
                        }
                        else{
                                timer++;
                                // speed_y-=timer*0.009;
                                this->position.y+=timer*0.03;
                        }
                }
                else if(this->position.y >= set_jump_height)
                {
                        set_jump_height = -1;
                        timer++;
                        // speed_y+=timer*0.009;
                        this->position.y -=timer*0.02;
                        if(this->position.y <= -1.0)
                        {
                                set_jump_height = INT_MIN;
                                speed_y = 0.5;
                                this->position.y = -1;
                                timer = 0;
                        }

                        if(this->position.y>= set_jump_height )
                        {
                                speed_x = 0.1;
                                speed_y = 0.42;
                        }

                }
        }

        // std::cout<<"x: "<<this->position.x<<" y:"<<this->position.y<<" set jmp height: "<<set_jump_height<<" speed_y: "<<speed_y<<"\n";

        this->box.x = this->position.x;
        this->box.y = this->position.y;

        this->box.x1 = this->position.x + this->box.width;
        this->box.y1 = this->position.y + this->box.height;
        this->box.x2 = this->position.x + this->box.width;
        this->box.y2 = this->position.y - this->box.height;

        this->box1.x1 = this->position.x - this->box.width;
        this->box1.y1 = this->position.y + this->box.height;
        this->box1.x2 = this->position.x - this->box.width;
        this->box1.y2 = this->position.y - this->box.height;

        // std::cout<<this->box1.x1<<" "<<this->box1.y1<<" "<<this->box1.x2<<" "<<this->box1.y2;
}
