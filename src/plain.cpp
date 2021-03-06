#include "plain.h"
#include "main.h"

Plain::Plain(float x, float y, float z, color_t color, float width, float length) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
//    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {
            0.0f,-length,-length,
            0.0f,-length,length,
            0.0f,length,length,

            0.0f,length,length,
            0.0f,-length,-length,
            0.0f,length,-length,

            0.0f,-length,-length,
            0.0f,length,-length,
            width,0.0f,0.0f,

            0.0f,-length,-length,
            0.0f,-length,length,
            width,0.0f,0.0f,

            0.0f,-length,length,
            0.0f,length,length,
            width,0.0f,0.0f,

            0.0f,length,-length,
            0.0f,length,length,
            width,0.0f,0.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void Plain::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
//    draw3DObject(this->object_xy2);
//    draw3DObject(this->object_xz1);
//    draw3DObject(this->object_xz2);
}

void Plain::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Plain::tick() {
//    this->rotation += 2;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

