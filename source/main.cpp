#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "OpenglObjects/SVAO.hpp"
#include "OpenglObjects/SVBO.hpp"
#include "OpenglObjects/SShader.hpp"
#include "OpenglObjects/SShaderProgram.hpp"
#include "Figures/SSquare.hpp"



const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;



float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
};


const char* fragmentShaderSource = "#version 330 core\n"
    "in vec3 color;"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(color, 1.0f);\n"
    "}\n\0";


int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", 0, 0);

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    glewInit();


    /*shm::SVAO svao;
    svao.create();

    shm::SVBO svbo;
    svbo.create();
    svbo.loadData(vertices, 36, GL_STATIC_DRAW);
    
    svao.setAttrib(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    svao.setAttrib(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));
    
    svao.enableAttrib(0);
    svao.enableAttrib(1);
    
    svao.bindVBO(svbo);*/


    shm::SShader vertexShader;
    vertexShader.create(GL_VERTEX_SHADER);
    vertexShader.loadSourceAndCompile("res/shaders/VertexShader.versh");

    shm::SShader fragmentShader;
    fragmentShader.create(GL_FRAGMENT_SHADER);
    fragmentShader.loadSourceAndCompile("res/shaders/FragmentShader.frash");

    shm::SShaderProgram shaderProgram;
    shaderProgram.create();

    shaderProgram.bindShader(vertexShader);
    shaderProgram.bindShader(fragmentShader);

    shaderProgram.link();

    vertexShader.destroy();
    fragmentShader.destroy();


    shaderProgram.uniform1f(0, WINDOW_WIDTH / float(WINDOW_HEIGHT));


    shm::SSquare square;
    square.assignProgram(shaderProgram);
    square.create();
    square.setColor(shm::SVec3f(1.0f, 1.0f, 1.0f));



    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        square.draw();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;
}
