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
    cube.transform.setScale(0.03f, 0.05f, 0.04f);
    cube.transform.setPosition(0, -0.06, 0);

    shm::SCube cube2;
    cube2.assignProgram(shaderProgram);
    cube2.create();
    cube2.setColor(shm::SVec3f(0.6f, 1.0f, 1.0f));
    cube2.transform.setScale(0.09f, 0.03f, 0.08f);
    cube2.transform.setPosition(0, 0.06, 0);

    shm::SCube cube3;
    cube3.assignProgram(shaderProgram);
    cube3.create();
    cube3.setColor(shm::SVec3f(0.6f, 1.0f, 1.0f));
    cube3.transform.setScale(0.09f, 0.03f, 0.04f);
    cube3.transform.setPosition(0.2, 0.06, 0);



    bool isWindowClosed = false;

    shm::SColliderBox box1;
    shm::SColliderBox box2;
    shm::SColliderBox box3;
    box2.isStatic = true;
    box3.isStatic = true;
    box1.create(cube.transform);
    box2.create(cube2.transform);
    box3.create(cube3.transform);

    for (int i = 0; i < 8; i++) {
    auto& v = box3.vertices[i];

    printf("%d: %.5f %.5f %.5f\n",
        i, v.x, v.y, v.z);
}

    while (!glfwWindowShouldClose(window.get()) && !isWindowClosed) {
        glClearColor(0.1f, 0.1f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE)) isWindowClosed = true;



        //camera.transform.setPosition(cube.transform.getPosition());
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


        cube.updateMatrixes();
        cube2.updateMatrixes();
        cube3.updateMatrixes();

        box1.update();
        box2.update();
        box3.update();  


        shm::SPhysicsEngine::checkCollisionBB(box1, box2);
        shm::SPhysicsEngine::checkCollisionBB(box1, box3);
        shm::SPhysicsEngine::checkCollisionBB(box2, box3);


        if (glfwGetKey(window.get(), GLFW_KEY_R)) cube3.transform.addRotation(0.06f, 0, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_T)) cube3.transform.addRotation(0, 0.06f, 0);
        if (glfwGetKey(window.get(), GLFW_KEY_Y)) cube3.transform.addRotation(0, 0, 0.06f);
 

        cube.draw();
        cube2.draw();
        cube3.draw();


        box1.debug(shm::SVec3f(1, 0, 0));
        box2.debug(shm::SVec3f(0, 1, 0));
        box3.debug(shm::SVec3f(0, 0, 1));

        //dshm::SDebug::drawBox(box1.transform->getPosition(), box1.transform->getRotation(), box1.transform->getScale(), shm::SVec3f(1, 0, 0));
        //dshm::SDebug::drawBox(box3.transform->getPosition(), box3.transform->getRotation(), box3.transform->getScale(), shm::SVec3f(0, 1, 0));
        


        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;
}
