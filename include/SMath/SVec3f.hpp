#ifndef SHM_SMATH_SVEC3F_HPP
#define SHM_SMATH_SVEC3F_HPP



namespace shm {
    class SVec3f {
        public:
        
        float x = 0;
        float y = 0;
        float z = 0;

        SVec3f() {}

        SVec3f(float x, float y, float z) : x(x), y(y), z(z) {}


        shm::SVec3f& operator+=(const shm::SVec3f& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        shm::SVec3f& operator-=(const shm::SVec3f& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
    };
}



#endif
