#ifndef SHM_SPHYSICS_SCOLLIDER_BOX_HPP
#define SHM_SPHYSICS_SCOLLIDER_BOX_HPP



#include <vector>

#include "SCollider.hpp"
#include "../SMath/SVec3f.hpp"



namespace shm {
    class SColliderBox : public shm::SCollider {
        public:

        std::vector<shm::SVec4f> vertices{8};



        void create(shm::STransform& transform) {
            this->transform = &transform;

            update();
        }

        void update() override {
            vertices[0] = shm::SVec4f{-1, -1, -1, 1};
            vertices[1] = shm::SVec4f{-1, 1, -1, 1};
            vertices[2] = shm::SVec4f{1, 1, -1, 1};
            vertices[3] = shm::SVec4f{1, -1, -1, 1};
            vertices[4] = shm::SVec4f{-1, -1, 1, 1};
            vertices[5] = shm::SVec4f{-1, 1, 1, 1};
            vertices[6] = shm::SVec4f{1, 1, 1, 1};
            vertices[7] = shm::SVec4f{1, -1, 1, 1};



            const shm::SVec3f& scale = transform->getScale();
            shm::SMatrix4x4& r = transform->getMatrixRotation();
            shm::SMatrix4x4& t = transform->getMatrixPosition();
            
            for (size_t i = 0; i < 8; i++) {
                vertices[i].x *= scale.x;
                vertices[i].y *= scale.y;
                vertices[i].z *= scale.z;

                vertices[i] = shm::SMatrix4x4::mul(t, shm::SMatrix4x4::mul(r, vertices[i]));
            }
        }



        virtual ~SColliderBox() {}
    };
}



#endif
