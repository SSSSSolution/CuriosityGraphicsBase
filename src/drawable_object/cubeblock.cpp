#include "cubeblock.h"

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
        glGenVertexArrays(1, &VAO_);
        glBindVertexArray(VAO_);

        glEnableVertexArrayAttrib(0);
        glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, GL_FALSE,
                              sizeof()
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
        unsigned int * target = (unsigned int *)(accessCube(x, y, z) + 2*sizeof(bool));
        *target = textureID;
    }

    unsigned int CubeBlock::getTextureID(int x, int y, int z) {
        return *((unsigned int *)(accessCube(x, y, z) + 2*sizeof(bool)));
    }

    void CubeBlock::draw(Program &program) {
        program.use();
        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void *CubeBlock::accessCube(int x, int y, int z) {
        return cubeBuff_ + (x + y * XSIZE + z * XSIZE * YSIZE) * DATA_SIZE;
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
        bool *target = (bool *)(accessCube(x, y, z) + sizeof(bool));
        *target = b;
    }

    bool CubeBlock::isSurface(int x, int y, int z) {
        return *((bool *)accessCube(x, y, z) + sizeof(bool));
    }

    }
}
















