#ifndef SHM_FIGURES_SSQUARE_HPP
#define SHM_FIGURES_SSQUARE_HPP



#include "SFigure.hpp"
#include "../Graphics/SDrawable.hpp"



namespace shm {
    class SSquare : public shm::SFigure {
        private:

        float size = 1.0f;

        public:

        void create() override {
            shm::SDrawable::create();

            data.resize(36);


            float halfSize = size * 0.5f;

            data[0] = -halfSize; data[1] = -halfSize; data[2] = 0.0f;
            data[6] = halfSize; data[7] = -halfSize; data[8] = 0.0f;
            data[12] = halfSize; data[13] = halfSize; data[14] = 0.0f;
            data[18] = halfSize; data[19] = halfSize; data[20] = 0.0f;
            data[24] = -halfSize; data[25] = halfSize; data[26] = 0.0f;
            data[30] = -halfSize; data[31] = -halfSize; data[32] = 0.0f;

            loadData(data);
        }


        virtual ~SSquare() {}
    };
}



#endif
