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
#include "Meshes/SPlane.hpp"
#include "SPhysics/SPhysicsEngine.hpp"
#include "SPhysics/SColliderBox.hpp"
#include "SDebug/SDebug.hpp"



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



    shm::SCamera camera;



    dshm::SDebug::init(matrixPerspective, camera, WINDOW_WIDTH / float(WINDOW_HEIGHT));



    shm::SCube cube;
    cube.assignProgram(shaderProgram);
    cube.create();
    cube.setColor(shm::SVec3f(1.0f, 1.0f, 0.6f));
    cube.transform.setScale(0.03f, 0.03f, 0.03f);
    cube.transform.setPosition(0.1f, -0.06, 0.15f);
    //cube.transform.parent = &camera.transform;

    shm::SCube cube2;
    cube2.assignProgram(shaderProgram);
    cube2.create();
    cube2.setColor(shm::SVec3f(0.6f, 1.0f, 1.0f));
    cube2.transform.setScale(0.03f, 0.03f, 0.03f);
    cube2.transform.setPosition(0.1f, 0.06, 0.15f);
    cube2.transform.parent = &cube.transform;

    shm::SCube cube3;
    cube3.assignProgram(shaderProgram);
    cube3.create();
    cube3.setColor(shm::SVec3f(1.0f, 0.6f, 1.0f));
    cube3.transform.setScale(0.03f, 0.03f, 0.03f);
    cube3.transform.setPosition(0.1f, 0.12, 0.15f);
    cube3.transform.parent = &cube2.transform;

    shm::SPlane plane;
    plane.assignProgram(shaderProgram);
    plane.create();
    plane.setColor(shm::SVec3f(1.0f, 1.0f, 1.0f));
    plane.transform.setScale(2, 0, 2);



    bool isWindowClosed = false;

    while (!glfwWindowShouldClose(window.get()) && !isWindowClosed) {
        glClearColor(0.1f, 0.1f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE)) isWindowClosed = true;



        camera.transform.updateMatrixes();
        camera.updateController(window);

        glUseProgram(shaderProgram.getId());
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "view"), 1, GL_FALSE, camera.transform.getMatrixView().getData());


        cube.transform.addRotation(1, 1, 1);
        cube.updateMatrixes();
        cube.draw();

        cube2.updateMatrixes();
        cube2.draw();

        cube3.updateMatrixes();
        cube3.draw();


        plane.updateMatrixes();
        //plane.draw();

        dshm::SDebug::drawBox(cube3.transform.getPosition(), cube3.transform.getRotation(), cube3.transform.getScale(), shm::SVec3f(1.0f, 1.0f, 1.0f));



        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;
}
