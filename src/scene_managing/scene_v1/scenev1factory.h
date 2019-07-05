#ifndef GRAPHICS_SCENEV1_FACTORY_H
#define GRAPHICS_SCENEV1_FACTORY_H

#include "scene_managing/scene.h"

namespace curiosity {
    namespace graphics {

    class SceneV1Factory : public SceneFactory {
    public:
        virtual SceneOrganizer *createSceneOrganizer();
    };

    }
}

#endif
