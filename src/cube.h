#include "main.h"

#ifndef CUBE_H
#define CUBE_H


class Cube {
public:
    Cube() {}
    Cube(float x, float y, float z, color_t color, float width);
    glm::vec3 position;
    float rotation,manx,many,manz,mancount,manacc;
    int counti,follow,health,monskill;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedx,speedy,speedz,accn,speed,accn1,speedx1;
private:
    VAO *object1;
    VAO *object2;
    VAO *object;
};

#endif // CUBE_H
