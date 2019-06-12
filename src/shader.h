#ifndef SHADER_H
#define SHADER_H
#include "graphicsglobal.h"

namespace curiosity {
    namespace graphics {

    class Shader {
    public:
        Shader(const char *filePath, GLenum type);
        ~Shader();

        GLenum getType() { return type_; }
        GLuint getShader() { return shader_; }

    private:
        const char *filePath_;
        GLenum type_;
        GLuint shader_;
    };

    }
}

#endif
