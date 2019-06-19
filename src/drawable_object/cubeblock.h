#ifndef GRAPHICS_CUBEBLOCK_H
#define GRAPHICS_CUBEBLOCK_H
#include "graphicsglobal.h"
#include "vec3.h"
#include "model.h"
#include "drawableobject.h"
#include "program.h"
#include <map>
#define BLOCK_SIZE  (1<<22) // 4M
#define XSIZE       (128)
#define YSIZE       (128)
#define ZSIZE       (32)
#define DATA_SIZE   (8)

namespace curiosity {
    namespace graphics {
    class CubeBlock : public DrawableObject {
    public:
        CubeBlock(Vec3 position = Vec3(0.0f, 0.0f, 0.0f));
        ~CubeBlock();

        struct CubeInfo {
            CubeInfo(const Vec3 &position)
                : position_(position) {
            }
            Vec3 position_; // 方块的x, y, z
        };
        void init();
        void clear();
        void setExist(int x, int y, int z, bool b);
        bool isExist(int x, int y ,int z);
        void setTextureID(int x, int y, int z, unsigned int textureID);
        unsigned int getTextureID(int x, int y, int z);

        virtual void draw(Program &program);

    private:
        /* 方块局部坐标
         * x:[0, 127], y:[0,127], z:[0, 32]
         */
        void *accessCube(int x, int y, int z);
        /* 更新是否是表面的数据, 复杂度 O(N)
         */
        void initSurface();
        void setSurface(int x, int y, int z, bool b);
        bool isSurface(int x, int y, int z);

    private:
        /* 存放连续的方块信息，每个方块信息包含
         *  1.是否存在(bool)
         *  2.是否是表面（bool)
         *  3.纹理编号(unsigned int)
         * 现在为每个方块分配8个字节，共有128*128*32个方块
         */
        void *cubeBuff_;
        GLuint VAO_, VBO_, positionBuffer_;
        std::map<unsigned int, CubeInfo *> drawCubes;
    };
    }
}

#endif
