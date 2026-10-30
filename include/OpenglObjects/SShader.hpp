#ifndef SHM_OPENGL_OBJECTS_SSHADER_HPP
#define SHM_OPENGL_OBJECTS_SSHADER_HPP



#include <iostream>
#include <fstream>
#include <string>

#include "GL/glew.h"



namespace shm {
    class SShader {
        private:

        GLuint id = 0;

        public:

        void create(const GLenum& type) {
            if (!id) {
                id = glCreateShader(type);
            }
            else {
                std::cout << "ERR: shader has already been created;" << std::endl;
            }
        }

        void loadSourceAndCompile(const std::string& path) {
            if (!id) {
                std::cerr << "ERR: shader is not created;" << std::endl;
            }


            std::ifstream file(path);

            if (file.is_open()) {
                std::string line;
                std::string source;

                while (std::getline(file, line)) {
                    source += line;
                    source += '\n';
                }

                source += '\0';


                const char* csource = source.c_str();
                glShaderSource(id, 1, &csource, 0);

                glCompileShader(id);


                GLint success;
                glGetShaderiv(id, GL_COMPILE_STATUS, &success);

                if (!success) {
                    char log[512];

                    glGetShaderInfoLog(id, 512, 0, log);

                    std::cerr << "ERR: cannot compile shader; LOG: " << log << std::endl;
                }
                else {
                    std::cout << "OUT: shader compile is success;" << std::endl;
                }
            }
            else {
                std::cerr << "ERR: cannot open file;" << std::endl;
            }
        }


        void destroy() {
            glDeleteShader(id);
            id = 0;
        }


        const GLuint& getId() {
            return id;
        }
    };
}



#endif
