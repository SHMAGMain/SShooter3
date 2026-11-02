#include "Graphics/SWindow.hpp"



void shm::SWindow::create(unsigned int width, unsigned int height, const char* title) {
    window = glfwCreateWindow(width, height, title, 0, 0);
}
