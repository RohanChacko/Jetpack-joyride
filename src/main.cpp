#include "main.h"
#include "timer.h"
#include "ball.h"
#include "floor.h"
#include "objects.h"
#include "magnet.h"
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
/*********************/

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

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
        floors.draw(VP);
        object.draw(VP, magnet);

}

int tick_input(GLFWwindow *window) {

        int left  = glfwGetKey(window, GLFW_KEY_LEFT) | glfwGetKey(window, GLFW_KEY_A);
        int right = glfwGetKey(window, GLFW_KEY_RIGHT) | glfwGetKey(window, GLFW_KEY_D);
        int space_bar = glfwGetKey(window, GLFW_KEY_SPACE) | glfwGetKey(window, GLFW_KEY_W);

        if (left) {
                cout<<"Left"<<endl;
                return -1;
        }
        else if(right) {
                cout<<"right"<<endl;
                return 1;
        }
        else if(space_bar) {
                cout<<"space"<<endl;
                return 0;
        }
        else
                return INT_MIN;
}

void tick_elements(int move) {

        object.generate_object(magnet);
        object.tick(magnet);
        ball1.tick(move);
        object.collision_checker(ball1.box);
        object.destroy_object();
        // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
        /* Objects should be created before any other gl function and shaders */
        // Create the models

        object = Objects();
        ball1 = Ball(0, -1, COLOR_RED);
        floors = Floors(0, -3, COLOR_GREEN);
        magnet = Magnet((float)0, (float)4, COLOR_GREY);
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

                }

                // Poll for Keyboard and mouse events
                glfwPollEvents();
        }

        quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
        return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
               (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void magnet_vel(int speed_y, int orientation)
{
        cout<<"Here:\n";
        if(orientation == 1)
        {  ball1.position.y += 0.008;
           ball1.box.y = ball1.position.y; }
        if(ball1.position.y >=magnet.position.y+ magnet.box.height)
        { ball1.position.y -= 0.008;
          ball1.box.y = ball1.position.y; }
          
        if(magnet.active_time >= 500)
          {
            magnet.active_magnet = 0;
            magnet.active_time = 0;
            ball1.position.y = -1;
          }
}

void reset_screen() {
        float top    = screen_center_y + 4 / screen_zoom;
        float bottom = screen_center_y - 4 / screen_zoom;
        float left   = screen_center_x - 4 / screen_zoom;
        float right  = screen_center_x + 4 / screen_zoom;
        Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
