#include <iostream>
#include "lightsource.h"
#include "program.h"
#include "scene.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    Program::Program()
        : scene(NULL)
    {
        std::cout << "Program" << std::endl;

    }

    Program::~Program()
    {
//        glDeleteProgram(id);
    }

    void Program::linkShaders(vector<Shader> &shaders)
    {
        id = glCreateProgram();
        std::cout << "program id: " << id << std::endl;

        int success;
        char infoLog[512];

        for (int i = 0; i < shaders.size(); ++i) {
            glAttachShader(id, shaders[i].getShader());
        }
        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "Program link error: " << infoLog << std::endl;
        }

        for (int i = 0; i < shaders.size(); ++i) {
            glDeleteShader(shaders[i].shader);
        }
    }

    void Program::use()
    {
        glUseProgram(id);
    }

    void Program::setBool(const string &name, bool value) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }

    void Program::setInt(const string &name, int value) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void Program::setFloat(const string &name, float value) const {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void Program::setTransMat4(const string &name, TransMat4 &mat4) {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, mat4.data_);
    }

    void Program::setVec3(const string &name, Vec3 &vec3) {
        glUniform3f(glGetUniformLocation(id, name.c_str()), vec3.x_, vec3.y_, vec3.z_);
    }

    void Program::setVector2f(const string &name, const Vec2 &vec2) {
        glUniform2f(glGetUniformLocation(id, name.c_str()), vec2.x_, vec2.y_);
    }

    void Program::setVector4f(const string &name, const Vec4 &vec4) {
        glUniform4f(glGetUniformLocation(id, name.c_str()), vec4.x, vec4.y, vec4.z, vec4.w);
    }

    void Program::set1fv(const string &name, GLuint size, const GLfloat *data) {
        glUniform1fv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void Program::set2fv(const string &name, GLuint size, const GLfloat *data) {
        glUniform2fv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void Program::set1iv(const string &name, GLuint size, const GLint *data) {
        glUniform1iv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void Program::set3f(const string &name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
    }

    }
}































