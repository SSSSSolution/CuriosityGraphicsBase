#include "cubeblock.h"
#include <iostream>

#include "stb_image.h"



using namespace std;
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

namespace curiosity {
    namespace graphics {
    CubeBlock::CubeBlock(const Vec3 position)
        : DrawableObject(position),
          cubeBuff_(NULL) {


    }

    void CubeBlock::init() {
        // 暂时先在这创建纹理
        glGenTextures(1, &textureID);
        int width, height, nrComponents;
        unsigned char *data = stbi_load("/home/huangwei/study/computer_graphics/learning_computer_graphics/src/media/container2.png",
                                        &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1) {
                format = GL_RED;
            } else if (nrComponents == 3) {
                format = GL_RGB;
            } else if (nrComponents == 4) {
                format = GL_RGBA;
            }

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                         0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        } else {
            std::cout << "texture fialed to load at path" << std::endl;
        }
        // 暂时先在这里创建顶点信息
        glGenBuffers(1, &VBO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*36*5,
                     cubeVertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO_);
        glBindVertexArray(VAO_);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));

        glGenBuffers(1, &positionBuffer_);
        glBindBuffer(GL_ARRAY_BUFFER, positionBuffer_);
        glBufferData(GL_ARRAY_BUFFER, XSIZE*YSIZE*ZSIZE * 3 *sizeof(float),  NULL, GL_DYNAMIC_DRAW);
        cubeBuff_ = (void *)malloc(BLOCK_SIZE);
        for (int x = 0; x < XSIZE; x++) {
            for (int y = 0; y < YSIZE; y++) {
                for (int z = 0; z < ZSIZE; z++) {
                    if ( y == 0)
                        setExist(x, y, z, true);
                    else
                        setExist(x, y, z, false);
//                    setExist(x, y, z, true);
                    setTextureID(x, y, z, 0);
                }
            }
        }
        initSurface();
        for (int x = 0; x < XSIZE; x++) {
            for (int y = 0; y < YSIZE; y++) {
                for (int z = 0; z < ZSIZE; z++) {
                    if (isSurface(x, y, z)) {
                        CubeInfo *ci = new CubeInfo(Vec3(x, y, z));
                        drawCubes[x + y * XSIZE + z * XSIZE * YSIZE] = ci;
                    }
                }
            }
        }
    }

    void CubeBlock::draw(Program &program) {
        program.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        program.setInt("blockTexture", 0);

        int i = 0;
        float *positionBuffer = (float *)malloc(drawCubes.size() * 3 * sizeof(float));
        map<unsigned int, CubeInfo *>::iterator iter;
        for (iter = drawCubes.begin(); iter!=drawCubes.end(); ++iter) {
            positionBuffer[i++] = (iter->second)->position_.x_;
            positionBuffer[i++] = (iter->second)->position_.y_;
            positionBuffer[i++] = (iter->second)->position_.z_;
        }

        glBindVertexArray(VAO_);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, positionBuffer_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 3*sizeof(float)*drawCubes.size(), positionBuffer);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);
        glVertexAttribDivisor(2, 1);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, drawCubes.size());
        free(positionBuffer);
    }

    void CubeBlock::clear() {
        if (cubeBuff_) {
            free(cubeBuff_);
            cubeBuff_ = NULL;
        }
    }

    void CubeBlock::setExist(int x, int y, int z, bool b) {
        bool *target = (bool *)accessCube(x, y, z);
        *target = b;
    }

    bool CubeBlock::isExist(int x, int y, int z) {
        return *((bool *)accessCube(x, y, z));
    }

    void CubeBlock::setTextureID(int x, int y, int z, unsigned int textureID) {
        unsigned int * target = (unsigned int *)((bool*)accessCube(x, y, z) + 2*sizeof(bool));
        *target = textureID;
    }

    unsigned int CubeBlock::getTextureID(int x, int y, int z) {
        return *((unsigned int *)((bool*)accessCube(x, y, z) + 2*sizeof(bool)));
    }

    void *CubeBlock::accessCube(int x, int y, int z) {
        return (char *)cubeBuff_ + (x + y * XSIZE + z * XSIZE * YSIZE) * DATA_SIZE;
    }

    void CubeBlock::initSurface() {
        if (!cubeBuff_)
            return;
        for (int x = 0; x < XSIZE; x++) {
            for (int y = 0; y < YSIZE; y++) {
                for (int z = 0; z < ZSIZE; z++) {
                    if (!isExist(x, y, z)) {
                        setSurface(x, y, z, false);
                    } else if (x == 0 || y == 0 || z == 0 ||
                        x == XSIZE-1 || y == YSIZE-1 || z == ZSIZE-1) {
                        setSurface(x, y, z, true);
                    } else if (!isExist(x-1, y, z) || !isExist(x+1, y, z) ||
                               !isExist(x, y-1, z) || !isExist(x, y+1, z) ||
                               !isExist(x, y, z-1) || !isExist(x, y, z+1)) {
                        setSurface(x, y, z, true);
                    } else {
                        setSurface(x, y, z, false);
                    }
                }
            }
        }
    }

    void CubeBlock::setSurface(int x, int y, int z, bool b) {
        bool *target = (bool *)((bool*)accessCube(x, y, z) + sizeof(bool));
        *target = b;
    }

    bool CubeBlock::isSurface(int x, int y, int z) {
        return *((bool *)accessCube(x, y, z) + sizeof(bool));
    }

    }
}
















