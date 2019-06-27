#include "graphicsglobal.h"
#include <stdlib.h>
using namespace std;

namespace curiosity {
    namespace graphics {

    string rootDir() {
        return string(getenv("PROJECT_ROOT"));
    }

    string textureDir() {
        return (rootDir() + "/texture/");
    }

    string skyboxDir() {
        return (textureDir() + "/skybox/");
    }

    string shaderDir() {
        return (rootDir() + "/shader/");
    }

    string modelDir() {
        return (rootDir() + "/model/");
    }

    string fontDir() {
        return (rootDir() + "/font/");
    }

    float clamp(float value, float minValue, float maxValue) {
        return max(minValue, min(maxValue, value));
    }

    Vec2 clamp(const Vec2 &value, const Vec2 &min, const Vec2 &max) {
        return Vec2(clamp(value.x_, min.x_, max.x_),
                    clamp(value.y_, min.y_, max.y_));
    }

    float length(const Vec2 &vec2) {
        return sqrt(vec2.x_ * vec2.x_ + vec2.y_ * vec2.y_);
    }

    }
}
