#ifndef SHM_SMATH_SVEC2U_HPP
#define SHM_SMATH_SVEC2U_HPP



namespace shm {
    class SVec2u {
        public:

        unsigned int x = 0;
        unsigned int y = 0;

        SVec2u() {}

        SVec2u(unsigned int x, unsigned int y) : x(x), y(y) {}
    };
}



#endif
