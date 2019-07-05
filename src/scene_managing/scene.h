#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H
#include "worldbaseobject.h"
#include "transmat4.h"

namespace curiosity {
    namespace graphics {
    class SceneOrganizer;
    class SceneFactory;

    class Scene {
    public:
        Scene(SceneFactory *factory);
        virtual ~Scene() {}

        void addObject(WorldBaseObject *obj);
        void removeObject(WorldBaseObject *obj);
        void exec();

    protected:
        SceneFactory *factory;
        SceneOrganizer *sceneOrganizer;
    };

    class SceneOrganizer {
    public:
        SceneOrganizer() {}
        virtual ~SceneOrganizer() {}

        virtual void addObject(WorldBaseObject *obj) = 0;
        virtual void removeObject(WorldBaseObject *obj) = 0;
        virtual void exec() = 0;
    };

    class SceneFactory {
    public:
        SceneFactory() {}
        virtual ~SceneFactory() {}

        virtual SceneOrganizer *createSceneOrganizer() = 0;
    };

    }
}

#endif
