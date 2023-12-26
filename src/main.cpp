#include "library.hpp"
#include "main.hpp"

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
    if(action == GLFW_PRESS)
        if(key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* initWindow(const int resX, const int resY)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(resX, resY, "Cube", NULL, NULL);

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, controls);

    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));


    glEnable(GL_DEPTH_TEST);    // Enable the depth buffer
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Ask for nicest perspective correction

    glEnable(GL_CULL_FACE);     // Cull back facing polygons
    glCullFace(GL_FRONT);
    return window;
}

void changePerspective( double eyeX,
                         double eyeY,
                         double eyeZ,
                         double centerX,
                         double centerY,
                         double centerZ,
                         double upX,
                         double upY,
                         double upZ 
                        )
{ gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ); }

void setScale(double x, double y, double z){ glScalef(x,y,z); }

void changeCameraCoords(double x, double y, double z){ glTranslatef(x,y,z); }

void display( GLFWwindow* window ) {

    Cube cube("Surface.dat");
    
    while(!glfwWindowShouldClose(window))
    {
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);


        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( 90, (double)windowWidth / (double)windowHeight, 0.1, 100 );

        glMatrixMode(GL_MODELVIEW_MATRIX);
        changeCameraCoords(0,0,-2);
        changePerspective( 0, -1, 0, 0, 2, 0, 0,  0, 1);
        glDepthRange(0.01, 1.0);
        cube.draw();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main(int argc, char** argv)
{
    GLFWwindow* window = initWindow(1000, 1000);
    if( NULL != window )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}