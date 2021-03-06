#include "cuboid.h"
#include "main.h"

Cuboid::Cuboid(float x, float y, float z, color_t color, float width) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->health=500;
    this->monskill=0;
    this->complete=0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            2,-width,-width, // triangle 1 : begin
            2,-width, width,
            2, width, width, // triangle 1 : end
            width*2+2, width,-width, // triangle 2 : begin
            2,-width,-width,
            2, width,-width, // triangle 2 : end
            width*2+2,-width, width,
            2,-width,-width,
            width*2+2,-width,-width,
            width*2+2, width,-width,
            width*2+2,-width,-width,
            2,-width,-width,
            2,-width,-width,
            2, width, width,
            2, width,-width,
            width*2+2,-width, width,
            2,-width, width,
            2,-width,-width,
            2, width, width,
            2,-width, width,
            width*2+2,-width, width,
            width*2+2, width, width,
            width*2+2,-width,-width,
            width*2+2, width,-width,
            width*2+2,-width,-width,
            width*2+2, width, width,
            width*2+2,-width, width,
            width*2+2, width, width,
            width*2+2, width,-width,
            2, width,-width,
            width*2+2, width, width,
            2, width,-width,
            2, width, width,
            width*2+2, width, width,
            2, width, width,
            width*2+2,-width, width
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {
            4,-width/2,-width/2, // triangle 1 : begin
            4,-width/2, width/2,
            4, width/2, width/2, // triangle 1 : end
            5, width/2,-width/2, // triangle 2 : begin
            4,-width/2,-width/2,
            4, width/2,-width/2, // triangle 2 : end
            5,-width/2, width/2,
            4,-width/2,-width/2,
            5,-width/2,-width/2,
            5, width/2,-width/2,
            5,-width/2,-width/2,
            4,-width/2,-width/2,
            4,-width/2,-width/2,
            4, width/2, width/2,
            4, width/2,-width/2,
            5,-width/2, width/2,
            4,-width/2, width/2,
            4,-width/2,-width/2,
            4, width/2, width/2,
            4,-width/2, width/2,
            5,-width/2, width/2,
            5, width/2, width/2,
            5,-width/2,-width/2,
            5, width/2,-width/2,
            5,-width/2,-width/2,
            5, width/2, width/2,
            5,-width/2, width/2,
            5, width/2, width/2,
            5, width/2,-width/2,
            4, width/2,-width/2,
            5, width/2, width/2,
            4, width/2,-width/2,
            4, width/2, width/2,
            5, width/2, width/2,
            4, width/2, width/2,
            5,-width/2, width/2
    };
    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, COLOR_BROWN, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {

            0.0f,-0.2f,-0.6f,
            0.0f,0.2f,-0.6f,
            2.0f,-0.2f,-0.6f,

            2.0f,-0.2f,-0.6f,
            0.0f,0.2f,-0.6f,
            2.0f,0.2f,-0.6f,

            0.0f,-0.2f,-0.4f,
            0.0f,0.2f,-0.4f,
            2.0f,-0.2f,-0.4f,

            2.0f,-0.2f,-0.4f,
            0.0f,0.2f,-0.4f,
            2.0f,0.2f,-0.4f,

            0.0f,-0.2f,0.6f,
            0.0f,0.2f,0.6f,
            2.0f,-0.2f,0.6f,

            2.0f,-0.2f,0.6f,
            0.0f,0.2f,0.6f,
            2.0f,0.2f,0.6f,

            0.0f,-0.2f,0.4f,
            0.0f,0.2f,0.4f,
            2.0f,-0.2f,0.4f,

            2.0f,-0.2f,0.4f,
            0.0f,0.2f,0.4f,
            2.0f,0.2f,0.4f,

            0.0f,-0.2f,-0.6f,
            0.0f,-0.2f,-0.4f,
            2.0f,-0.2f,-0.6f,

            2.0f,-0.2f,-0.6f,
            0.0f,-0.2f,-0.4f,
            2.0f,-0.2f,-0.4f,

            0.0f,0.2f,-0.6f,
            0.0f,0.2f,-0.4f,
            2.0f,0.2f,-0.6f,

            2.0f,0.2f,-0.6f,
            0.0f,0.2f,-0.4f,
            2.0f,0.2f,-0.4f,

            0.0f,-0.2f,0.6f,
            0.0f,-0.2f,0.4f,
            2.0f,-0.2f,0.6f,

            2.0f,-0.2f,0.6f,
            0.0f,-0.2f,0.4f,
            2.0f,-0.2f,0.4f,

            0.0f,0.2f,0.6f,
            0.0f,0.2f,0.4f,
            2.0f,0.2f,0.6f,

            2.0f,0.2f,0.6f,
            0.0f,0.2f,0.4f,
            2.0f,0.2f,0.4f,
    };
    this->object2 = create3DObject(GL_TRIANGLES, 16*3, vertex_buffer_data2, COLOR_BROWN, GL_FILL);

}

void Cuboid::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Cuboid::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cuboid::tick() {
    this->rotation += speed;
}
