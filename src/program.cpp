#include <iostream>
#include "lightsource.h"
#include "program.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    Program::Program()
    {
        std::cout << "Program" << std::endl;

    }

    Program::~Program()
    {
        glDeleteProgram(programID_);
    }

    void Program::linkShaders(vector<Shader> &shaders)
    {
        programID_ = glCreateProgram();

        int success;
        char infoLog[512];

        for (int i = 0; i < shaders.size(); ++i) {
            glAttachShader(programID_, shaders[i].getShader());
        }
        glLinkProgram(programID_);
        glGetProgramiv(programID_, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programID_, 512, NULL, infoLog);
            std::cout << "Program link error: " << infoLog << std::endl;
        }
    }

    void Program::use()
    {
        glUseProgram(programID_);
    }

    void Program::addLightSource(LightSource *ls) {
        lightSources.push_back(ls);
    }

    void Program::installLights() {
        dirLightCount = 0;
        pointLightCount = 0;
        spotLightCount = 0;
        for (int i = 0; i < lightSources.size(); i++) {
            lightSources[i]->install(*this);
        }
        setInt("dirLightCount", dirLightCount);
        setInt("pointLightCount", pointLightCount);
        setInt("spotLightCount", spotLightCount);
    }

    void Program::setBool(const string &name, bool value) const {
        glUniform1i(glGetUniformLocation(programID_, name.c_str()), (int)value);
    }

    void Program::setInt(const string &name, int value) const {
        glUniform1i(glGetUniformLocation(programID_, name.c_str()), value);
    }

    void Program::setFloat(const string &name, float value) const {
        glUniform1f(glGetUniformLocation(programID_, name.c_str()), value);
    }

    void Program::setTransMat4(const string &name, TransMat4 &mat4) {
        glUniformMatrix4fv(glGetUniformLocation(programID_, name.c_str()), 1, GL_FALSE, mat4.data_);
    }

    void Program::setVec3(const string &name, Vec3 &vec3) {
        glUniform3f(glGetUniformLocation(programID_, name.c_str()), vec3.x_, vec3.y_, vec3.z_);
    }

    }
}









