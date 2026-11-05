#ifndef SHM_SDEBUG_SDEBUG_HPP
#define SHM_SDEBUG_SDEBUG_HPP



#include <string>

#include "../OpenglObjects/SVAO.hpp"
#include "../OpenglObjects/SVBO.hpp"
#include "../OpenglObjects/SShader.hpp"
#include "../OpenglObjects/SShaderProgram.hpp"
#include "../SMath/SVec3f.hpp"
#include "../Standard/SCamera.hpp"
#include "../SMath/SMatrix4x4.hpp"



namespace dshm {
    class SDebug {
        private:

        static shm::SMatrix4x4* per;
        static shm::SCamera* camera;



        static shm::SVAO vaoLines;
        static shm::SVBO vboLines;
        
        static std::string pathVertexShaderSource;
        static std::string pathFragmentShaderSource;

        static shm::SShaderProgram shaderProgram;



        static std::vector<float> dataBox;

        public:

        static void init(shm::SMatrix4x4& per, shm::SCamera& camera, float ratio) {
            dshm::SDebug::per = &per;
            dshm::SDebug::camera = &camera;



            shaderProgram.create();
            shaderProgram.use();

            shm::SShader vertexShader;
            shm::SShader fragmentShader;
            
            vertexShader.create(GL_VERTEX_SHADER);
            fragmentShader.create(GL_FRAGMENT_SHADER);

            vertexShader.loadSourceAndCompile(pathVertexShaderSource);
            fragmentShader.loadSourceAndCompile(pathFragmentShaderSource);

            shaderProgram.create();

            shaderProgram.bindShader(vertexShader);
            shaderProgram.bindShader(fragmentShader);

            shaderProgram.link();



            shaderProgram.uniform1f(glGetUniformLocation(shaderProgram.getId(), "ratio"), ratio);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "per"), 1, GL_FALSE, per.getData());



            vaoLines.create();
            vboLines.create();

            glBindVertexArray(vaoLines.getId());
            glBindBuffer(GL_ARRAY_BUFFER, vboLines.getId());

            vaoLines.setAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

            vaoLines.enableAttrib(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }



        static void drawBox(const shm::SVec3f& position, const shm::SVec3f& rotation, const shm::SVec3f& scale, const shm::SVec3f& color) {
            glDisable(GL_DEPTH_TEST);

            shm::SMatrix4x4 s;
            shm::SMatrix4x4 t;

            s.toScale(scale.x, scale.y, scale.z);
            t.toTranslate(position.x, position.y, position.z);

            shm::SMatrix4x4 rx;
            shm::SMatrix4x4 ry;
            shm::SMatrix4x4 rz;

            rx.toRotX(rotation.x);
            ry.toRotY(rotation.y);
            rz.toRotZ(rotation.z);

            shm::SMatrix4x4 rxyz = shm::SMatrix4x4::mul(rz, shm::SMatrix4x4::mul(ry, rx));

            shm::SMatrix4x4 model = shm::SMatrix4x4::mul(t, shm::SMatrix4x4::mul(rxyz, s));



            shaderProgram.use();
            glUniform3f(glGetUniformLocation(shaderProgram.getId(), "ucolor"), color.x, color.y, color.z);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "model"), 1, GL_FALSE, model.getData());
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getId(), "view"), 1, GL_FALSE, camera->transform.getMatrixView().getData());


            glBindVertexArray(vaoLines.getId());
            glBindBuffer(GL_ARRAY_BUFFER, vboLines.getId());

            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataBox.size(), dataBox.data(), GL_DYNAMIC_DRAW);

            glDrawArrays(GL_LINES, 0, dataBox.size());


            glEnable(GL_DEPTH_TEST);
        }
    };

    shm::SVAO dshm::SDebug::vaoLines;
    shm::SVBO dshm::SDebug::vboLines;

    shm::SShaderProgram dshm::SDebug::shaderProgram;

    shm::SMatrix4x4* dshm::SDebug::per = nullptr;
    shm::SCamera* dshm::SDebug::camera = nullptr;

    std::string dshm::SDebug::pathVertexShaderSource = "res/shaders/VertexShader.versh";
    std::string dshm::SDebug::pathFragmentShaderSource = "res/shaders/FragmentShader.frash";

    std::vector<float> dshm::SDebug::dataBox = std::vector<float>{
        -1, -1, -1, 1, -1, -1,
        1, -1, -1, 1, 1, -1,
        1, 1, -1, -1, 1, -1,
        -1, 1, -1, -1, -1, -1,
        -1, -1, 1, 1, -1, 1, 
        1, -1, 1, 1, 1, 1,
        1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, 1,
        -1, -1, 1, -1, -1, -1,
        -1, 1, 1, -1, 1, -1,
        1, -1, 1, 1, -1, -1,
        1, 1, 1, 1, 1, -1
    };
}



#endif
