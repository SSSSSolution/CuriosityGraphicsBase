#include "cubeobject.h"
#include "resourcemanager.h"
#include "gravity.h"
#include <assert.h>

namespace curiosity {
    namespace graphics {
    static float cubeVertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
            // Left face
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
            // Right face
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
            // Top face
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
    };

    CubeObject::CubeObject(const Vec3 &position, const Vec3 &scaleFactor, Program *program)
        : WorldBaseObject(position, scaleFactor, program) {
        program->use();
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float *)*36 * 5,
                     cubeVertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    CubeObject::~CubeObject() {

    }

    void CubeObject::draw() {
        program->use();
        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        program->setInt("text", 0);
        WorldBaseObject::setModelMatrix();

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_VERTEX_ARRAY, vbo);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glBindBuffer(GL_VERTEX_ARRAY, 0);
    }

    void CubeObject::setTexture(std::string name) {
        texture = ResourceManager::getTexture2D(name);
    }

    void CubeObject::update(Subject *subject) {
        if (subject->getSubjectState() == "Gravity") {
            // 受重力影响
            Gravity *gravity = dynamic_cast<Gravity *>(subject);
            assert(gravity);
            float deltaTime = gravity->getDeltaTime();
            float g = gravity->getG();
            // y方向速度改变
            velocity.y_ -= deltaTime * g;
        }
    }
    }
}
