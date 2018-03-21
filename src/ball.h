#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color, float width);
    glm::vec3 position;
    float rotation,xsp,ysp,zsp,xaccn,sunacc,suny,sunx,sunz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    int suncount;
private:
    VAO *object;
};

#endif // BALL_H
