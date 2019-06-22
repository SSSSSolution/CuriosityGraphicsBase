#ifndef GRAPHICS_RESOURCE_MANAGER_H
#define GRAPHICS_RESOURCE_MANAGER_H
#include "graphicsglobal.h"
#include <map>
#include "texture2d.h"
#include "program.h"

namespace curiosity {
    namespace graphics {

    class ResourceManager {
    public:
        static std::map<std::string, Program> programs;
        static std::map<std::string, Texture2D> textures;

        static Program loadProgram(const GLchar *vShaderFile,
                                 const GLchar *fShaderFile,
                                 const GLchar *gShaderFile,
                                 std::string name);
        static Program getProgram(std::string name);
        static Texture2D loadTexture(const GLchar *file, GLboolean  alpha,
                                     std::string name);

        static Texture2D &getTexture2D(std::string name);

        static void clear();

    private:
        ResourceManager() {}
        static Program loadProgramFromFile(const GLchar *vShaderFile,
                                         const GLchar *fShaderFile,
                                         const GLchar *gShaderFile = NULL);
        static Texture2D loadTextureFromFile(const GLchar *file);
    };

    }
}

#endif
