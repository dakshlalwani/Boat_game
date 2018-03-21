#include "main.h"

#ifndef CUBOID_H
#define CUBOID_H


class Cuboid {
public:
    Cuboid() {}
    Cuboid(float x, float y, float z, color_t color, float width);
    glm::vec3 position;
    float rotation;
    int counti,follow,health,monskill,complete;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedx,speedy,speedz,accn,speed,accn1,speedx1;
private:
    VAO *object1;
    VAO *object2;
    VAO *object;
};

#endif // CUBOID_H
