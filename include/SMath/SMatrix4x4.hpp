#ifndef SHM_SMATH_SMATRIX4X4_HPP
#define SHM_SMATH_SMATRIX4X4_HPP



#include <cstring>
#include <cmath>
#include <iostream>



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
            toOne();

            m[12] = x;
            m[13] = y;
            m[14] = z;
        }

        void toScale(float x, float y, float z) {
            toZero();

            m[0] = x;
            m[5] = y;
            m[10] = z;
            m[15] = 1.0f;
        }

        void toPerspective() {
            toOne();

            m[10] = 0.03f;
            m[11] = 1.0f;
        }

        void toRotX(float x) {
            toOne();

            float s = std::cos(x * 0.0174532925f);
            float c = std::sin(x * 0.0174532925f);

            m[5] = s;
            m[6] = c;
            m[9] = c;
            m[10] = -s;
        }

        void toRotY(float y) {
            toOne();

            float s = std::cos(y * 0.0174532925f);
            float c = std::sin(y * 0.0174532925f);

            m[0] = s;
            m[2] = c;
            m[8] = c;
            m[10] = -s;
        }

        void toRotZ(float z) {
            toOne();

            float s = std::cos(z * 0.0174532925f);
            float c = std::sin(z * 0.0174532925f);

            m[0] = s;
            m[1] = c;
            m[4] = c;
            m[5] = -s;
        }


        float* getData() {
            return m;
        }


        void debug() { 
            std::cout << "DEBUG: " << std::endl << "| " << m[0] << " " << m[4] << " " << m[8] << " " << m[12] << " |" << std::endl;
            std::cout << "| " << m[1] << " " << m[5] << " " << m[9] << " " << m[13] << " |" << std::endl;
            std::cout << "| " << m[2] << " " << m[6] << " " << m[10] << " " << m[14] << " |" << std::endl;
            std::cout << "| " << m[3] << " " << m[7] << " " << m[11] << " " << m[15] << " |" << std::endl;
        }



        static shm::SMatrix4x4 mul(const shm::SMatrix4x4& a, const shm::SMatrix4x4& b) {
            shm::SMatrix4x4 r;

            r.m[0]  =  a.m[0] * b.m[0]  +  a.m[4] * b.m[1]  +  a.m[8] * b.m[2]  +  a.m[12] * b.m[3];
            r.m[4]  =  a.m[0] * b.m[4]  +  a.m[4] * b.m[5]  +  a.m[8] * b.m[6]  +  a.m[12] * b.m[7];
            r.m[8]  =  a.m[0] * b.m[8]  +  a.m[4] * b.m[9]  +  a.m[8] * b.m[10]  +  a.m[12] * b.m[11];
            r.m[12]  =  a.m[0] * b.m[12]  +  a.m[4] * b.m[13]  +  a.m[8] * b.m[14]  +  a.m[12] * b.m[15];

            r.m[1]  =  a.m[1] * b.m[0]  +  a.m[5] * b.m[1]  +  a.m[9] * b.m[2]  +  a.m[13] * b.m[3];
            r.m[5]  =  a.m[1] * b.m[4]  +  a.m[5] * b.m[5]  +  a.m[9] * b.m[6]  +  a.m[13] * b.m[7];
            r.m[9]  =  a.m[1] * b.m[8]  +  a.m[5] * b.m[9]  +  a.m[9] * b.m[10]  +  a.m[13] * b.m[11];
            r.m[13]  =  a.m[1] * b.m[12]  +  a.m[5] * b.m[13]  +  a.m[9] * b.m[14]  +  a.m[13] * b.m[15];

            r.m[2]  =  a.m[2] * b.m[0]  +  a.m[6] * b.m[1]  +  a.m[10] * b.m[2]  +  a.m[14] * b.m[3];
            r.m[6]  =  a.m[2] * b.m[4]  +  a.m[6] * b.m[5]  +  a.m[10] * b.m[6]  +  a.m[14] * b.m[7];
            r.m[10]  =  a.m[2] * b.m[8]  +  a.m[6] * b.m[9]  +  a.m[10] * b.m[10]  +  a.m[14] * b.m[11];
            r.m[14]  =  a.m[2] * b.m[12]  +  a.m[6] * b.m[13]  +  a.m[10] * b.m[14]  +  a.m[14] * b.m[15];

            r.m[3]  =  a.m[3] * b.m[0]  +  a.m[7] * b.m[1]  +  a.m[11] * b.m[2]  +  a.m[15] * b.m[3];
            r.m[7]  =  a.m[3] * b.m[4]  +  a.m[7] * b.m[5]  +  a.m[11] * b.m[6]  +  a.m[15] * b.m[7];
            r.m[11]  =  a.m[3] * b.m[8]  +  a.m[7] * b.m[9]  +  a.m[11] * b.m[10]  +  a.m[15] * b.m[11];
            r.m[15]  =  a.m[3] * b.m[12]  +  a.m[7] * b.m[13]  +  a.m[11] * b.m[14]  +  a.m[15] * b.m[15];
            
            return r;
        }
    };
}



#endif
