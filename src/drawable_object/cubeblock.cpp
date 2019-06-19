#include "cubeblock.h"

using namespace std;
static float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

     -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,

     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

     -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f, -0.5f,

     -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
};

namespace curiosity {
    namespace graphics {
    CubeBlock::CubeBlock(const Vec3 position)
        : DrawableObject(position),
          cubeBuff_(NULL) {

    }

    void CubeBlock::init() {
        cubeBuff_ = (void *)malloc(BLOCK_SIZE);
        for (int x = 0; x < XSIZE; x++) {
            for (int y = 0; y < YSIZE; y++) {
                for (int z = 0; z < ZSIZE; z++) {
                    setExist(x, y, z, true);
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

        int i = 0;
        float *positionBuffer = (float *)malloc(drawCubes.size() * 3 * sizeof(float));
        map<unsigned int, CubeInfo *>::iterator iter;
        for (iter = drawCubes.begin(); iter!=drawCubes.end(); ++iter) {
            positionBuffer[i++] = (iter->second)->position_.x_;
            positionBuffer[i++] = (iter->second)->position_.y_;
            positionBuffer[i++] = (iter->second)->position_.z_;
        }
        glGenBuffers(1, &VBO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices),
                     cubeVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &positionBuffer_);
        glBindBuffer(GL_ARRAY_BUFFER, positionBuffer_);
        glBufferData(GL_ARRAY_BUFFER, drawCubes.size() * 3 * sizeof(float),
                     positionBuffer, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
        glVertexAttribDivisor(1, 1);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, drawCubes.size());
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
        return (bool*)cubeBuff_ + (x + y * XSIZE + z * XSIZE * YSIZE) * DATA_SIZE;
    }

    void CubeBlock::initSurface() {
        if (!cubeBuff_)
            return;
        for (int x = 0; x < XSIZE; x++) {
            for (int y = 0; y < YSIZE; y++) {
                for (int z = 0; z < ZSIZE; z++) {
                    if (x == 0 || y == 0 || z == 0 ||
                        x == XSIZE || y == YSIZE || z == ZSIZE) {
                        setSurface(x, y, z, true);
                    } else if (isExist(x-1, y, z) || isExist(x+1, y, z) ||
                               isExist(x, y-1, z) || isExist(x, y+1, z) ||
                               isExist(x, y, z-1) || isExist(x, y, z+1)) {
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
















