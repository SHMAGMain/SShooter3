#ifndef SHM_STANDARD_SCAMERA_HPP
#define SHM_STANDARD_SCAMERA_HPP



#include <cmath>

#include "GLFW/glfw3.h"

#include "SObject.hpp"
#include "../SMath/SVec4f.hpp"
#include "../Graphics/SWindow.hpp"
#include "../SMath/SVec3f.hpp"
#include "../SMath/SVec2f.hpp"



namespace shm {
    class SCamera : public shm::SObject {
        private:

        float moveSpeed = 0.01f;
        float rotateSpeed = 0.04f;


        float forceRotationX = 0;
        float forceRotationY = 0;
        float dampingRotation = 0.8f;

        public:

        void updateController(shm::SWindow& window);


        virtual ~SCamera() {}
    };
}



#endif
