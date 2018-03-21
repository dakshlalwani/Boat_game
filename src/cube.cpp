#include "cube.h"
#include "main.h"

Cube::Cube(float x, float y, float z, color_t color, float width) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->health=500;
    this->monskill=0;
    speed = 0;
    this->manacc=0;
    this->manx=0;
    this->many=0;
    this->manz=0;
    this->mancount=0;
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

void Cube::draw(glm::mat4 VP) {
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
//    draw3DObject(this->object1);
}

void Cube::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cube::tick() {
    this->rotation += speed;
    if (this->mancount) {
//        printf("yesssssssssssss\n");
        this->manx -= this->manacc;
        this->position.x += this->manx;
        this->position.y -= many;
        this->position.z += manz;
        if (this->position.x <= 1) {
            this->position.x = 1;
            this->manx = 0;
            this->manacc = 0;
//            this->mancount=0;
        }
        this->many = 0;
        this->manz = 0;
    }
    if (this->position.x<1) {
        this->many=0;
        this->manz=0;
    }
}
