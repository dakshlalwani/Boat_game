#include "main.h"

#ifndef PLAIN_H
#define PLAIN_H


class Plain {
public:
    Plain() {}
    Plain(float x, float y, float z, color_t color, float width,float length);
    glm::vec3 position;
    float rotation;
    int counti,follow;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedx,speedy,speedz,accn,speed,accn1,speedx1;
private:
    VAO *object_xy1;
    VAO *object1;
};

#endif // PLAIN_H
