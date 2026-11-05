#ifndef SHM_SMATH_SVEC3F_HPP
#define SHM_SMATH_SVEC3F_HPP



#include <cmath>



namespace shm {
    class SVec3f {
        public:
        
        float x = 0;
        float y = 0;
        float z = 0;

        SVec3f() {}

        SVec3f(float x, float y, float z) : x(x), y(y), z(z) {}



        shm::SVec3f negative() {
            return shm::SVec3f(-x, -y, -z);
        }


        void mul(float f) {
            x *= f;
            y *= f;
            z *= f;
        }

        void normalize() {
            float m = std::sqrt(x * x + y * y + z * z);

            if (m != 0) {
                x /= m;
                y /= m;
                z /= m;
            }
        }


        static shm::SVec3f smul(const shm::SVec3f& v, float f) {
            return shm::SVec3f(v.x * f, v.y * f, v.z * f);
        }

        static shm::SVec3f sadd(const shm::SVec3f& a, const shm::SVec3f& b) {
            return shm::SVec3f(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        
        static shm::SVec3f getNormalize(const shm::SVec3f& v) {
            float m = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
            if (m != 0) {
                return shm::SVec3f(v.x / m, v.y / m, v.z / m);
            }
            else {
                return shm::SVec3f();
            }
        }

        static float getProj(const shm::SVec3f& a, const shm::SVec3f& b) {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }



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
