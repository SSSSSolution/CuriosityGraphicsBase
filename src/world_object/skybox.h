#ifndef GRAPHICS_SKYBOX_H
#define GRAPHICS_SKYBOX_H
#include <memory>
#include <vector>
#include <string>
#include "graphicsglobal.h"
#include "drawableobject.h"

namespace curiosity {
    namespace graphics {

    class Skybox : public DrawableObject {
    public:
        static std::shared_ptr<Skybox> create(std::vector<std::string> &cubemapPaths);
        virtual void draw(Program &program);
        ~Skybox();

    private:
        Skybox(std::vector<std::string> &cubemapPaths);
        void loadCubemaps(std::vector<std::string> &cubemapPaths);
        GLuint getFormat(unsigned int channels);
        void initSet();
        void genVAOandVBO();

    private:
        GLuint cubeTextureID;
        GLuint VBO, VAO;
    };

    }
}

#endif
