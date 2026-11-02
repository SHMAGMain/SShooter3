#ifndef SHM_OPENGL_OBJECTS_SSHADER_PROGRAM_HPP
#define SHM_OPENGL_OBJECTS_SSHADER_PROGRAM_HPP



#include "GL/glew.h"

#include "SShader.hpp"



namespace shm {
    class SShaderProgram {
        private:

        GLuint id = 0;

        public:

        void create() {
            id = glCreateProgram();
        }

        void bindShader(shm::SShader& shader) {
            glAttachShader(id, shader.getId());
        }

        void link() {
            glLinkProgram(id);
        }


        void uniform1f(GLuint location, float f) {
            use();

            glUniform1f(location, f);
        }

        void uniform2f(GLuint location, float x, float y) {
            use();

            glUniform2f(location, x, y);
        }


        void use() {
            if (!id) {
                std::cout << "ERR: shader program is not created;" << std::endl;
                return;
            }

            glUseProgram(id);
        }


        const GLuint& getId() {
            return id;
        }
    };
}



#endif
