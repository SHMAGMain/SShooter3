#ifndef SHM_OPENGL_OBJECTS_SVBO_HPP
#define SHM_OPENGL_OBJECTS_SVBO_HPP



#include <vector>
#include <iostream>

#include "GL/glew.h"



namespace shm {
    class SVBO {
        private:

        uint32_t id = 0;

        public:

        void create() {
            glGenBuffers(1, &id);
        }

        void destroy() {
            glDeleteBuffers(1, &id);
            id = 0;
        }


        void loadData(std::vector<float>& data, const GLenum& usage) {
            if (!id) { 
                std::cout << "ERR: VBO is not created;" << std::endl; 
                return; 
            }

            glBindBuffer(GL_ARRAY_BUFFER, id);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), usage);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void loadData(float* data, uint32_t count, const GLenum& usage) {
            if (!id) { 
                std::cout << "ERR: VBO is not created;" << std::endl; 
                return; 
            }

            glBindBuffer(GL_ARRAY_BUFFER, id);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, usage);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }


        const uint32_t& getId() {
            return id;
        }
    };
}



#endif
