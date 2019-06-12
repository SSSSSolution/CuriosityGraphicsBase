#ifndef GRAPHICS_PROGRAM_H
#define GRAPHICS_PROGRAM_H
#include "graphicsglobal.h"
#include "shader.h"

namespace curiosity {
    namespace graphics {

    class Program {
    public:
        Program();
        ~Program() {
            glDeleteProgram(programID_);
        }

        void linkShaders(Shader *shaders, int size);
        void use();

    private:
        GLuint programID_;
    };

    }
}

#endif
