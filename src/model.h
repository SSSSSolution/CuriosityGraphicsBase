#ifndef GRAPHICS_MODEL_H
#define GRAPHICS_MODEL_H
#include <iostream>
#include <vector>
#include "graphicsglobal.h"
#include "mesh.h"
#include "program.h"

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace curiosity {
    namespace graphics {

    class Model {
    public:
        Model(const char *path, bool gamma = false);
        void draw(Program &program);

    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        GLuint textureFromFile(const char *path, const std::string &directory, bool gamma = false);

    private:
        std::vector<Texture> textures_loaded_;
        std::vector<Mesh> meshes_;
        std::string directory_;
        bool gammaCorrection_;
    };

    }
}

#endif
