#ifndef SHM_MESHES_SCUBE_HPP
#define SHM_MESHES_SCUBE_HPP



#include <vector>

#include "SMesh.hpp"
#include "../SMath/SVec3f.hpp"
#include "../Graphics/SDrawable.hpp"



namespace shm {
    class SCube : public shm::SMesh {
        private:


        public:

        void create() override {
            shm::SMesh::create();

            data.resize(324);


            std::vector<shm::SVec3f> vs{8};
            
            vs[0] = shm::SVec3f{-0.5f, -0.5f, -0.5f};
            vs[1] = shm::SVec3f{-0.5f, 0.5f, -0.5f};
            vs[2] = shm::SVec3f{0.5f, 0.5f, -0.5f};
            vs[3] = shm::SVec3f{0.5f, -0.5f, -0.5f};
            vs[4] = shm::SVec3f{-0.5f, -0.5f, 0.5f};
            vs[5] = shm::SVec3f{-0.5f, 0.5f, 0.5f};
            vs[6] = shm::SVec3f{0.5f, 0.5f, 0.5f};
            vs[7] = shm::SVec3f{0.5f, -0.5f, 0.5f};

            std::vector<shm::SVec3f> ndirs{6};

            ndirs[0] = shm::SVec3f(0, 0, -1.0f);
            ndirs[1] = shm::SVec3f(0, 0, 1.0f);
            ndirs[2] = shm::SVec3f(0, -1.0f, 0);
            ndirs[3] = shm::SVec3f(0, 1.0f, 0);
            ndirs[4] = shm::SVec3f(-1.0f, 0, 0);
            ndirs[5] = shm::SVec3f(1.0f, 0, 0);

            
            int is[] = {
                0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4, 1, 5, 6, 6, 2, 1, 0, 4, 7, 7, 3, 0
            };

            int ins[] = {
                0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2
            };

            size_t id = 0;
            for (size_t i = 0; i < 36; i++) {
                shm::SVec3f& v = vs[is[i]];
                shm::SVec3f& n = ndirs[ins[i]];

                data[id] = v.x;
                data[id + 1] = v.y;
                data[id + 2] = v.z;

                data[id + 3] = n.x;
                data[id + 4] = n.y;
                data[id + 5] = n.z;

                id += 9;
            }

            loadData(data);
        }



        virtual ~SCube() {}
    };
}



#endif
