#include "vao.h"

namespace curiosity {
    namespace graphics {

    VAO::VAO() {
        glGenVertexArrays(1, &vao);
    }

    void VAO::bindVertexArray()

    }
}
