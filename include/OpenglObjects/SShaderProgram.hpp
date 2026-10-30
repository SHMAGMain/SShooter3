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


        void use() {
            glUseProgram(id);
        }
    };
}



#endif
