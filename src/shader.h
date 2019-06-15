#ifndef SHADER_H
#define SHADER_H
#include "graphicsglobal.h"

namespace curiosity {
    namespace graphics {

    /* 对应openGL的着色器对象　*/
    class Shader {
    public:
        Shader(const char *filePath, GLenum type);
        ~Shader();

        void compile();
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
