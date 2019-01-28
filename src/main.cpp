#include "main.h"
#include "timer.h"
#include "ball.h"
#include "floor.h"
#include "objects.h"
#include "magnet.h"
#include "firebeam.h"
#include "fireline.h"
#include "ring.h"
#include "wballoon.h"
#include "display.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

/* Object declaration */
Ball ball1;
Floors floors;
Objects object;
Magnet magnet;
Firebeam firebeam;
Firebeam firebeam1;
Fireline fireline;
Boomerang boomerang;
Ring ring;
Balloon balloon;
Display display;
/*********************/

float screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);
int quit_bit = 0;
int disable_input = 0;
/* Render the scene with openGL */

void draw() {
        // clear the color and depth in the frame buffer
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // use the loaded shader program

        glUseProgram (programID);

        // Eye - Location of camera.
        glm::vec3 eye (0,0,100 );
        // Target - Where is the camera looking at.
        glm::vec3 target (0, 0, 0);
        // Up - Up vector defines tilt of camera.
        glm::vec3 up (0, 1, 0);

        // Compute Camera matrix (view)
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

        // Matrices.view = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

        // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)

        glm::mat4 VP = Matrices.projection * Matrices.view;

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // For each model you render, since the MVP will be different (at least the M part)
        // Don't change unless you are sure!!
        glm::mat4 MVP; // MVP = Projection * View * Model

        // Scene render
        ball1.draw(VP);
        if(balloon.active_balloon)
          balloon.draw(VP);
        floors.draw(VP);
        object.draw(VP);
        // Magnet
        if(magnet.active_magnet == 1)
                magnet.draw(VP);

        // Firebeam
        if(firebeam.active_firebeam == 1)
                {
                  firebeam.draw(VP);
                  firebeam1.draw(VP);
                }
        // Fireline
        if(fireline.active_fireline == 1)
                fireline.draw(VP);

        // Boomerang
        if(boomerang.active_boomerang == 1)
                boomerang.draw(VP);

        // Ring
        if(ring.active_ring == 1)
                ring.draw(VP);
        display.draw(VP, ball1.score);

}

int tick_input(GLFWwindow *window) {

        int left  = glfwGetKey(window, GLFW_KEY_LEFT) | glfwGetKey(window, GLFW_KEY_A);
        int right = glfwGetKey(window, GLFW_KEY_RIGHT) | glfwGetKey(window, GLFW_KEY_D);
        int space_bar = glfwGetKey(window, GLFW_KEY_SPACE) | glfwGetKey(window, GLFW_KEY_W);
        int wballoon = glfwGetKey(window, GLFW_KEY_S);

        // int scroll = glfwGetKey(window, GLFW_MOUSE_BUTTON_UP);
        if(!disable_input)
        {
          if (left) {
                  // cout<<"Left"<<endl;
                  return -1;
          }
          else if(right) {
                  // cout<<"right"<<endl;
                  return 1;
          }
          else if(space_bar) {
                  // cout<<"space"<<endl;
                  return 0;
          }
          else if(wballoon) {
                  // cout<<"balloon"<<endl;
                  balloon.stock--;
                  cout<<"Balloon stock: "<<balloon.stock<<endl;
                  return 2;
          }
          else
              return INT_MIN;
        }
        else
            return INT_MIN;
}

void tick_elements(int move) {

        object.generate_object(magnet, firebeam, fireline, boomerang, ring);

        if(firebeam.active_firebeam)
          firebeam1.active_firebeam = 1;
        object.tick();
        magnet.tick();
        firebeam.tick(1);
        firebeam1.tick(0);
        // cout<<firebeam.turn_bit<<" "<<firebeam1.turn_bit<<endl;
        fireline.tick();
        boomerang.tick();
        ring.tick();
        if(!disable_input)
        {
          ball1.tick(move);
          balloon.tick(move, ball1.position);
        }
        ball1.score+=object.collision_checker(ball1.box, balloon);
        display.tick();
        object.destroy_object();
        // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
        /* Objects should be created before any other gl function and shaders */
        // Create the models

        object = Objects();
        ball1 = Ball(0.0, -1, COLOR_RED);
        balloon = Balloon(ball1.position.x, ball1.position.y, COLOR_BLUE);
        floors = Floors(0, -3, COLOR_GREEN);
        magnet = Magnet(0, 4, COLOR_GREY);
        firebeam = Firebeam(-3.5, 4, COLOR_ORANGE);
        firebeam1 = Firebeam(-3.5, -3, COLOR_ORANGE);
        fireline = Fireline(3.5, 0.0, -5.0);                     //Randomise this
        boomerang = Boomerang(3.5, 2);
        ring = Ring(3.5, 2, COLOR_GOLD);
        display = Display(-3.5, 3.8);
        // Create and compile our GLSL program from the shaders
        programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
        // Get a handle for our "MVP" uniform
        Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


        reshapeWindow (window, width, height);

        // Background color of the scene
        glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
        glClearDepth (1.0f);

        glEnable (GL_DEPTH_TEST);
        glDepthFunc (GL_LEQUAL);

        cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
        cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
        cout << "VERSION: " << glGetString(GL_VERSION) << endl;
        cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
        srand(time(0));
        int window_width  = 1000;
        int window_height = 1000;

        window = initGLFW(window_width, window_height);

        initGL (window, window_width, window_height);

        /* Draw in loop */
        while (!glfwWindowShouldClose(window)) {
                // Process timers

                if (t60.processTick()) {
                        // 60 fps
                        // OpenGL Draw commands
                        draw();
                        // Swap Frame Buffer in double buffering
                        glfwSwapBuffers(window);

                        int move = tick_input(window);
                        tick_elements(move);

                        if(quit_bit == 1)
                          break;

                }

                // Poll for Keyboard and mouse events
                glfwPollEvents();
        }

        quit(window);
}

bool linesTouching(bounding_box_t a, bounding_box_t b)
{
  float denominator = ((a.x2 - a.x1) * (b.y2 - b.y1)) - ((a.y2 - a.y1) * (b.x2 - b.x1));
  float numerator1 = ((a.y1 - b.y1) * (a.x2 - b.x1)) - ((a.x1 - b.x1) * (b.y2 - b.y1));
  float numerator2 = ((a.y1 - b.y1) * (a.x2 - a.x1)) - ((a.x1 - b.x1) * (a.y2 - a.y1));

  // Detect coincident lines (has a problem, read below)
  if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

  float r = numerator1 / denominator;
  float s = numerator2 / denominator;

  return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {

        return (abs(abs(a.x) - abs(b.x)) * 2 < (a.width + b.width)) &&
               (abs(abs(a.y) - abs(b.y)) * 2 < (a.height + b.height));
}

void magnet_vel(int speed_y, int orientation)
{
        // cout<<"Here:\n";
        if(orientation == 1)
        {  ball1.position.y += 0.008;
           ball1.box.y = ball1.position.y; }
        if(ball1.position.y >=magnet.position.y+ magnet.box.height)
        { ball1.position.y -= 0.008;
          ball1.box.y = ball1.position.y; }

        if(ball1.position.x > magnet.position.x)
        {
          ball1.position.x-=0.008;
        }
        else if(ball1.position.x < magnet.position.x)
        {
          ball1.position.x+=0.008;
        }
        if(magnet.active_time >= 500)
        {
                magnet.active_magnet = 0;
                magnet.active_time = 0;
                ball1.position.y = -1;
        }
}

void firebeam_vel(int speed_y, int orientation)
{
        // cout<<detect_collision(ball1.box, firebeam.box)<<" "<<detect_collision(ball1.box, firebeam1.box)<<endl;
        if(detect_collision(ball1.box, firebeam.box)||detect_collision(ball1.box, firebeam1.box))
        {ball1.score-=3;}

        if(firebeam.active_time >= 500)
        {
                firebeam.active_firebeam = 0;
                firebeam.active_time = 0;

                firebeam1.active_firebeam = 0;
                firebeam1.active_time = 0;

                ball1.position.y = -1;
        }
}

void fireline_vel(int speed_x, int orientation)
{
        // if(ball1.position.y >=fireline.position.y+ fireline.box.height)
        // { cout<<"Dead from fireline\n";}

        if(fireline.active_time >= 500)
        {
                fireline.active_fireline = 0;
                fireline.active_time = 0;
                ball1.position.y = -1;
        }


        if((linesTouching(ball1.box, fireline.box) || linesTouching(ball1.box1, fireline.box)))
        {
          if(ball1.box.x + ball1.box.width >= fireline.box.x && ball1.box.x + ball1.box.width <= fireline.box.x + 2)
            if(ball1.box.y - ball1.box.height <= fireline.box.y && ball1.box.y + ball1.box.height > fireline.box.y )
              {
                // cout<<"ANSWER: "<<fireline.position.x<<" "<<fireline.position.y<<" "<<fireline.box.x2<<" "<<fireline.box.y2<<" "<<linesTouching(ball1.box1, fireline.box)<<" "<<linesTouching(ball1.box1, fireline.box)<<"\n";
                ball1.score-=2;
              }
        }

}

void ring_attract()
{
  if(ball1.position.y >= 1.9f && ball1.position.y <=3.5f)
  {
    if(ball1.position.x  <= ring.position.x && ball1.position.x + ball1.box.width - 1.0>= ring.position.x )
      {
        // cout<<"sfgd\n";
        ball1.position.y +=0.001;
        ball1.position.x +=0.15;
        disable_input = 1;
      }

    if(ball1.position.x  > ring.position.x && ball1.position.x - ball1.box.width <= ring.position.x + ring.box.width)
      {
        // cout<<"efew\n";
        ball1.position.y -=0.001;
        ball1.position.x +=0.15;
        disable_input = 0;

        if(!disable_input)
          ball1.score-=5;
      }

  }

  if(ball1.position.y >= 3.5)
    ball1.position.y = 3.5;

  if(ball1.position.y <= -1.0)
    {
      ball1.position.y = -1.0;
    }

}


void balloon_kill()
{
  // cout<<detect_collision(balloon.box, firebeam.box)<<" "<<detect_collision(firebeam1.box, balloon.box)<<endl;

  if(firebeam.active_firebeam&&balloon.active_balloon&&balloon.stock)
  if(detect_collision(balloon.box, firebeam.box) || detect_collision(firebeam1.box, balloon.box))
    {
      firebeam.active_firebeam = 0;
      firebeam.active_time = 0;

      firebeam1.active_firebeam = 0;
      firebeam1.active_time = 0;

      ball1.position.y = -1;
    }

  if(fireline.active_fireline&&balloon.active_balloon&&balloon.stock)
  {
    // cout<<linesTouching(balloon.box, fireline.box)<<endl;
    if(linesTouching(balloon.box, fireline.box))
    {
      // cout<<"ASAaaaaaaaaaaaaaaaaaaaaaa"<<endl;
      fireline.active_fireline = 0;
      fireline.active_time = 0;
      ball1.position.y = -1;
    }
  }
// cout<<balloon.position.x<<" "<<balloon.position.y<<"\n";
}

void boomerang_kill()
{
  if(boomerang.active_boomerang)
  {
      if((abs(ball1.box.x - boomerang.box.x) * 2 < (ball1.box.width + boomerang.box.width)) &&
             (abs(ball1.box.y - boomerang.box.y) * 2 < (ball1.box.height + boomerang.box.height)))
        {
          ball1.score-=4;
        }

  }

}
void reset_screen() {
        float top    = screen_center_y + 4 / screen_zoom;
        float bottom = screen_center_y - 4 / screen_zoom;
        float left   = screen_center_x - 4 / screen_zoom;
        float right  = screen_center_x + 4 / screen_zoom;
        Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
