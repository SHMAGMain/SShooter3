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
    cube.transform.setPosition(0, -0.06, 0);

    shm::SCube cube2;
    cube2.assignProgram(shaderProgram);
    cube2.create();
    cube2.setColor(shm::SVec3f(0.6f, 1.0f, 1.0f));
    cube2.transform.setScale(0.09f, 0.03f, 0.04f);
    cube2.transform.setPosition(0, 0.06, 0);



    bool isWindowClosed = false;

    shm::SColliderBox box1;
    shm::SColliderBox box2;
    box1.create(cube.transform);
    box2.create(cube2.transform);

    while (!glfwWindowShouldClose(window.get()) && !isWindowClosed) {
        glClearColor(0.1f, 0.1f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE)) isWindowClosed = true;



        camera.transform.updateMatrixes();
        camera.updateController(window);

        glUseProgram(shaderProgram.getId());
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "view"), 1, GL_FALSE, camera.transform.getMatrixView().getData());


        
        float speed = 0.001f;
        if (glfwGetKey(window.get(), GLFW_KEY_UP)) cube.transform.addPosition(0, -speed, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_DOWN)) cube.transform.addPosition(0, speed, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_RIGHT)) cube.transform.addPosition(speed, 0, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_LEFT)) cube.transform.addPosition(-speed, 0, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_E)) cube.transform.addRotation(0, 0, 1);
        if (glfwGetKey(window.get(), GLFW_KEY_Q)) cube.transform.addRotation(0, 0, -1);


        box1.update();
        box2.update();


        if (shm::SPhysicsEngine::checkCollisionBB(box1, box2)) {
            std::cout << "True" << std::endl;
        }
        else {
            std::cout << "False" << std::endl;
        }


        cube.updateMatrixes();
        cube.draw();
        cube2.updateMatrixes();
        cube2.draw();



        //dshm::SDebug::drawBox(cube.transform.getPosition(), cube.transform.getRotation(), cube.transform.getScale(), shm::SVec3f(1, 0, 0));
        //dshm::SDebug::drawBox(cube2.transform.getPosition(), cube2.transform.getRotation(), cube2.transform.getScale(), shm::SVec3f(0, 1, 0));


        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;
}
