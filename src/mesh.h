#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H
#include <string>
#include <vector>
#include "graphicsglobal.h"
#include "vec3.h"
#include "vec2.h"
#include "program.h"

namespace curiosity {
    namespace graphics {

    // openGL中的顶点
    struct Vertex {
        Vec3 position_;     // 位置坐标
        Vec3 normal_;       // 定点法向量
        Vec2 texCoords_;    // 纹理坐标
        Vec3 tangent;       //
        Vec3 bitTangent;    //
    };

    // openGL中的纹理
    struct Texture {
        GLuint id_;
        std::string type_;
        std::string path_;
    };

    // 网格，openGL draw 一次的单元
    class Mesh {
    public:
        Mesh(std::vector<Vertex> vertices,
             std::vector<GLuint> indices,
             std::vector<Texture> texutres);
        void draw(Program &program);

    private:
        void setupMesh();

    private:
        std::vector<Vertex> vertices_;
        std::vector<GLuint> indices_;
        std::vector<Texture> textures_;
        GLuint VAO_, VBO_, EBO_;
    };

    }
}












#endif
