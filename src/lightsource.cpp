#include "lightsource.h"
#include <string>
using namespace std;

namespace curiosity {
    namespace graphics {

    LightSource::LightSource(Vec3 diffuse, Vec3 ambient, Vec3 specular)
        : diffuse_(diffuse), ambient_(ambient), specular_(specular) {
    }

    DirLight::DirLight(Vec3 direction, Vec3 diffuse, Vec3 ambient, Vec3 specular)
        : LightSource(diffuse, ambient, specular), direction_(direction) {
    }

    void DirLight::install(Program &program) {
        program.dirLightCount++;
        if (program.dirLightCount > MAX_DIR_LIGHT_NUM) {
            program.dirLightCount--;
            return;
        }
        program.use();
        string num = to_string(program.dirLightCount-1);
        program.setVec3(string("dirLights[")+num+"].direction_", direction_);
        program.setVec3(string("dirLights[")+num+"].diffuse_", diffuse_);
        program.setVec3(string("dirLights[")+num+"].ambient_", ambient_);
        program.setVec3(string("dirLights[")+num+"].specular_", specular_);
    }

    PointLight::PointLight(Vec3 position, Vec3 diffuse, Vec3 ambient, Vec3 specular,
                           float constant, float linear, float quadratic)
        : LightSource(diffuse, ambient, specular), position_(position),
          constant_(constant), linear_(linear), quadratic_(quadratic) {
    }

    void PointLight::install(Program &program) {
        program.pointLightCount++;
        if (program.pointLightCount > MAX_POINT_LIGHT_NUM) {
            program.pointLightCount--;
            return;
        }
        program.use();
        string num = to_string(program.pointLightCount-1);
        program.setVec3(string("pointLights[")+num+"].position_", position_);
        program.setFloat(string("pointLights[")+num+"].constant_", constant_);
        program.setFloat(string("pointLights[")+num+"].linear_", linear_);
        program.setFloat(string("pointLights[")+num+"].quadratic_", quadratic_);
        program.setVec3(string("pointLights[")+num+"].diffuse_", diffuse_);
        program.setVec3(string("pointLights[")+num+"].ambient_", ambient_);
        program.setVec3(string("pointLights[")+num+"].specular_", specular_);
    }

    SpotLight::SpotLight(Vec3 position, Vec3 direction, Vec3 diffuse, Vec3 ambient,
                         Vec3 specular, float cutOff, float outCutOff)
        : LightSource(diffuse, ambient, specular), direction_(direction),
          position_(position), cutOff_(cutOff), outCutOff_(outCutOff) {
    }

    void SpotLight::install(Program &program) {
        program.spotLightCount++;
        if (program.spotLightCount > MAX_SPOT_LIGHT_NUM) {
            program.spotLightCount--;
            return;
        }
        program.use();
        string num = to_string(program.spotLightCount-1);
        program.setVec3(string("spotLights[")+num+"].position_", position_);
        program.setVec3(string("spotLights[")+num+"].direction_", direction_);
        program.setFloat(string("spotLights[")+num+"].cutOff_", std::cos(RADIANS(cutOff_)));
        program.setFloat(string("spotLights[")+num+"].outCutOff_", std::cos(RADIANS(outCutOff_)));
        program.setVec3(string("spotLights[")+num+"].diffuse_", diffuse_);
        program.setVec3(string("spotLights[")+num+"].ambient_", ambient_);
        program.setVec3(string("spotLights[")+num+"].specular_", specular_);
    }

    }
}
