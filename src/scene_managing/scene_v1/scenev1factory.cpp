#include "scenev1factory.h"
#include "scene_managing/scene_v1/scenev1organizer.h"
namespace curiosity {
    namespace graphics {

    SceneOrganizer *SceneFactory::createSceneOrganizer() {
        return new SceneV1Organizer;
    }

    }
}
