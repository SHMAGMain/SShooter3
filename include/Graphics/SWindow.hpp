#ifndef SHM_GRAPHICS_SWINDOW_HPP
#define SHM_GRAPHICS_SWINDOW_HPP



#include "GLFW/glfw3.h"



namespace shm {
    class SWindow {
        private:

        GLFWwindow* window = nullptr;

        public:

        void create(unsigned int width, unsigned int height, const char* title);


        GLFWwindow* get() {
            return window;
        }
    };
}



#endif
