#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H
#include "graphicsglobal.h"
#include "vec3.h"
#include "transmat4.h"

namespace curiosity {
    namespace graphics {

    class FPSCamera {
    public:
        FPSCamera(Vec3 position = Vec3(0.0f, 0.0f, 0.0f),
                  Vec3 worldUp = Vec3(0.0f, 1.0f, 0.0f),
                  float pitch = 0.0f, float yaw = -90.0f);

        TransMat4 getViewTransMat();

        void updateCameraVectors();

        enum MoveDirection {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };
        void processKeyboard(MoveDirection direction);
        void processMouseMove(float xOffset, float yOffset);

        Vec3 getFront();

    public:
        Vec3 position_; // 位置
        Vec3 worldUp_;  // 世界坐标系的y轴正方向
        float pitch_; // 俯仰角
        float yaw_;   // 偏航角
        float moveSpeed_; //　调节移动速度
        float mouseSensitivity_; // 调节视角转动速度

    private:
        Vec3 front_;    // 朝向
        Vec3 up_;       // 上方向
        Vec3 right_;    // 右方向
    };

    }
}

#endif
