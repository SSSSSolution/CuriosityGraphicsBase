#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace curiosity {
    namespace graphics {
        Shader::Shader(const char *filePath, GLenum type)
            : filePath_(filePath), type_(type)
        {

        }

        void Shader::compile() {
            std::string shaderSrc;
            std::stringstream srcStream;
            int success;
            char infoLog[512];

            if (!filePath_)
                return;

            // 加载源码
            std::ifstream shaderFile(filePath_);
            if (!shaderFile) {
                std::cerr << "can't open shader file: " << filePath_ << std::endl;
                return;
            }
            srcStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderSrc = srcStream.str();
            // 编译源码
            shader_ = glCreateShader(type_);
            const char * shaderCode = shaderSrc.c_str();
            glShaderSource(shader_, 1, &shaderCode, NULL);
            glCompileShader(shader_);
            glGetShaderiv(shader_, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader_, 512, NULL, infoLog);
                std::cout << shader_ << ": shader compile failed: "
                          << infoLog << std::endl;
            }
        }

        Shader::~Shader()
        {

        }
    }
}
