#ifndef SHM_SPHYSICS_SPHYSICS_ENGINE_HPP
#define SHM_SPHYSICS_SPHYSICS_ENGINE_HPP



#include "SColliderBox.hpp"
#include "../SMath/SMatrix4x4.hpp"



namespace shm {
    class SPhysicsEngine {
        private:

        bool isAxesCollision(float p0, float p1, float q0, float q1);

        public:

        bool checkCollisionBB(shm::SColliderBox& b1, shm::SColliderBox& b2);
    };
}



#endif
