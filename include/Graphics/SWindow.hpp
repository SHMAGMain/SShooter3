#ifndef SHM_GRAPHICS_SWINDOW_HPP
#define SHM_GRAPHICS_SWINDOW_HPP



#include "GLFW/glfw3.h"

#include "../SMath/SVec2u.hpp"



namespace shm {
    class SWindow {
        private:

        GLFWwindow* window = nullptr;
        shm::SVec2u size;

        public:

        void create(unsigned int width, unsigned int height, const char* title);


        const shm::SVec2u& getSize() {
            return size;
        }


        GLFWwindow* get() {
            return window;
        }
    };
}



#endif
