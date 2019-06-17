#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H
#include "graphicsglobal.h"
#include "program.h"
#include <vector>

namespace curiosity {
    namespace graphics {

    class Model;
    class LightSource;
    class Scene {
    public:
        Scene();

        void draw(Program &program);
        void addLightSource(LightSource *ls);
        void addModel(Model *);

    private:
        void installLights(Program &program);

    public:
        std::vector<LightSource *> lightSources;
        std::vector<Model *> models;
        unsigned int dirLightCount;
        unsigned int pointLightCount;
        unsigned int spotLightCount;
    };

    }
}

#endif
