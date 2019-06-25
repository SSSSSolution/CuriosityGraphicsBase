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
            std::string path = shaderDir() + filePath_;
            std::ifstream shaderFile(path.c_str());
            if (!shaderFile) {
                std::cerr << "can't open shader file: " << path << std::endl;
                return;
            }
            srcStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderSrc = srcStream.str();
            // 编译源码
            shader = glCreateShader(type_);
            const char * shaderCode = shaderSrc.c_str();
            glShaderSource(shader, 1, &shaderCode, NULL);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cout << shader << ": shader compile failed: "
                          << infoLog << std::endl;
            }
        }

        Shader::~Shader()
        {

        }
    }
}
