#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#include <iostream>

// Macro for indexing vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace std;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Shader shader1("shader.vs", "shader.fs");
GLuint ShaderProgramID1;
GLuint VBO1;
GLuint VBO2;

#pragma region VBO_FUNCTIONS
GLuint generateObjectBuffer(GLuint VBO, GLfloat vertices[], GLuint numVertices, GLfloat colors[] = NULL)
{
    glGenBuffers(1, &VBO);
    // In OpenGL, we bind (make active) the handle to a target name and then execute commands on that target
    // Buffer will contain an array of vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // After binding, we now fill our object with data, everything in "Vertices" goes to the GPU
    glBufferData(GL_ARRAY_BUFFER, numVertices * 7 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    // if you have more data besides vertices (e.g., vertex colours or normals), use glBufferSubData to tell the buffer when the vertices array ends and when the colors start
    glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * 3 * sizeof(GLfloat), vertices);
    if (colors != NULL)
    {
        glBufferSubData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(GLfloat), numVertices * 4 * sizeof(GLfloat), colors);
    }
    return VBO;
}

void linkCurrentBufferToShader(GLuint shaderProgramID, GLuint numVertices)
{
    GLuint positionID = glGetAttribLocation(shaderProgramID, "vPosition");
    GLuint colorID = glGetAttribLocation(shaderProgramID, "vColor");

    // position data
    glEnableVertexAttribArray(positionID);
    glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // color data
    glEnableVertexAttribArray(colorID);
    glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(numVertices * 3 * sizeof(GLfloat)));
}
#pragma endregion VBO_FUNCTIONS

void setup()
{
    // vertex setup
    GLfloat vertices0[] = {-1.0f, -1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           0.0f, 1.0f, 0.0f};
    GLfloat vertices1[] = {-1.0f, 1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           0.0f, 1.0f, 0.0f};
    // Create a color array that identfies the colors of each vertex (format R, G, B, A)
    GLfloat colours[] = {0.0f, 1.0f, 0.0f, 1.0f,
                         1.0f, 0.0f, 0.0f, 1.0f,
                         0.0f, 0.0f, 1.0f, 1.0f};
    GLuint numVertices = 3;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VBO1 = generateObjectBuffer(VBO1, vertices0, numVertices, colours);
    VBO2 = generateObjectBuffer(VBO2, vertices1, numVertices);
    // build and compile shaders
    Shader shader("shader1.vs", "shader1.fs");
    ShaderProgramID1 = shader.ID;
}

void display(GLFWwindow *window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(ShaderProgramID1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    linkCurrentBufferToShader(ShaderProgramID1, 3);

    // NB: Make the call to draw the geometry in the currently activated vertex buffer. This is where the GPU starts to work!
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function points
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "failed to init glad");
        return -1;
    }

    setup();
    while (!glfwWindowShouldClose(window))
    {
        display(window);
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}