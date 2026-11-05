#ifndef SHM_SPHYSICS_SCOLLIDER_BOX_HPP
#define SHM_SPHYSICS_SCOLLIDER_BOX_HPP



#include <vector>

#include "SCollider.hpp"
#include "../SMath/SVec3f.hpp"



namespace shm {
    class SColliderBox : public shm::SCollider {
        public:

        std::vector<shm::SVec3f> vertices{8};



        void create(shm::STransform& transform) {
            this->transform = &transform;

            update();
        }

        void update() override {
            vertices[0] = shm::SVec3f{-0.5f, -0.5f, -0.5f};
            vertices[1] = shm::SVec3f{-0.5f, 0.5f, -0.5f};
            vertices[2] = shm::SVec3f{0.5f, 0.5f, -0.5f};
            vertices[3] = shm::SVec3f{0.5f, -0.5f, -0.5f};
            vertices[4] = shm::SVec3f{-0.5f, -0.5f, 0.5f};
            vertices[5] = shm::SVec3f{-0.5f, 0.5f, 0.5f};
            vertices[6] = shm::SVec3f{0.5f, 0.5f, 0.5f};
            vertices[7] = shm::SVec3f{0.5f, -0.5f, 0.5f};



            const shm::SVec3f& scale = transform->getScale();
            shm::SMatrix4x4 rt = transform->getMatrixRotation();
            
            for (shm::SVec3f& v : vertices) {
                v.x *= scale.x;
                v.y *= scale.y;
                v.z *= scale.z;

                v = shm::SMatrix4x4::mul(rt, v);
            }
        }
    };
}



#endif
