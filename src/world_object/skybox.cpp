#include "skybox.h"
#include "stb_image.h"
using namespace std;

float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

namespace curiosity {
    namespace graphics {

    shared_ptr<Skybox> Skybox::create(vector<string> &cubemapPaths) {
        return shared_ptr<Skybox>(new Skybox(cubemapPaths));
    }

    Skybox::Skybox(std::vector<std::string> &cubemapPaths)
        : DrawableObject(Vec3(0.0f, 0.0f, 0.0f)) {
        glGenTextures(1, &cubeTextureID);
        loadCubemaps(cubemapPaths);
        genVAOandVBO();
    }

    void Skybox::draw(Program &program) {
        program.use();
        glDepthMask(GL_FALSE);

        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureID);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDepthMask(GL_TRUE);

        glBindVertexArray(0);

        glBindBuffer(GL_VERTEX_ARRAY, 0);
        glActiveTexture(GL_TEXTURE0);
    }

    Skybox::~Skybox() {
        glDeleteTextures(1, &cubeTextureID);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void Skybox::loadCubemaps(std::vector<string> &cubemapPaths) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureID);
        int width, height, nrChannels;
        for (unsigned int i = 0; i < cubemapPaths.size(); i++) {
            unsigned char *data = stbi_load(cubemapPaths[i].c_str(), &width,
                                            &height, &nrChannels, 0);
            if (data) {
                GLuint format = getFormat(nrChannels);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format,
                             width, height, 0, format, GL_UNSIGNED_BYTE, data);
            } else {
                std::cout << "cubeMap load failed: " << cubemapPaths[i] << std::endl;
            }
            stbi_image_free(data);
        }
        initSet();
    }

    GLuint Skybox::getFormat(unsigned int channels) {
        if (channels == 1) {
            return GL_RED;
        } else if (channels == 3) {
            return GL_RGB;
        } else if (channels == 4) {
            return GL_RGBA;
        }
        return 0;
    }

    void Skybox::initSet() {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void Skybox::genVAOandVBO() {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, skyboxVertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    }

    }
}
