#include "cubeline.h"
#include "resourcemanager.h"
#include "gravity.h"
#include <assert.h>

namespace curiosity {
    namespace graphics {
    static float cubeVertices[] = {
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,

            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,

            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, 0.5f

    };

    CubeLine::CubeLine(const Vec3 &position, const Vec3 &scaleFactor, Program *program)
        : WorldBaseObject(position, scaleFactor, program) {
        program->use();
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24 * 3,
                     cubeVertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    CubeLine::~CubeLine() {

    }

    void CubeLine::draw() {
        program->use();
        WorldBaseObject::setModelMatrix();

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_VERTEX_ARRAY, vbo);

        glLineWidth(10);
        glDrawArrays(GL_LINES, 0, 24);

        glBindVertexArray(0);
        glBindBuffer(GL_VERTEX_ARRAY, 0);
    }
    }
}
