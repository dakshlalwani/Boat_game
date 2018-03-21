#include "objcircle.h"
#include "main.h"

Objcircle::Objcircle(float x, float y, float z, color_t color, float radii, float width) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
//    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    GLfloat g_vertex_buffer_data_xy1[10000];
    float oct_theta = 0.79, circle_theta = 0.017;
    g_vertex_buffer_data_xy1[0] = width;
    g_vertex_buffer_data_xy1[1] = 0.0f;
    g_vertex_buffer_data_xy1[2] = 0.0f;
    g_vertex_buffer_data_xy1[3] = radii;
    g_vertex_buffer_data_xy1[4] = 0.0f;
    g_vertex_buffer_data_xy1[5] = 0.0f;
    g_vertex_buffer_data_xy1[8] = 0.0f;

    for (int i = 0; i < 1000; i++) {
        if (i == 0) {
            g_vertex_buffer_data_xy1[6] = (float) cos(circle_theta) * g_vertex_buffer_data_xy1[3] -
                                      (float) sin(circle_theta) * g_vertex_buffer_data_xy1[4];
            g_vertex_buffer_data_xy1[7] = (float) sin(circle_theta) * g_vertex_buffer_data_xy1[3] +
                                      (float) cos(circle_theta) * g_vertex_buffer_data_xy1[4];
        } else {
            g_vertex_buffer_data_xy1[i * 9] = width;
            g_vertex_buffer_data_xy1[i * 9 + 1] = 0.0f;
            g_vertex_buffer_data_xy1[i * 9 + 2] = 0.0f;
            g_vertex_buffer_data_xy1[i * 9 + 3] = g_vertex_buffer_data_xy1[(i - 1) * 9 + 6];
            g_vertex_buffer_data_xy1[i * 9 + 4] = g_vertex_buffer_data_xy1[(i - 1) * 9 + 7];
            g_vertex_buffer_data_xy1[i * 9 + 5] = 0.0f;
            g_vertex_buffer_data_xy1[i * 9 + 6] = (float) cos(circle_theta) * g_vertex_buffer_data_xy1[i * 9 + 3] -
                                              (float) sin(circle_theta) * g_vertex_buffer_data_xy1[i * 9 + 4];
            g_vertex_buffer_data_xy1[i * 9 + 7] = (float) sin(circle_theta) * g_vertex_buffer_data_xy1[i * 9 + 3] +
                                              (float) cos(circle_theta) * g_vertex_buffer_data_xy1[i * 9 + 4];
            g_vertex_buffer_data_xy1[i * 9 + 8] = 0.0f;
        }
    }


    this->object_xy1 = create3DObject(GL_TRIANGLES, 3000, g_vertex_buffer_data_xy1, color, GL_FILL);
}

void Objcircle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_xy1);
//    draw3DObject(this->object1);
//    draw3DObject(this->object_xy2);
//    draw3DObject(this->object_xz1);
//    draw3DObject(this->object_xz2);
}

void Objcircle::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Objcircle::tick() {
    this->rotation += 2;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

