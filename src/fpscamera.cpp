#include "fpscamera.h"

namespace curiosity {
    namespace graphics {
        FPSCamera::FPSCamera(Vec3 position, Vec3 worldUp, float pitch, float yaw)
            : position_(position), worldUp_(worldUp), pitch_(pitch), yaw_(yaw) ,
              moveSpeed_(1.0f), mouseSensitivity_(0.1f) {
            updateCameraVectors();
        }

        void FPSCamera::updateCameraVectors() {
            Vec3 front;
            front.x_ = cos(RADIANS(yaw_)) * cos(RADIANS(pitch_));
            front.y_ = sin(RADIANS(pitch_));
            front.z_ = sin(RADIANS(yaw_)) * cos(RADIANS(pitch_));
            front_ = front.normalize();
            right_ = front_.cross(worldUp_);
            up_ = right_.cross(front_);
        }

        void FPSCamera::processKeyboard(MoveDirection direction) {
            switch (direction) {
            case FORWARD:
                position_ = position_ + front_ * moveSpeed_;
                break;
            case BACKWARD:
                position_ = position_ - front_ * moveSpeed_;
                break;
            case LEFT:
                position_ = position_ - right_ * moveSpeed_;
                break;
            case RIGHT:
                position_ = position_ + right_ * moveSpeed_;
                break;
            }
            updateCameraVectors();
        }

        void FPSCamera::processMouseMove(float xOffset, float yOffset)
        {
            xOffset *= mouseSensitivity_;
            yOffset *= mouseSensitivity_;

            yaw_ += xOffset;
            pitch_ -= yOffset;

            if (pitch_ > 89.0f)
                pitch_ = 89.0f;
            if (pitch_ < -89.0f)
                pitch_ = -89.0f;

            updateCameraVectors();
        }

    }
}
