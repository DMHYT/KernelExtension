#include <commontypes.hpp>

#ifndef KEX_CAMERADIRECTOR_HPP
#define KEX_CAMERADIRECTOR_HPP


class Camera {
    public:
    void setOrientation(float, float, float);
    Vec3 getEulerAngles() const;  
};

class CameraDirector {
    public:
    Camera* getCamera() const;
};

class Timer {
    public:
    float getAlpha() const;
};

class Minecraft {
    public:
    Timer* getTimer();
};


#endif //KEX_CAMERADIRECTOR_HPP