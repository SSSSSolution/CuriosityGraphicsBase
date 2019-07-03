#ifndef GRAPHICS_GLOBAL_H
#define GRAPHICS_GLOBAL_H

#include <cmath>
#include <utility>
#include <string>
#include <iostream>
//#include "glad/glad.h"
#include "sb7_include/sb7.h"
#include "GLFW/glfw3.h"
#include "vec2.h"

#define PI                      (3.14159f)
#define RADIANS(r)              (r*PI/180.0f)

#define FLOAT_EPS               (1e-6)
#define IS_FLOAT_ZERO(f)        (fabs(f) <= FLOAT_EPS)
#define IS_FLOAT_EQUAL(a, b)    IS_FLOAT_ZERO(a-b)

namespace curiosity {
    namespace graphics {

    std::string rootDir();

    std::string textureDir();

    std::string skyboxDir();

    std::string shaderDir();

    std::string modelDir();

    std::string fontDir();

    // math extern
    float clamp(float value, float min, float max);

    Vec2 clamp(const Vec2 &value, const Vec2 &min, const Vec2 &max);

    float length(const Vec2 &vec2);

    }
}

#endif
