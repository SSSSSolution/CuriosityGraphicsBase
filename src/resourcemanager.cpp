#include "resourcemanager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "stb_image.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    std::map<string, Texture2D> ResourceManager::textures;
    std::map<string, Program>    ResourceManager::programs;

    Program ResourceManager::loadProgram(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, string name) {
        programs[name] = loadProgramFromFile(vShaderFile, fShaderFile, gShaderFile);
        return programs[name];
    }

    Program ResourceManager::getProgram(string name) {
        return programs[name];
    }

    Texture2D ResourceManager::loadTexture(const GLchar *file, GLboolean alpha, string name) {
        textures[name] = loadTextureFromFile(file);
        return textures[name];
    }

    Texture2D ResourceManager::getTexture2D(string name) {
        return textures[name];
    }

    void ResourceManager::clear() {
        for (auto iter : programs)
            glDeleteProgram(iter.second.id);

        for (auto iter : textures)
            glDeleteTextures(1, &iter.second.id);
    }

    Program ResourceManager::loadProgramFromFile(const GLchar *vShaderPath, const GLchar *fShaderPath, const GLchar *gShaderPath) {
        vector<Shader> shaders;

        Shader vShader(vShaderPath, GL_VERTEX_SHADER);
        vShader.compile();
        shaders.push_back(vShader);

        Shader fShader(fShaderPath, GL_FRAGMENT_SHADER);
        fShader.compile();
        shaders.push_back(fShader);

        if (gShaderPath) {
            Shader gShader(gShaderPath, GL_GEOMETRY_SHADER);
            gShader.compile();
            shaders.push_back(gShader);
        }

        Program program;
        program.linkShaders(shaders);
        return program;
    }

    Texture2D ResourceManager::loadTextureFromFile(const GLchar *file) {
        Texture2D texture;
        int width, height, nrComponents;
        string filePath = textureDir() + "/" + file;
        unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1) {
                format = GL_RED;
            } else if (nrComponents == 3) {
                format = GL_RGB;
            } else if (nrComponents == 4) {
                format = GL_RGBA;
            }
            texture.imageFormat = format;
            texture.internalFormat = GL_RGBA;
            texture.generate(width, height, data);
            stbi_image_free(data);
        } else {
            cout << "texture failed to load: " << filePath << endl;
        }

        return texture;
    }

    }
}
