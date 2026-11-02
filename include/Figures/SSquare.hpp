#ifndef SHM_FIGURES_SSQUARE_HPP
#define SHM_FIGURES_SSQUARE_HPP



#include "SFigure.hpp"
#include "../Graphics/SDrawable.hpp"



namespace shm {
    class SSquare : public shm::SFigure {
        private:

        public:

        void create() override {
            shm::SDrawable::create();

            data.resize(36);


            data[0] = -0.5f; data[1] = -0.5f; data[2] = 1.0f;
            data[6] = 0.5f; data[7] = -0.5f; data[8] = 1.0f;
            data[12] = 0.5f; data[13] = 0.5f; data[14] = 1.0f;
            data[18] = 0.5f; data[19] = 0.5f; data[20] = 1.0f;
            data[24] = -0.5f; data[25] = 0.5f; data[26] = 1.0f;
            data[30] = -0.5f; data[31] = -0.5f; data[32] = 1.0f;

            loadData(data);
        }


        virtual ~SSquare() {}
    };
}



#endif
