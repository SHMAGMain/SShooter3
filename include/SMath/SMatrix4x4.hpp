#ifndef SHM_SMATH_SMATRIX4X4_HPP
#define SHM_SMATH_SMATRIX4X4_HPP



#include <cstring>



namespace shm {
    class SMatrix4x4 {
        private:

        float m[16];

        public:

        void toZero() {
            memset(m, 0, sizeof(float) * 16);
        }

        void toOne() {
            memset(m, 0, sizeof(float) * 16);

            m[0] = 1.0f;
            m[5] = 1.0f;
            m[10] = 1.0f;
            m[15] = 1.0f;
        }

        void toTranslate(float x, float y, float z) {
            memset(m, 0, sizeof(float) * 16);

            
        }
    };
}



#endif
