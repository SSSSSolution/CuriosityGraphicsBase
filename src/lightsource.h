#ifndef GRAPHICS_LIGHTSOURCE_H
#define GRAPHICS_LIGHTSOURCE_H
#include "graphicsglobal.h"
#include "vec3.h"
#include "program.h"

#define MAX_DIR_LIGHT_NUM       (8)
#define MAX_POINT_LIGHT_NUM     (64)
#define MAX_SPOT_LIGHT_NUM      (8)

namespace curiosity {
    namespace graphics {

    class LightSource {
    public:
        LightSource(Vec3 diffuse, Vec3 ambient, Vec3 specular);

        virtual void install(Program &program) = 0;

    public:
        Vec3 diffuse_;
        Vec3 ambient_;
        Vec3 specular_;
    };

    class DirLight : public LightSource {
    public:
        DirLight(Vec3 direction = Vec3(0.0f, 0.0f, -1.0f),
                 Vec3 diffuse = Vec3(1.0f, 1.0f, 1.0f),
                 Vec3 ambient = Vec3(0.2f, 0.2f, 0.2f),
                 Vec3 specular = Vec3(0.5f, 0.5f, 0.5f));

        virtual void install(Program &program);

    public:
        Vec3 direction_;
    };

    class PointLight : public LightSource {
    public:
        PointLight(Vec3 position = Vec3(0.0f, 14.0f, 5.0f),
                   Vec3 diffuse = Vec3(1.0f, 1.0f, 1.0f),
                   Vec3 ambient = Vec3(0.2f, 0.2f, 0.2f),
                   Vec3 specular = Vec3(0.5f, 0.5f, 0.5f),
                   float constant = 1.0f,
                   float linear = 0.007f,
                   float quadratic = 0.0002f);

        virtual void install(Program &program);

    public:
        Vec3 position_;
        float constant_;
        float linear_;
        float quadratic_;
    };

    class SpotLight : public LightSource {
    public:
        SpotLight(Vec3 position = Vec3(0.0f, 14.0f, 5.0f),
                  Vec3 direction = Vec3(0.0f, 0.0f, -1.0f),
                  Vec3 diffuse = Vec3(1.0f, 1.0f, 1.0f),
                  Vec3 ambient = Vec3(0.2f, 0.2f, 0.2f),
                  Vec3 specular = Vec3(0.5f, 0.5f, 0.5f),
                  float cutOff = 12.5f,
                  float outCutOff = 17.5f);

        virtual void install(Program &program);

    public:
        Vec3 position_;
        Vec3 direction_;
        float cutOff_;
        float outCutOff_;
    };

    }
}

#endif
























