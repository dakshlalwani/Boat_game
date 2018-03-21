#include "boat.h"
#include "main.h"
#include "ball.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 0;
    this->speedyw = 0;
    this->speedzw = 0;
    this->nitrotime=0;
    this->follow = 0;
    this->health=250;
    this->nitrox=0;
    this->score=0;
    this->rotationpole=0;
    this->fattack = 0;
    this->counti = 0;
    this->counti2 = 0;
    this->speedx = 0;
    this->speedx1 = 0.05;
    this->speedy = 0;
    this->speedz = 0;
    this->accn = 0;
    this->cannon_roty = 45.0f;
    this->cannon_rotz = 30.0f;
    this->accn1 = 0.02;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
           0.0f,4.0f,0.0f,  //uppertriangle
           0.0f,2.0f,2.0f,
           0.0f,2.0f,-2.0f,

           0.0f,2.0f,2.0f,  //midbase1
           0.0f,-2.0f,2.0f,
           0.0f,2.0f,-2.0f,

           0.0f,-2.0f,2.0f,     //midbase2
           0.0f,-2.0f,-2.0f,
           0.0f,2.0f,-2.0f,

           0.0f,-2.0f,2.0f,     //lowertriangle
           0.0f,-2.0f,-2.0f,
           0.0f,-4.0f,0.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);

    static const GLfloat vertex_buffer_data_3d[] = {
            2.0f,4.0f,0.0f,
            0.0f,4.0f,0.0f,      //3d_uptria1
            0.0f,2.0f,2.0f,

            0.0f,2.0f,2.0f,
            2.0f,4.0f,0.0f,
            2.0f,2.0f,2.0f,

            2.0f,4.0f,0.0f,
            0.0f,4.0f,0.0f,      //3d_uptria2
            0.0f,2.0f,-2.0f,

            0.0f,2.0f,-2.0f,
            2.0f,4.0f,0.0f,
            2.0f,2.0f,-2.0f,

            0.0f,2.0f,2.0f,
            2.0f,2.0f,2.0f,      //3d_midbase1
            0.0f,-2.0f,2.0f,

            0.0f,-2.0f,2.0f,
            2.0f,2.0f,2.0f,
            2.0f,-2.0f,2.0f,

            0.0f,2.0f,-2.0f,
            2.0f,2.0f,-2.0f,      //3d_midbase2
            0.0f,-2.0f,-2.0f,

            0.0f,-2.0f,-2.0f,
            2.0f,2.0f,-2.0f,
            2.0f,-2.0f,-2.0f,

            0.0f,-2.0f,2.0f,
            2.0f,-2.0f,2.0f,     //3d_lowertria1
            0.0f,-4.0f,0.0f,

            0.0f,-4.0f,0.0f,
            2.0f,-2.0f,2.0f,
            2.0f,-4.0f,0.0f,

            0.0f,-2.0f,-2.0f,
            2.0f,-2.0f,-2.0f,    //3d_lowertria2
            0.0f,-4.0f,0.0f,

            0.0f,-4.0f,0.0f,
            2.0f,-2.0f,-2.0f,
            2.0f,-4.0f,0.0f,
    };

    this->object_3d = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_3d, COLOR_SILVER, GL_FILL);

    static const GLfloat vertex_buffer_data_3dpole[] = {
            0.0f,0.0f,0.25f,
            0.0f,0.0f,-0.25f,      //3d_pole
            4.0f,0.0f,0.25f,

            4.0f,0.0f,0.25f,
            4.0f,0.0f,-0.25f,
            0.0f,0.0f,-0.25f,
    };

    this->object_3dpole = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3dpole, COLOR_BROWN, GL_FILL);

    static const GLfloat vertex_buffer_data_3dpole1[] = {
            4.0f,0.0f,0.25f,
            2.0f,0.0f,0.25f,
            3.0f,0.0f,3.0f,
    };

    this->object_3dpole1 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_3dpole1, COLOR_ORANGE, GL_FILL);


    static const GLfloat vertex_buffer_data_3dcannon[] = {
            0.0f,0.25f,0.25f,
            0.0f,0.25f,-0.25f,      //3d_pole
            2.0f,4.0f,0.25f,

            2.0f,4.0f,0.25f,
            2.0f,4.0f,-0.25f,
            0.0f,0.25f,-0.25f,

            0.0f,-0.25f,0.25f,
            0.0f,-0.25f,-0.25f,      //3d_pole
            2.2f,4.0f,0.25f,

            2.2f,4.0f,0.25f,
            2.2f,4.0f,-0.25f,
            0.0f,-0.25f,-0.25f,

            0.0f,0.25f,0.25f,
            0.0f,-0.25f,0.25f,      //3d_pole
            2.0f,4.0f,0.25f,

            2.0f,4.0f,0.25f,
            2.2f,4.0f,0.25f,
            0.0f,-0.25f,0.25f,

            0.0f,0.25f,-0.25f,
            0.0f,-0.25f,-0.25f,      //3d_pole
            2.0f,4.0f,-0.25f,

            2.0f,4.0f,-0.25f,
            2.2f,4.0f,-0.25f,
            0.0f,-0.25f,-0.25f,
    };

    this->object_3dcannon = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data_3dcannon, COLOR_RED, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object_3d);
    draw3DObject(this->object_3dpole);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate(this->position);    // glTranslatef
//    rotate = glm::rotate((float) ((this->cannon_roty) * M_PI / 180.0f), glm::vec3(-1, 0, 0));
    rotate = glm::rotate((float) ((this->rotation + this->cannon_rotz) * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate *= glm::rotate((float) ((this->cannon_roty) * M_PI / 180.0f), glm::vec3(0, 0, -1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_3dcannon);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate = glm::rotate((float) (this->rotationpole * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_3dpole1);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->speedx -= this->accn;
     this->position.x += this->speedx;
     this->position.y -= speedy;
    this->position.z += speedz;
    if(this->position.x>=1 && this->counti==0) {

        this->accn1 = 0.003;
        this->speedx1 -= this->accn1;
        this->position.x += this->speedx1;
    }
    if(this->position.x<=1) {
//        if(this->position.x<=0.5) {
            this->accn1 = 0.013;
            this->speedx1 = 0.05;
            this->position.x = 1.001;
        this->accn=0;
        this->speedx=0;
//        }
//        else if(this->position.x<=1)
            this->counti=0;
    }
    counti2++;
    if (counti2 >= 300) {
        counti2 = 0;
        this->rangle = static_cast<float>(-180 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360))));
        this->rotationpole = this->rangle;
        if (this->rangle < 0) {
            this->rotation += 10;
        }
        else if (this->rangle > 0) {
            this->rotation -= 10;
        }
        if (this->rangle <= 90 && this->rangle >= -90) {
            this->speedyw = -1.5 * cos(this->rotation * M_PI / 180.0f);
            this->speedzw = 1.5 * sin(this->rotation * M_PI / 180.0f);
//            this->position.y += this->speedy;
//            this->position.z += this->speedz;
            this->speedy += this->speedyw;
            this->speedz += this->speedzw;
        }
        else if (this->rangle >= 90 || this->rangle <= -90) {
            this->speedy += 1.5 * cos(this->rotation * M_PI / 180.0f);
            this->speedz += 1.5 * sin(this->rotation * M_PI / 180.0f);
        }
    }
//    this->speedx=0;
    this->speedy=0;
    this->speedz=0;
    this->speed=0;
}

