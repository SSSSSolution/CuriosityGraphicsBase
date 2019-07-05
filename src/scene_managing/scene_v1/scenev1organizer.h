#ifndef GRAPHICS_SCENE_ORGANIZER_H
#define GRAPHICS_SCENE_ORGANIZER_H

#include "scene_managing/scene.h"
#include "scene_managing/scene_v1/scenev1Tree.h"

namespace curiosity {
    namespace graphics {

    class SceneV1Organizer : public SceneOrganizer {
    public:
        SceneV1Organizer() {}

        virtual void addObject(WorldBaseObject *obj);
        virtual void removeObject(WorldBaseObject *obj);

    private:
        SceneV1Tree ocTree;
    };

    }
}

#endif
