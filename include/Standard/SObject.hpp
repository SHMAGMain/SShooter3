#ifndef SHM_STANDARD_SOBJECT_HPP
#define SHM_STANDARD_SOBJECT_HPP



#include "../SMath/STransform.hpp"



namespace shm {
    class SObject {
        public:

        shm::STransform transform;



        virtual void create() {}



        virtual ~SObject() = default;
    };
}



#endif
