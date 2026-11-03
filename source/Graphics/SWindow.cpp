#include "Graphics/SWindow.hpp"



void shm::SWindow::create(unsigned int width, unsigned int height, const char* title) {
    size = shm::SVec2u(width, height);


    window = glfwCreateWindow(width, height, title, 0, 0);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int halfw = vidmode->width / 2;
    int halfh = vidmode->height / 2;
    
    glfwSetWindowPos(window, halfw - int(width) / 2, halfh - int(height) / 2);
}
