#include "library.hpp"
#include "main.hpp"

glm::vec3 cameraPosition(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFront(0.0f, 0.0f, 1.0f);
glm::vec3 cameraRight(1.0f, 0.0f, 0.0f);

float cameraSpeed = 0.05f;
float yaw = -90.0f;   
float pitch = 0.0f;

void processInput(GLFWwindow* window) {
    // Camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    static double lastX = 400, lastY = 300;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    const float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));

    lastX = xpos;
    lastY = ypos;
}

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

    // .............
    glewExperimental = GL_TRUE;
    glewInit();
    // ..............
    glfwSetKeyCallback(window, controls);

    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));


    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);  

    return window;
}

void changePerspective(double eyeX, double eyeY, double eyeZ,
                       double centerX, double centerY, double centerZ,
                       double upX, double upY, double upZ) {
    glm::vec3 eye(eyeX, eyeY, eyeZ);
    glm::vec3 center(centerX, centerY, centerZ);
    glm::vec3 up(upX, upY, upZ);

    glm::mat4 viewMatrix = glm::lookAt(eye, center, up);
    glLoadMatrixf(glm::value_ptr(viewMatrix));
}

glm::mat4 scaleMatrix(double x, double y, double z) {
    return glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}

glm::mat4 translateMatrix(double x, double y, double z) {
    return glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void changeCameraCoords(double x, double y, double z) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    glMultMatrixf(glm::value_ptr(translationMatrix));
}

void display( GLFWwindow* window ) {

    Cube cube("Surface.dat", "CubeConnectivity.dat");

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), (float)windowWidth / (float)windowHeight, 0.01f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(projectionMatrix));

        glDepthRange(0.01, 1.0);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        
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