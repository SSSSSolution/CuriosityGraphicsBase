#include "graphicsglobal.h"
#include <stdlib.h>
using namespace std;

namespace curiosity {
    namespace graphics {

    string rootDir() {
        return string(getenv("PROJECT_ROOT"));
    }

    string textureDir() {
        return (rootDir() + "/texture");
    }

    string skyboxDir() {
        return (textureDir() + "/skybox");
    }

    string shaderDir() {
        return (rootDir() + "/shader");
    }

    string modelDir() {
        return (rootDir() + "/model");
    }

    }
}
