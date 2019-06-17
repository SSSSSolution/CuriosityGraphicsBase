#include <iostream>
#include "model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

namespace curiosity {
    namespace graphics {

    Model::Model(const char *path, bool gamma)
        : gammaCorrection_(gamma) {
        loadModel(path);
    }

    void Model::draw(Program &program) {
        for (unsigned int i = 0; i < meshes_.size(); i++) {
            meshes_[i].draw(program);
        }
    }

    void Model::loadModel(std::string path) {
        std::cout << "load model start" << std::endl;
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate
                                               | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
                || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory_ = path.substr(0, path.find_last_of('/'));
        std::cout << "processNode start" << std::endl;
        processNode(scene->mRootNode, scene);
        std::cout << "load model finished" << std::endl;
    }

    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes_.push_back(processMesh(mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;

            aiVector3D v3 = mesh->mVertices[i];
            vertex.position_ = Vec3(v3.x, v3.y, v3.z);
            v3 = mesh->mNormals[i];
            vertex.normal_ = Vec3(v3.x, v3.y, v3.z);
            if (mesh->mTextureCoords[0]) {
                v3 = mesh->mTextureCoords[0][i];
                vertex.texCoords_ = Vec2(v3.x, v3.y);
            } else {
                vertex.texCoords_ = Vec2(0.0f, 0.0f);
            }
//            if (mesh->mTangents) {
//                v3 = mesh->mTangents[i];
//                vertex.tangent = Vec3(v3.x, v3.y, v3.z);
//            }
//            if (mesh->mBitangents) {
//                v3 = mesh->mBitangents[i];
//                vertex.bitTangent = Vec3(v3.x, v3.y, v3.z);
//            }

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        // 网格的材质
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        vector<Texture> diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "material.texture_diffuse");
        textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());
        vector<Texture> specularMap = loadMaterialTextures(material, aiTextureType_SPECULAR, "material.texture_specular");
        textures.insert(textures.end(), specularMap.begin(), specularMap.end());
        vector<Texture> ambientMap = loadMaterialTextures(material, aiTextureType_AMBIENT, "material.texture_ambient");
        textures.insert(textures.end(), ambientMap.begin(), ambientMap.end());
        vector<Texture> normalMap = loadMaterialTextures(material, aiTextureType_HEIGHT, "material.texture_normal");
        textures.insert(textures.end(), normalMap.begin(), normalMap.end());

        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat,
                                                     aiTextureType type,
                                                     string typeName) {
        vector<Texture> textures;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded_.size(); j++ ) {
                if (std::strcmp(textures_loaded_[j].path_.data(),
                                str.C_Str()) == 0) {
                    textures.push_back(textures_loaded_[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip) {
                Texture texture;
                std::cout << str.C_Str() << std::endl;
                texture.id_ = textureFromFile(str.C_Str(), directory_);
                std::cout << "texture id : " << texture.id_ <<"," << type << std::endl;
                texture.type_ = typeName;
                texture.path_ = str.C_Str();
                textures.push_back(texture);
                textures_loaded_.push_back(texture);
            }
        }
        return textures;
    }


    GLuint Model::textureFromFile(const char *path,
                                  const std::string &directory,
                                  bool gamma) {
        string filename = string(path);
        filename = directory + '/' + filename;

        // 创建纹理
        GLuint textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height,
                                        &nrComponents, 0);
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
            std::cout << "texture fialed to load at path" << path << std::endl;
        }

        return textureID;
    }

    }
}
