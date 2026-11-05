#ifndef SHM_MESHES_SPLANE_HPP
#define SHM_MESHES_SPLANE_HPP



#include "SMesh.hpp"
#include "../SMath/SVec3f.hpp"



namespace shm {
    class SPlane : public shm::SMesh {
        private:

        public:

        void create() override {
            shm::SMesh::create();

            data.resize(54);

            std::vector<shm::SVec3f> vs{4};

            vs[0] = shm::SVec3f{-0.5f, 0, -0.5f};
            vs[1] = shm::SVec3f{-0.5f, 0, 0.5f};
            vs[2] = shm::SVec3f{0.5f, 0, 0.5f};
            vs[3] = shm::SVec3f{0.5f, 0, -0.5f};

            int ips[] = {
                0, 1, 2, 2, 3, 0
            };

            int ind = 0;
            for (size_t i = 0; i < 6; i++) {
                shm::SVec3f& v = vs[ips[i]];

                data[ind] = v.x;
                data[ind + 1] = v.y;
                data[ind + 2] = v.z;

                data[ind + 3] = 0;
                data[ind + 4] = 1.0f;
                data[ind + 5] = 0;

                ind += 9;
            }

            loadData(data);
        }



        virtual ~SPlane() {}
    };
}



#endif
