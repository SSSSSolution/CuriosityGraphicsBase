#include "scene.h"
#include "lightsource.h"
#include "model.h"

namespace curiosity {
    namespace graphics {

    Scene::Scene() {
    }

    void Scene::draw(Program &program) {
        program.scene = this;
        program.use();
        installLights(program);
        for (int i = 0; i < models.size(); i++) {
            models[i]->draw(program);
        }
    }

    void Scene::addModel(Model *model) {
        models.push_back(model);
    }

    void Scene::addLightSource(LightSource *ls) {
        lightSources.push_back(ls);
    }

    void Scene::installLights(Program &program) {
        dirLightCount = 0;
        pointLightCount = 0;
        spotLightCount = 0;
        for (int i = 0; i < lightSources.size(); i++) {
            lightSources[i]->install(program);
        }
        program.setInt("dirLightCount", dirLightCount);
        program.setInt("pointLightCount", pointLightCount);
        program.setInt("spotLightCount", spotLightCount);
    }

    }
}
