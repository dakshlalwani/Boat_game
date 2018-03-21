#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation, cannon_roty, cannon_rotz,rotationpole,rangle;
    int counti,follow,fattack,counti2,health,nitrox,score,nitrotime;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedx,speedy,speedz,accn,speed,accn1,speedx1,speedyw,speedzw;
private:
    VAO *object;
    VAO *object_3d;
    VAO *object_3dpole;
    VAO *object_3dpole1;
    VAO *object_3dcannon;
};

#endif // BOAT_H
