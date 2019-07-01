#ifndef GRAPHICS_GRAVITY_H
#define GRAPHICS_GRAVITY_H

#include "observer.h"

namespace curiosity {
    namespace graphics {

    class Gravity : public Subject {
    public:
        Gravity (float g = 9.8f) : g(g), deltaTime(0.0f) {}

        virtual std::string getSubjectState() { return std::string("Gravity"); }

        void setG(float v) { g = v; }
        float getG() { return g; }

        void setDeltaTime(float delta) { deltaTime = delta; }
        float getDeltaTime() { return deltaTime; }

    private:
        float g;
        float deltaTime;
    };

    }
}

#endif
