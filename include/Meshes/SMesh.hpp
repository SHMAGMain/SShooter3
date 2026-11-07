#ifndef SHM_MESHES_SMESH_HPP
#define SHM_MESHES_SMESH_HPP



#include "../Graphics/SDrawable.hpp"



namespace shm {
    class SMesh : public shm::SDrawable {
        private:

        public:

        void create() override {
            VAO.create();
            VBO.create();

            glBindVertexArray(VAO.getId());
            glBindBuffer(GL_ARRAY_BUFFER, VBO.getId());

            VAO.bindVBO(VBO);

            VAO.setAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
            VAO.setAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, sizeof(float) * 3);
            VAO.setAttrib(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, sizeof(float) * 6);

            VAO.enableAttrib(0);
            VAO.enableAttrib(1);
            VAO.enableAttrib(2);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }



        void setColor(shm::SVec3f newColor) override {
            for (size_t i = 6; i < data.size(); i += 9) {
                data[i] = newColor.x;
                data[i + 1] = newColor.y;
                data[i + 2] = newColor.z;
            }

            loadData(data);
        }



        void draw() override {
            shaderProgram->use();

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getId(), "model"), 1, GL_FALSE, transform.getMatrixModel().getData());
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getId(), "mNormal"), 1, GL_FALSE, transform.getMatrixNormal().getData());

            glBindVertexArray(VAO.getId());
            glDrawArrays(GL_TRIANGLES, 0, data.size() / 9);
            glBindVertexArray(0);
        }



        virtual ~SMesh() {}
    };
}



#endif
