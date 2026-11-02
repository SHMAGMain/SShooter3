#ifndef SHM_GRAPHICS_DRAWABLE_HPP
#define SHM_GRAPHICS_DRAWABLE_HPP



#include <vector>

#include "../Standard/SObject.hpp"
#include "../OpenglObjects/SVAO.hpp"
#include "../OpenglObjects/SVBO.hpp"
#include "../OpenglObjects/SShaderProgram.hpp"
#include "../SMath/SVec3f.hpp"



namespace shm {
    class SDrawable : public shm::SObject {
        protected:

        shm::SShaderProgram* shaderProgram = nullptr;

        shm::SVAO VAO;
        shm::SVBO VBO;

        std::vector<float> data;

        public:

        void assignProgram(shm::SShaderProgram& program) {
            shaderProgram = &program;
        }

        void create() override {
            shm::SObject::create();

            VAO.create();
            VBO.create();

            glBindVertexArray(VAO.getId());
            glBindBuffer(GL_ARRAY_BUFFER, VBO.getId());

            VAO.bindVBO(VBO);

            VAO.setAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
            VAO.setAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, sizeof(float) * 3);

            VAO.enableAttrib(0);
            VAO.enableAttrib(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }


        virtual void updateMatrixes() {
            transform.updateMatrix();

            shaderProgram->use();
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getId(), "model"), 1, GL_FALSE, transform.getMatrixModel().getData());
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getId(), "mNormal"), 1, GL_FALSE, transform.getMatrixNormal().getData());
        }


        virtual void loadData(std::vector<float>& data) {
            VBO.loadData(data, GL_STATIC_DRAW);
        }


        virtual void setColor(shm::SVec3f newColor) {
            for (size_t i = 3; i < data.size(); i += 6) {
                data[i] = newColor.x;
                data[i + 1] = newColor.y;
                data[i + 2] = newColor.z;
            }

            loadData(data);
        }


        virtual void draw() {
            shaderProgram->use();
            glBindVertexArray(VAO.getId());
            glDrawArrays(GL_TRIANGLES, 0, data.size() / 6);
        }


        virtual ~SDrawable() {}
    };
}



#endif
