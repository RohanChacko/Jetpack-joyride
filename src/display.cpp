#include "display.h"
#include "main.h"
#include <iostream>


Display::Display(float x, float y) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    angle = (M_PI / 180.0f)*90.0f;
    disp.resize(7);

    for(int i = 0;i<7; ++i)
    {
      disp[i].resize(18);
    }

    GLfloat temp[18] = {
    // 1
        -0.10f,-0.05f, 0.0f, // 1st row fire
        -0.10f, 0.05f, 0.0f, // triangle 1 : begin
        0.05f , 0.05f, 0.0f, // triangle 1 : end

        -0.10f, -0.05f, 0.0f, // triangle 2 : begin
        0.05f , -0.05f, 0.0f,
        0.05f , 0.05f, 0.0f // triangle 2 : end
    };

    for(int i = 0;i<18;++i)
    {
      disp[0][i] = temp[i];
    }

    // 2
    for(int i = 0;i<18;i+=3)
    {
      disp[1][i] = disp[0][i]* cosf(angle) + disp[0][i+1]*sinf(angle) - 0.16f;
      disp[1][i+1] = -1*disp[0][i]*sinf(angle) + disp[0][i+1]*cosf(angle) - 0.16f;
      disp[1][i+2] = 0.0f;
    }

    // 3
    for(int i = 0;i<18;i+=3)
    {
      disp[2][i] = disp[1][i];
      disp[2][i+1] = disp[1][i + 1] - 0.28f;
      disp[2][i+2] = 0.0f;
    }

    // 4
    for(int i = 0;i<18;i+=3)
    {
      disp[3][i] = disp[0][i];
      disp[3][i+1] = disp[0][i + 1] - 0.55f;
      disp[3][i+2] = 0.0f;
    }

    // 5
    for(int i = 0;i<18;i+=3)
    {
      disp[4][i] = disp[2][i] +  0.28f;
      disp[4][i+1] = disp[2][i + 1];
      disp[4][i+2] = 0.0f;
    }

    // 6
    for(int i = 0;i<18;i+=3)
    {
      disp[5][i] = disp[1][i] + 0.28f;
      disp[5][i+1] = disp[1][i + 1];
      disp[5][i+2] = 0.0f;
    }

    // 7
    for(int i = 0;i<18;i+=3)
    {
      disp[6][i] = disp[0][i];
      disp[6][i+1] = disp[0][i + 1] - 0.27f;
      disp[6][i+2] = 0.0f;
    }

    static GLfloat vertex_buffer_data[1000];
    int n = 0;

    // S
    int s_index[7] = {0,1,3,4,6};

    for(int i = 0; i < 5; ++i)
    {
      for(int j = 0; j<disp[s_index[i]].size(); ++j)
        vertex_buffer_data[n++] = disp[s_index[i]][j];
    }

    // C
    int c_index[4] = {0,1,2,3};

    for(int i = 0; i < 4; ++i)
    {
      for(int j = 0; j<disp[c_index[i]].size(); ++j)
        {
          vertex_buffer_data[n++] = disp[c_index[i]][j];
          if((n-1)%3 == 0)
            vertex_buffer_data[n-1]+=0.44;
        }
    }

    // O
    int o_index[6] = {0,1,2,3,4,5};

    for(int i = 0; i < 6; ++i)
    {
      for(int j = 0; j<disp[o_index[i]].size(); ++j)
        {
          vertex_buffer_data[n++] = disp[o_index[i]][j];
          if((n-1)%3 == 0)
            vertex_buffer_data[n-1]+=0.88;
        }
    }

    // R
    int r_index[6] = {0,1,2,4,5,6};

    for(int i = 0; i < 6; ++i)
    {
      for(int j = 0; j<disp[r_index[i]].size(); ++j)
        {
          vertex_buffer_data[n++] = disp[r_index[i]][j];
          if((n-1)%3 == 0)
            vertex_buffer_data[n-1]+=1.42;
        }
    }

    // E
    int e_index[5] = {0,1,2,3,6};

    for(int i = 0; i < 5; ++i)
    {
      for(int j = 0; j<disp[e_index[i]].size(); ++j)
        {
          vertex_buffer_data[n++] = disp[e_index[i]][j];
          if((n-1)%3 == 0)
            vertex_buffer_data[n-1]+=1.96;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, 2*3* (5+4+6+6+5), vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Display::draw(glm::mat4 VP, int score) {

    static GLfloat vertex_buffer_data[1000];
    int n = 0;
    int size = 0;
    int iter = 0;

    if(score == 0)
    {
      int tmp[6] = {0,1,2,3,4,5};
      size+=6;
      for(int i = 0; i < 6; ++i)
      {
        for(int j = 0; j<disp[tmp[i]].size(); ++j)
          {
            vertex_buffer_data[n++] = disp[tmp[i]][j];
            if((n-1)%3 == 0)
              vertex_buffer_data[n-1]+=3.8;
          }
      }
    }
    if(score < 0)
    {
      for(int i = 0;i<18;i+=3)
      {
        vertex_buffer_data[n++] = disp[0][i] + 3.8 - 3*0.44;
        vertex_buffer_data[n++] = disp[0][i + 1] - 0.27f;
        vertex_buffer_data[n++] = 0.0f;
      }
      size++;
    }
    while(abs(score)>0)
    {
      int rem = abs(score)%10;
      switch (rem) {
        case 0: {
                    int zero_index[6] = {0,1,2,3,4,5};
                    size+=6;
                    for(int i = 0; i < 6; ++i)
                    {
                      for(int j = 0; j<disp[zero_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[zero_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }
                    break;
        };
        case 1: {
                    int one_index[2] = {1,2};
                    size+=2;
                    for(int i = 0; i < 2; ++i)
                    {
                      for(int j = 0; j<disp[one_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[one_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 2: {
                    int two_index[5] = {0,2,3,5,6};
                    size+=5;
                    for(int i = 0; i < 5; ++i)
                    {
                      for(int j = 0; j<disp[two_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[two_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 3: {
                    int three_index[5] = {0,3,4,5,6};
                    size+=5;
                    for(int i = 0; i < 5; ++i)
                    {
                      for(int j = 0; j<disp[three_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[three_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 4: {
                    int four_index[4] = {1,4,5,6};
                    size+=4;
                    for(int i = 0; i < 4; ++i)
                    {
                      for(int j = 0; j<disp[four_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[four_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 5: {
                    int five_index[5] = {0,1,3,4,6};
                    size+=5;
                    for(int i = 0; i < 5; ++i)
                    {
                      for(int j = 0; j<disp[five_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[five_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 6: {
                    int six_index[6] = {0,1,2,3,4,6};
                    size+=6;
                    for(int i = 0; i < 6; ++i)
                    {
                      for(int j = 0; j<disp[six_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[six_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 7: {
                    int seven_index[5] = {0,4,5};
                    size+=3;
                    for(int i = 0; i < 3; ++i)
                    {
                      for(int j = 0; j<disp[seven_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[seven_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 8: {
                    int eight_index[7] = {0,1,2,3,4,5,6};
                    size+=7;
                    for(int i = 0; i < 7; ++i)
                    {
                      for(int j = 0; j<disp[eight_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[eight_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
        case 9: {
                    int nine_index[6] = {0,1,3,4,5,6};
                    size+=6;
                    for(int i = 0; i < 6; ++i)
                    {
                      for(int j = 0; j<disp[nine_index[i]].size(); ++j)
                        {
                          vertex_buffer_data[n++] = disp[nine_index[i]][j];
                          if((n-1)%3 == 0)
                            vertex_buffer_data[n-1]+=3.8 - iter*0.44;
                        }
                    }

                    break;
        };
      }

      iter++;
      score/=10;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 2*3* (size), vertex_buffer_data, COLOR_BLACK, GL_FILL);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube around which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Display::tick() {

}

void Display::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
