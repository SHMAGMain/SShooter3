#ifndef SHM_SMATH_SVEC4F_HPP
#define SHM_SMATH_SVEC4F_HPP



#include "SVec3f.hpp"



namespace shm {
    class SVec4f {
        public:

        float x = 0;
        float y = 0;
        float z = 0;
        float w = 0;



        SVec4f() {}

        SVec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}



        shm::SVec3f to3NoW() {
            return shm::SVec3f(x, y, z);
        }
    };
}



#endif
