#ifndef SHM_OPENGL_OBJECTS_SVAO_HPP
#define SHM_OPENGL_OBJECTS_SVAO_HPP



#include "GL/glew.h"

#include "SVBO.hpp"



namespace shm {
    class SVAO {
        private:

        uint32_t id = 0;

        public:

        void create() {
            glGenVertexArrays(1, &id);
        }

        /// @brief Назначает атрибут
        /// @param index номер атрибута
        /// @param count сколько данных в атрибуте
        /// @param type тип данных
        /// @param norm нормализовывать ли данные
        /// @param stride шаг
        /// @param pointer точка
        void setAttrib(GLuint index, GLuint count, GLenum type, GLenum norm, GLsizei stride, GLsizei pointer) {
            if (!id) { 
                std::cout << "ERR: VAO is not created;" << std::endl; 
                return; 
            }

            glVertexAttribPointer(index, count, type, norm, stride, (void*)pointer);
        }

        void bindVBO(shm::SVBO& vbo) {
            if (!id) { 
                std::cout << "ERR: VAO is not created;" << std::endl; 
                return; 
            }

            glBindBuffer(GL_VERTEX_ARRAY, vbo.getId());
        }

        void enableAttrib(GLuint index) {
            if (!id) { 
                std::cout << "ERR: VAO is not created;" << std::endl; 
                return; 
            }

            glEnableVertexAttribArray(index);
        }

        void disableAttrib(GLuint index) {
            if (!id) { 
                std::cout << "ERR: VAO is not created;" << std::endl; 
                return; 
            }

            glDisableVertexAttribArray(index);
        }

        void destroy() {
            glDeleteVertexArrays(1, &id);
            id = 0;
        }


        const uint32_t& getId() {
            return id;
        }
    };
}



#endif
