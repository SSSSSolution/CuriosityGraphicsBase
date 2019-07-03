#include "drawable_object/ballobject.h"
#include "geometry/sphere.h"
#include "gravity.h"
#include <assert.h>
#include <vector>
using namespace std;

namespace curiosity {
    namespace graphics {

    BallObject::BallObject(const Vec3 &position, const Vec3 &scaleFactor, Program *program)
        : WorldBaseObject(position, scaleFactor, program) {
        // 获得球体的定点坐标
        vector<float> vert = Sphere::genVertexs(5, 5);
        float *vertices = (float *)malloc(vert.size() * sizeof(float));
        int index = 0;
        for (auto f : vert) {
            vertices[index++] = f;
        }
        vertCount = (index)/3;
        //
        program->use();
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float *)*vertCount * 3,
                     vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        free(vertices);
    }

    BallObject::~BallObject() {
    }

    void BallObject::draw() {
        program->use();
        WorldBaseObject::setModelMatrix();

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_VERTEX_ARRAY, vbo);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertCount);

        glBindVertexArray(0);
        glBindBuffer(GL_VERTEX_ARRAY, 0);
    }

    void BallObject::update(Subject *subject) {
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
