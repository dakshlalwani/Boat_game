#include "main.h"

#ifndef NITRO_H
#define NITRO_H


class Nitro {
public:
    Nitro() {}
    Nitro(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation, cannon_roty, cannon_rotz;
    int counti,follow;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedx,speedy,speedz,accn,speed,accn1,speedx1;
private:
    VAO *object;
};

#endif // NITRO_H
