#ifndef SHM_SPHYSICS_SCOLLIDER_HPP
#define SHM_SPHYSICS_SCOLLIDER_HPP



#include "../SMath/STransform.hpp"



namespace shm {
    enum ESColliderTypes {
        None,
        Box,
        Sphere
    };

    class SCollider {
        public:

        ESColliderTypes type = None;

        shm::STransform* transform = nullptr;



        virtual void update() {}



        virtual ~SCollider() {}
    };
}



#endif
