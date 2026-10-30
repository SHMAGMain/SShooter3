#ifndef SHM_GRAPHICS_DRAWABLE_HPP
#define SHM_GRAPHICS_DRAWABLE_HPP



#include <vector>

#include "../Standard/SObject.hpp"
#include "../OpenglObjects/SVAO.hpp"
#include "../OpenglObjects/SVBO.hpp"
#include "../OpenglObjects/SShaderProgram.hpp"



namespace shm {
    class SDrawable : private shm::SObject{
        private:

        shm::SShaderProgram* shaderProgram = nullptr;

        shm::SVAO VAO;
        shm::SVBO VBO;

        std::vector<float> data;

        public:

        void assignProgram(shm::SShaderProgram& program) {
            shaderProgram = &program;
        }

        virtual void create() {
            VAO.create();
            VBO.create();

            VAO.setAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
            VAO.setAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, sizeof(float) * 3);

            VAO.enableAttrib(0);
            VAO.enableAttrib(1);

            VAO.bindVBO(VBO);
        }


        virtual void draw() {
            shaderProgram->use();
            glBindVertexArray(VAO.getId());
            glDrawArrays(GL_TRIANGLES, 0, data.size() / 2);
        }


        virtual ~SDrawable() {}
    };
}



#endif
