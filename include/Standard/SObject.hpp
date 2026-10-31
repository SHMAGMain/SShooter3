#ifndef SHM_STANDARD_SOBJECT_HPP
#define SHM_STANDARD_SOBJECT_HPP



#include "../SMath/STransform.hpp"



namespace shm {
    class SObject {
        protected:

        shm::STransform transform;

        public:

        virtual ~SObject() = default;
    };
}



#endif
