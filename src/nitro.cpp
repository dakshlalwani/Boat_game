#include "nitro.h"
#include "main.h"

Nitro::Nitro(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed=0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            0.0f,0.0f,0.0f,  //uppertriangle
            1.0f,0.0f,1.0f,
            1.0f,0.0f,2.0f,

            1.0f,0.0f,1.0f,  //midbase1
            2.0f,0.0f,0.0f,
            2.0f,0.0f,1.0f,

            1.0f,0.0f,1.0f,     //midbase2
            2.0f,0.0f,1.0f,
            1.0f,0.0f,2.0f,

            2.0f,0.0f,0.0f,     //lowertriangle
            2.0f,0.0f,1.0f,
            3.0f,0.0f,2.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Nitro::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
//    draw3DObject(this->object_3d);
//    draw3DObject(this->object_3dpole);
//    Matrices.model = glm::mat4(1.0f);
//    translate = glm::translate(this->position);    // glTranslatef
////    rotate = glm::rotate((float) ((this->cannon_roty) * M_PI / 180.0f), glm::vec3(-1, 0, 0));
//    rotate = glm::rotate((float) ((this->rotation + this->cannon_rotz) * M_PI / 180.0f), glm::vec3(1, 0, 0));
//    rotate *= glm::rotate((float) ((this->cannon_roty) * M_PI / 180.0f), glm::vec3(0, 0, -1));
//    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
//    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
//    Matrices.model *= (translate * rotate);
//    MVP = VP * Matrices.model;
//    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
//    draw3DObject(this->object_3dcannon);
}

void Nitro::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Nitro::tick() {

//    this->speedx -= this->accn;
//    this->position.x += this->speedx;
//    this->position.y -= speedy;
//    this->position.z += speedz;
//    if(this->position.x<=0) {
//        this->position.x = 0;
//        this->speedx = 0;
//    }
//    if(this->position.x>-1 && this->counti==0) {
//        this->accn1 = 0.02;
//        this->speedx1 -= this->accn1;
//        this->position.x += this->speedx1;
//    }
//    if(this->position.x<=0){
//        if(this->position.x<=-1) {
//            this->accn1 = 0.03;
//            this->speedx1 = 0.075;
//            this->position.x = -1;
//        }
//        else if(this->position.x<=0)
//            this->counti=0;
//    }
////    this->speedx=0;
//    this->speedy=0;
//    this->speedz=0;
//    this->speed=0;
}

