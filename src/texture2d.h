#ifndef GRAPHICS_TEXTURE2D_H
#define GRAPHICS_TEXTURE2D_H
#include "graphicsglobal.h"

namespace curiosity {
    namespace graphics {

    class Texture2D {
    public:
        Texture2D();
        void generate(GLuint width, GLuint height, unsigned char *data);
        void bind() const;

    public:
        GLuint id;
        GLuint width, height;
        GLuint internalFormat;
        GLuint imageFormat;
        GLuint wrap_s;
        GLuint wrap_t;
        GLuint filter_min;
        GLuint filter_max;
    };

    }
}

#endif
