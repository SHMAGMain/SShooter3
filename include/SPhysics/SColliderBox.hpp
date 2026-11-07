#ifndef SHM_SPHYSICS_SCOLLIDER_BOX_HPP
#define SHM_SPHYSICS_SCOLLIDER_BOX_HPP



#include <vector>

#include "SCollider.hpp"
#include "../SMath/SVec3f.hpp"
#include "../SDebug/SDebug.hpp"



namespace shm {
    class SColliderBox : public shm::SCollider {
        public:

        std::vector<shm::SVec4f> vertices{8};



        void create(shm::STransform& transform) {
            this->transform = &transform;

            type = shm::ESColliderTypes::Box;

            update();
        }

        void update() override {
            vertices[0] = {-1, -1, -1, 1};
            vertices[1] = {-1,  1, -1, 1};
            vertices[2] = { 1,  1, -1, 1};
            vertices[3] = { 1, -1, -1, 1};
            vertices[4] = {-1, -1,  1, 1};
            vertices[5] = {-1,  1,  1, 1};
            vertices[6] = { 1,  1,  1, 1};
            vertices[7] = { 1, -1,  1, 1};

            shm::SMatrix4x4 s;
            s.toScale(
                transform->getScale().x,
                transform->getScale().y,
                transform->getScale().z
            );

            auto& r = transform->getMatrixRotation();
            auto& t = transform->getMatrixPosition();

            for (size_t i = 0; i < 8; i++) {
               auto scaled = shm::SMatrix4x4::mul(s, vertices[i]);
                auto rotated = shm::SMatrix4x4::mul(r, scaled);
                auto translated = shm::SMatrix4x4::mul(t, rotated);

                vertices[i] = translated;
            }
        }

        void debug(const shm::SVec3f& color) override {
            dshm::SDebug::drawBox(transform->getPosition(), transform->getRotation(), transform->getScale(), color);
        }



        virtual ~SColliderBox() {}
    };
}



#endif
