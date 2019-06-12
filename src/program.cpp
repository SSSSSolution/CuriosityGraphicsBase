#include "program.h"

namespace curiosity {
    namespace graphics {

    Program::Program()
    {
        programID_ = glCreateProgram();
    }

    Program::~Program()
    {
        glDeleteProgram(programID_);
    }

    void Program::linkShaders(Shader *shaders, int size)
    {
        int success;
        char infoLog[512];

        for (int i = 0; i < size; ++i) {
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

    }
}
