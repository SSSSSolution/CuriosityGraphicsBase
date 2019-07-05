#ifndef GRAPHCIS_SCENE_V1_H
#define GRAPHCIS_SCENE_V1_H
#include "scene_managing/scene.h"
#include "transmat4.h"
namespace curiosity {
    namespace graphics {

    class SceneV1 : public Scene{
    public:
        SceneV1(SceneFactory *factory);
        ~SceneV1();

        void setMat(const TransMat4 projectMat, const TransMat4 viewMat);
        void concreatProcess(WorldBaseObject *obj);

    private:
        TransMat4 projectMat;
        TransMat4 viewMat;
    };

    }
}


#endif
