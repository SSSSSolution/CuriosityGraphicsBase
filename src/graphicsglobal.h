#ifndef GRAPHICS_GLOBAL_H
#define GRAPHICS_GLOBAL_H

#include <cmath>
#include <string>
#include <iostream>
//#include "glad/glad.h"
#include "sb7_include/sb7.h"
#include "GLFW/glfw3.h"

#define RADIANS(r)              (r*3.14159f/180.0f)

namespace curiosity {
    namespace graphics {

    std::string rootDir();

    std::string textureDir();

    std::string skyboxDir();

    std::string shaderDir();

    std::string modelDir();

    }
}

#endif
