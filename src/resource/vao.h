#ifndef GRAPHICS_VAO_H
#define GRAPHICS_VAP_H

#include "graphicsglobal.h"

namespace curiosity {
    namespace graphics {

    class VAO {
    public:
        VAO();
        ~VAO();

        GLuint getVAO() const { return vao; }
        void bindVertexArray();

    private:
        // 顶点数据
        float *vertices;
        GLuint vao;
    };

    }
}

#endif
