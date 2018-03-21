#include "water.h"
#include "main.h"

Water::Water(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat trgls_data[90009];
    static const GLfloat vertex_buffer_data[] = {
            0.0f,-10000.0f, -1000.0f, // triangle 1 : begin
            0.0f, 10000.0f, -1000.0f,
            0.0f, 10000.0f, 1000.0f, // triangle 1 : end
            0.0f, 10000.0f, 1000.0f, // triangle 2 : begin
            0.0f,-10000.0f, 1000.0f,
            0.0f, -10000.0f, -1000.0f, // triangle 2 : end
    };
    for (int i = -400; i <= 400 ; i+=16) {
        for (int j = -400; j <= 400 ; j+=16) {
            if (i==0 && j==0) {
                trgls_data[11475] = 0.05;
                trgls_data[11476] = (float)i;
                trgls_data[11477] = (float)j;
                trgls_data[11478] = 0.05;
                trgls_data[11479] = (float)i;
                trgls_data[11480] = (float)j+16;
                trgls_data[11481] = 0.05;
                trgls_data[11482] = (float)i+16;
                trgls_data[11483] = (float)j;
            }
            else {
                int p = ((i + 400) / 16) * 450 + ((j + 400) / 16) * 9;
                trgls_data[p] = 0.05;
                trgls_data[p + 1] = (float) i;
                trgls_data[p + 2] = (float) j;
                trgls_data[p + 3] = 0.05;
                trgls_data[p + 4] = (float) i;
                trgls_data[p + 5] = (float) j + 16;
                trgls_data[p + 6] = 0.05;
                trgls_data[p + 7] = (float) i + 16;
                trgls_data[p + 8] = (float) j;
            }
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 50 * 50 * 3, trgls_data, COLOR_CREAMBLUE, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Water::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Water::tick() {
//    this->position.x += this->speed;
//    if(this->position.x < -2 || this->position.x > 2)
//        this->speed = -this->speed;
//    this->rotation = 0;
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
