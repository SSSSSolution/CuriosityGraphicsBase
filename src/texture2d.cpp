#include "texture2d.h"

namespace curiosity {
    namespace graphics {

    Texture2D::Texture2D()
        :width(0), height(0), internalFormat(GL_RGB),
         imageFormat(GL_RGB), wrap_s(GL_REPEAT),
         wrap_t(GL_REPEAT), filter_min(GL_LINEAR),
         filter_max(GL_LINEAR)
    {
        glGenTextures(1, &id);
    }

    void Texture2D::generate(GLuint w, GLuint h, unsigned char *data) {
        width = w;
        height = h;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0,
                     imageFormat, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::bind() const {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    }
}
