#include <vector>
#include <random>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "OpenglObjects/SVAO.hpp"
#include "OpenglObjects/SVBO.hpp"
#include "OpenglObjects/SShader.hpp"
#include "OpenglObjects/SShaderProgram.hpp"
#include "Figures/SSquare.hpp"
#include "SMath/SVec2f.hpp"
#include "Graphics/SWindow.hpp"
#include "Meshes/SCube.hpp"
#include "SMath/STransform.hpp"
#include "Standard/SCamera.hpp"



const uint32_t WINDOW_WIDTH = 1000;
const uint32_t WINDOW_HEIGHT = 800;



shm::SWindow window;



const char* fragmentShaderSource = "#version 330 core\n"
    "in vec3 color;"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(color, 1.0f);\n"
    "}\n\0";


int main() {
    glfwInit();

    window.create(WINDOW_WIDTH, WINDOW_HEIGHT, "SHM-SShooter3");

    glfwMakeContextCurrent(window.get());

    glewExperimental = true;
    glewInit();

    glEnable(GL_DEPTH_TEST);



    shm::SShader vertexShader;
    vertexShader.create(GL_VERTEX_SHADER);
    vertexShader.loadSourceAndCompile("res/shaders/PerVertexShader.versh");

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



    shm::SMatrix4x4 matrixPerspective;
    matrixPerspective.toPerspective();

    shaderProgram.uniform1f(glGetUniformLocation(shaderProgram.getId(), "ratio"), WINDOW_WIDTH / float(WINDOW_HEIGHT));
    shaderProgram.uniform2f(glGetUniformLocation(shaderProgram.getId(), "winSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "per"), 1, GL_FALSE, matrixPerspective.getData());



    int count = 5;


    std::vector<shm::SSquare> squares;

    for (size_t i = 0; i < count; i++) {
        shm::SSquare s;
        s.assignProgram(shaderProgram);
        s.transform.setScale(0.01f, 0.01f, 0);

        squares.push_back(s);
    }

    for (shm::SSquare& square : squares) {
        square.create();

        square.setColor(shm::SVec3f(1.0f, 1.0f, 0.6f));
    }



    std::vector<shm::SVec2f> forces(count);

    std::random_device randev;
    std::mt19937 gen(randev());
    std::uniform_real_distribution<float> dist(-0.012f, 0.012f);

    std::uniform_real_distribution<float> dist2(0, 360);

    for (size_t i = 0; i < count; i++) {
        forces[i] = shm::SVec2f(dist(gen), dist(gen));

        squares[i].transform.addRotation(0, 0, dist2(gen));
        squares[i].transform.addPosition(dist(gen) * 0.5f, dist(gen) * 0.5f, 0);
    }


    shm::SCube cube;
    cube.assignProgram(shaderProgram);
    cube.create();
    cube.setColor(shm::SVec3f(1.0f, 1.0f, 0.6f));
    cube.transform.setScale(0.1f, 0.1f, 0.1f);

    float t = 0;



    shm::SCamera camera;



    bool isWindowClosed = false;

    while (!glfwWindowShouldClose(window.get()) && !isWindowClosed) {
        glClearColor(0.1f, 0.1f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE)) isWindowClosed = true;



        if (glfwGetKey(window.get(), GLFW_KEY_UP)) camera.transform.addRotation(1, 0, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_DOWN)) camera.transform.addRotation(-1, 0, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_RIGHT)) camera.transform.addRotation(0, 1, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_LEFT)) camera.transform.addRotation(0, -1, 0);

        camera.updateController(window);

        glUseProgram(shaderProgram.getId());
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "view"), 1, GL_FALSE, camera.transform.getMatrixView().getData());



        /*for (size_t i = 0; i < count; i++) {
            squares[i].transform.addPosition(shm::SVec3f(forces[i].x, forces[i].y, 0));
            forces[i].x *= 0.98f;
            forces[i].y *= 0.98f;

            squares[i].transform.addRotation(0, 0, std::sqrt(forces[i].x * forces[i].x + forces[i].y * forces[i].y) * 200);

            squares[i].updateMatrixModel();

            squares[i].draw();
        }*/

        t += 0.05f;
        //cube.transform.addPosition(std::cos(t) * 0.008f, 0, 0);
        //cube.transform.addRotation(1, 1, 1);
        cube.updateMatrixes();
        cube.draw();



        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;
}
