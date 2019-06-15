#include "mesh.h"
#include <cstddef>
using namespace std;

namespace curiosity {
    namespace graphics {

    Mesh::Mesh(std::vector<Vertex> vertices,
               std::vector<GLuint> indices,
               std::vector<Texture> textures)
        : vertices_(vertices),
          indices_(indices),
          textures_(textures) {
        std::cout << "mesh: " << vertices_.size() << "," << indices_.size()
                  << "," << textures_.size() << std::endl;
        setupMesh();
    }

    void Mesh::draw(Program &program) {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int ambientNr = 1;
        unsigned int heightNr = 1;

        for (unsigned int i = 0; i < textures_.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            string number;
            string name = textures_[i].type_;
            if (name == "texture_diffuse") {
                number = std::to_string(diffuseNr++);
            } else if (name == "texture_specular") {
                number = std::to_string(specularNr++);
            } else if (name == "texture_ambient") {
                number = std::to_string(ambientNr++);
            } else if (name == "texture_normal") {
                number = std::to_string(heightNr++);
            }
            program.setInt((name+number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures_[i].id_);
        }
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }

    void Mesh::setupMesh() {
        //　缓冲区设置成顶点信息
        glGenBuffers(1, &VBO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex),
                     &vertices_[0], GL_STATIC_DRAW);

        // 创建对应这个网格的顶点对象，绑定属性
        glGenVertexArrays(1, &VAO_);
        glBindVertexArray(VAO_);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void *)(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void *)offsetof(Vertex, normal_));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void *)offsetof(Vertex, texCoords_));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void *)offsetof(Vertex, tangent));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void *)offsetof(Vertex, bitTangent));

        // 绑定EBO的属性, 目前只能画三角形
        glGenBuffers(1, &EBO_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint),
                     &indices_[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    }
}
