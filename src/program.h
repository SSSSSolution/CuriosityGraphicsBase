#ifndef GRAPHICS_PROGRAM_H
#define GRAPHICS_PROGRAM_H
#include "graphicsglobal.h"
#include "shader.h"
#include "transmat4.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include <vector>
#include <string>

namespace curiosity {
    namespace graphics {

    class LightSource;
    class Scene;
    /* 对应openGL的program对象 */
    class Program {
    public:
        Program();
        ~Program();

        // 链接着色器
        void linkShaders(std::vector<Shader> &shaders);
        // openGL使用这个程序
        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setTransMat4(const std::string &name, const TransMat4 &mat4);
        void setVec3(const std::string &name, Vec3 &vec3);
        void setVector2f(const std::string &name, const Vec2 &vec2);
        void setVector4f(const std::string &name, const Vec4 &vec4);
        void set1fv(const std::string &name, GLuint size, const GLfloat *data);
        void set2fv(const std::string &name, GLuint size, const GLfloat *data);
        void set1iv(const std::string &name, GLuint size, const GLint *data);
        void set3f(const std::string &name, float x, float y, float z);

    public:
        GLuint id;
        Scene *scene;
    };

    }
}

#endif
