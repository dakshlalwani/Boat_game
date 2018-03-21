#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "boat.h"
#include "objcircle.h"
#include "nitro.h"
#include "plain.h"
#include "cuboid.h"
#include "island.h"
#include "cube.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

//Ball ball1;
Water water1;
Boat boat1;
Ball ball1[100], f[100],sun;
Objcircle objcircle1[20], coin;
Nitro nitro1[30];
Plain plain1[20], rocks[50], treasure;
Ball ballcan;
Cuboid cuboid1, cuboid2;
Island island;
Cube cube1[5],man;

int window_width = 1024;
int window_height = 768;
int count = 0, change = 0, counttimer = 0, j = 0, k = 0, mousekey = 0, cubescount = 0, gamewon=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, fx[100], fy[100], fz[100];
double e1 = 10, e2 = 0, e3 = 0, t1 = 0, t2 = 0, t3 = 0, u1 = 0, u2 = 1, u3 = 0, xpos = 0, ypos = 0, eh1=15, eh2=50, eh3=0, th1=0, th2=1, th3=0;
float camera_rotation_angle = 0;
double curposz, prevposz, curposy, prevposy;
std::string hm = "",hm2="Top";
char camera_state[10] = {'b', 's', 't', 'f', 'h'};

Timer t60(1.0 / 60);

void draw();

void set_view(int count) {
    if (count==-1) {
        e1 = 7;
        e2 = -5 * cos(man.rotation * M_PI / 180.0f) + man.position.y;
        e3 = -5 * sin(man.rotation * M_PI / 180.0f) + man.position.z;
        t1 = man.position.x;
        t2 = man.position.y;
        t3 = man.position.z;
        u1 = 1;
        u2 = 0;
        u3 = 0;
        hm2 = "Follow";
        draw();
        return;
    }
    if (count % 5 == 0) {
        e1 = 10;
        e2 = boat1.position.y;
        e3 = boat1.position.z;
        t1 = boat1.position.x;
        t2 = boat1.position.y;
        t3 = boat1.position.z;
        u1 = 0;
        u2 = 1;
        u3 = 0;
        hm2 = "Top";
    }
    if (count % 5 == 1) {
        e1 = 7;
        e2 = -5 * cos(boat1.rotation * M_PI / 180.0f) + boat1.position.y;
        e3 = -5 * sin(boat1.rotation * M_PI / 180.0f) + boat1.position.z;
        t1 = boat1.position.x;
        t2 = boat1.position.y;
        t3 = boat1.position.z;
        u1 = 1;
        u2 = 0;
        u3 = 0;
        hm2 = "Follow";
    }
    if (count % 5 == 2) {
        e1 = boat1.position.x + 4;
        e2 = boat1.position.y;
        e3 = boat1.position.z;
        t1 = boat1.position.x + 2;
        t2 = boat1.position.y + 2 * cos(boat1.rotation * M_PI / 180.0f);
        t3 = boat1.position.z + 2 * sin(boat1.rotation * M_PI / 180.0f);
        u1 = 1;
        u2 = 0;
        u3 = 0;
        hm2 = "Boat";
    }
    if (count % 5 == 3) {
        e1 = 20;
        e2 = 0;
        e3 = 20;
        t1 = boat1.position.x;
        t2 = boat1.position.y;
        t3 = boat1.position.z;
        u1 = 1;
        u2 = 0;
        u3 = 0;
        hm2 = "Tower";
    }
    if (count % 5 == 4) {
        e1 = eh1;
        e2 = eh2;
        e3 = eh3;
        t1 = th1;
        t2 = th2;
        t3= th3;
        u1 = 1;
        u2 = 0;
        u3 = 0;
        hm2 = "Helicopter";
    }
    draw();
}


void scroll_call(double x_scroll, double y_scroll){
    eh1 += (y_scroll)*(th1-eh1)/sqrt((th1-eh1)*(th1-eh1) + (th2-eh2)*(th2-eh2) + (th3-eh3)*(th3-eh3));
    eh2 += (y_scroll)*(th2-eh2)/sqrt((th1-eh1)*(th1-eh1) + (th2-eh2)*(th2-eh2) + (th3-eh3)*(th3-eh3));
    eh3 += (y_scroll)*(th3-eh3)/sqrt((th1-eh1)*(th1-eh1) + (th2-eh2)*(th2-eh2) + (th3-eh3)*(th3-eh3));
    set_view(count);
}

void dragS() {
    mousekey = 1;
}

void dragE() {
    mousekey = 0;
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye(e1, e2, e3);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target(t1, t2, t3);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up(u1, u2, u3);
    Matrices.view = glm::lookAt(eye, target, up);
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;
    water1.draw(VP);
    for (int i = 0; i < 10; ++i) {
        nitro1[i].draw(VP);
    }
//    for(int i=0;i<1;i++)
//        ball1[i].draw(VP);
    boat1.draw(VP);
    for (int i = 0; i < 20; ++i) {
        objcircle1[i].draw(VP);
        plain1[i].draw(VP);
    }
    for (int i = 0; i < 50; ++i) {
        rocks[i].draw(VP);
    }
    if (boat1.fattack) {
        ballcan.draw(VP);
    }
    cuboid1.draw(VP);
//    cuboid2.draw(VP);
    for (int i = 0; i < 4; ++i) {
        cube1[i].draw(VP);
    }
//    cube1.draw(VP);
    coin.draw(VP);
    island.draw(VP);
    treasure.draw(VP);
    man.draw(VP);
//    if (boat1.follow) {
//        for (int i=0;i<99;i++) {
//            f[i].draw(VP);
//        }
//    }
}

void tick_input(GLFWwindow *window) {
    glfwGetCursorPos(window, &curposz, &curposy);
    int cnleft = glfwGetKey(window, GLFW_KEY_A);
    int cnright = glfwGetKey(window, GLFW_KEY_D);
    int cnup = glfwGetKey(window, GLFW_KEY_W);
    int cndown = glfwGetKey(window, GLFW_KEY_S);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int zoomin = glfwGetKey(window, GLFW_KEY_M);
    int zoomout = glfwGetKey(window, GLFW_KEY_N);
    int viewchange = glfwGetKey(window, GLFW_KEY_V);
    int attack = glfwGetKey(window, GLFW_KEY_F);
    int manplayer = glfwGetKey(window, GLFW_KEY_T);
    if (left) {
        if (count!=-1) {
            boat1.speed = 0.8;
            boat1.rotation += boat1.speed;
            boat1.speed = 0;
        } else {
            man.speed = 0.8;
            man.rotation += man.speed;
            man.speed=0;
        }
        set_view(count);
    }
    if (right) {
        if (count!=-1) {
            boat1.speed = -0.8;
            boat1.rotation += boat1.speed;
            boat1.speed = 0;
        } else {
            man.speed = -0.8;
            man.rotation += man.speed;
            man.speed=0;
        }
        set_view(count);
    }
    if (up) {
        // TODO
//        boat1.follow=1;
//        for (j = k; j < 99; j=(j+1)) {
//            if (fz[j]==-5) {
//                fx[j] = boat1.position.z;
//                fy[j] = boat1.position.y;
//                f[j] = Ball(1, fy[j], fx[j], COLOR_BLACK);
//            }
//            else if (fz[j] != 0) {
//                if (f[j].position.x != boat1.position.x) {
//                    f[j].set_position(1, boat1.position.y, boat1.position.z);
//                    draw();
//                } else
//                    break;
//            }
//        }
//        k=j%99;
        if (count!=-1) {
            boat1.speedy = -0.8 * cos(boat1.rotation * M_PI / 180.0f);
            boat1.speedz = 0.8 * sin(boat1.rotation * M_PI / 180.0f);
        } else {
//            printf("%d      %f\n",count,man.rotation);
            man.many = static_cast<float>(-0.8 * cos(man.rotation * M_PI / 180.0f));
            man.manz = static_cast<float>(0.8 * sin(man.rotation * M_PI / 180.0f));
        }
        set_view(count);
    }
    if (down) {
        boat1.follow = 1;
        if (count!=-1) {
            boat1.speedy = 0.8 * cos(boat1.rotation * M_PI / 180.0f);
            boat1.speedz = -0.8 * sin(boat1.rotation * M_PI / 180.0f);
        } else {
            man.many = static_cast<float>(0.8 * cos(man.rotation * M_PI / 180.0f));
            man.manz = static_cast<float>(-0.8 * sin(man.rotation * M_PI / 180.0f));
        }
        set_view(count);
    }
    if (jump && boat1.counti == 0 && boat1.position.x >= 1.0) {
        // TODO
//        boat1.follow=0;
//        k=0;
//        for(int p =0;p<=99;p++) {
//            f[p].set_position(-10, 0, 0);
//            draw();
//        }
        boat1.counti = 1;
        boat1.accn = 0.005;
        boat1.speedx = 0.15;
//        boat1.speedy = 0.1;
//        boat1.speedz = 0.1;
    }
//    if (mousekey==1) {
//        if (curpos - prevpos >0) {
//            right = 1;
//        }
//        else if (curpos - prevpos <0) {
//            left = 1;
//        }
//    }
    if (cnleft)
        boat1.cannon_rotz += 1;
    if (cnright)
        boat1.cannon_rotz -= 1;
    if (cnup)
        boat1.cannon_roty += 1;
    if (cndown)
        boat1.cannon_roty -= 1;

    if (viewchange == 0)
        counttimer = 0;
    if (viewchange) {
        if (counttimer == 0) {
            if (count == 4)
                count = 0;
            else
                count++;
            set_view(count);
        }
        counttimer++;
        if (counttimer == 10)
            counttimer = 0;
    }
    if (attack != 0 && boat1.fattack == 0) {
        boat1.fattack = 1;
        ballcan.position.x = static_cast<float>(boat1.position.x + (4.3 * sin(boat1.cannon_roty * M_PI / 180.0f) *
                                                                    cos((boat1.cannon_rotz + boat1.rotation) * M_PI /
                                                                        180.0f)));
        ballcan.position.y = static_cast<float>(boat1.position.y + (4.3 * sin(boat1.cannon_roty * M_PI / 180.0f)));
        ballcan.position.z = static_cast<float>(boat1.position.z + (4.3 * cos(boat1.cannon_roty * M_PI / 180.0f) *
                                                                    sin((boat1.cannon_rotz + boat1.rotation) * M_PI /
                                                                        180.0f)));
        ballcan.xsp = 0.3;
    }
    if (boat1.fattack) {
        ballcan.xaccn = 0.013;
        ballcan.xsp -= ballcan.xaccn;
        ballcan.position.x += ballcan.xsp;
        ballcan.position.y += ballcan.ysp * cos(boat1.cannon_roty * M_PI / 180.0f) *
                              cos((boat1.cannon_rotz + boat1.rotation) * M_PI / 180.0f);
        ballcan.position.z += ballcan.ysp * cos(boat1.cannon_roty * M_PI / 180.0f) *
                              sin((boat1.cannon_rotz + boat1.rotation) * M_PI / 180.0f);
//        printf("%f %f %f\n",ballcan.position.x,ballcan.position.y,ballcan.position.z);
    }
    if (boat1.fattack == 1 && ballcan.position.x <= 0)
        boat1.fattack = 0;
//    if (trea && cuboid1.complete) {
//        set_view(1000);
//    }
//    printf("%f   %f   %f======\n",man.position.x,man.position.y,man.position.z);
    if (manplayer && cuboid1.complete && (boat1.position.z<-30 && boat1.position.z>-130 && boat1.position.y<-30 && boat1.position.y>-130)) {
        man.set_position(3,boat1.position.y,boat1.position.z);
        count = -1;
        man.mancount=1;
        man.manacc=0.013;
        man.manx = 0.1;
        man.many = 0.1;
        man.manz = 0.1;
        cuboid1.complete=0;
    }
    glfwGetCursorPos(window, &curposz, &curposy);
    if (mousekey == 1) {
        float v1,v3,l1,l2;
        v1 += (th1-eh1)/sqrt((th1-eh1)*(th1-eh1) + (th2-eh2)*(th2-eh2) + (th3-eh3)*(th3-eh3));
        v3 += (th3-eh3)/sqrt((th1-eh1)*(th1-eh1) + (th2-eh2)*(th2-eh2) + (th3-eh3)*(th3-eh3));
        l1 = v3/sqrt(v1*v1+v3*v3);
        l2 = v1/sqrt(v1*v1+v3*v3);
        th1 += l2*(curposy-prevposy) + l1*(curposz-prevposz);
        th3 += l1*(curposy-prevposy) + l2*(curposz-prevposz);
        set_view(count);
    }
    prevposz = curposz;
    prevposy = curposy;
}

void tick_elements() {
//    ball1.tick();
    water1.tick();
    boat1.tick();
    coin.tick();
    cuboid1.tick();
    man.tick();
    for (int i = 0; i < 4; ++i) {
        cube1[i].tick();
    }
//    cube1.tick();
//    cuboid2.tick();
//    for(int i=0;i<1;i++)
//        ball1[i].tick();
    // TODO: BONUS
    for (int i = 0; i < 20; ++i) {
        objcircle1[i].tick();
    }
//    for (int i = 0; i < 20; ++i) {
//        printf("%f---%f------\n",plain1[i].position.x,boat1.position.x);
//    }
//    for(int i=0;i<=99;i++) {
//        printf("%d   %f   %f-----------\n",i,f[i].position.z,f[i].position.y);
//    }

//    printf("%d======count\n",count);
//    camera_rotation_angle += 1;

    for (int i = 0; i < 20; ++i) {
//        printf("%f   %f   %f   %f   %f   %f\n",objcircle1[i].position.x,objcircle1[i].position.y,objcircle1[i].position.z,boat1.position.x,boat1.position.y,boat1.position.z);
        if (fabs(boat1.position.x - objcircle1[i].position.x) <= 1.5 &&
            fabs(boat1.position.y - objcircle1[i].position.y) <= 4 &&
            fabs(boat1.position.z - objcircle1[i].position.z) <= 4) {
//            printf("yessssssss\n");
            boat1.health += 20;
            float z = static_cast<float>(-300 +
                                         static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
            float y = static_cast<float>(-300 +
                                         static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
            objcircle1[i].set_position(3, y, z);
            plain1[i].set_position(0, y, z);
            hm = "Yay Health!!";
        }
    }
    if (fabs(boat1.position.x - coin.position.x) <= 1.5 && fabs(boat1.position.y - coin.position.y) <= 4 &&
        fabs(boat1.position.z - coin.position.z) <= 4) {
        boat1.score += 500;
        coin.set_position(-5, 0, 0);
        hm = "Go to the Island!!";
    }
    for (int i = 0; i < 29; ++i) {
        if (fabs(boat1.position.x - nitro1[i].position.x) <= 2 && fabs(boat1.position.y - nitro1[i].position.y) <= 4 &&
            fabs(boat1.position.z - nitro1[i].position.z) <= 4) {
            boat1.nitrox = 1;
            boat1.nitrotime = 0;
            float z = static_cast<float>(-300 +
                                         static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
            float y = static_cast<float>(-300 +
                                         static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
            nitro1[i].set_position(1.0, y, z);
            hm = "Nitro Booster";
//            printf("yessssssss\n");
        }
    }
    for (int i = 0; i < 50; ++i) {
        if (fabs(boat1.position.x - rocks[i].position.x) <= 2 && fabs(boat1.position.y - rocks[i].position.y) <= 4 &&
            fabs(boat1.position.z - rocks[i].position.z) <= 2) {
            boat1.health -= 10;
            float z = static_cast<float>(-300 +
                                         static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
            float y = static_cast<float>(-300 +
                                         static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
            rocks[i].set_position(0.0f, y, z);
            hm = "Watch out for rocks";
//            printf("yessssssss\n");
        }
    }
//    printf("%f %f %f\n",cuboid1.position.x,cuboid1.position.y,cuboid1.position.z);
//    if (cuboid1.monskill==1) {
    if (fabs(boat1.position.x - cuboid1.position.x) <= 2 && fabs(boat1.position.y - cuboid1.position.y) <= 2 &&
        fabs(boat1.position.z - cuboid1.position.z) <= 2) {
        boat1.health -= 30;
        hm = "Watch out for Boss Monster";
        //        printf("yessssss\n");
    }
//    }
    for (int i = 0; i < 4; ++i) {
        if (fabs(boat1.position.x - cube1[i].position.x) <= 2 && fabs(boat1.position.y - cube1[i].position.y) <= 2 &&
            fabs(boat1.position.z - cube1[i].position.z) <= 2) {
            boat1.health -= 20;
            hm = "Watch out for Monster";
            //        printf("yessssss\n");
        }
    }
    if (boat1.health <= 0)
        boat1.health = 0;
//    printf("%f   %f   %f   %f   %f   %f\n",ballcan.position.x,ballcan.position.y,ballcan.position.z,cuboid1.position.x,cuboid1.position.y,cuboid1.position.z);
    if (cuboid1.monskill == 1) {
        if ((fabs(ballcan.position.x - cuboid1.position.x) <= 10) && ballcan.position.x >= 0 &&
            (fabs(ballcan.position.y - cuboid1.position.y) <= 3.5) &&
            (fabs(ballcan.position.z - cuboid1.position.z) <= 3.5 &&
             fabs(ballcan.position.z - cuboid1.position.z) >= 0.5)) {
            //        printf("yessssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n");
            cuboid1.health -= 30;
            hm = "  BOSS-HIT ";
        }
    }
    for (int i = 0; i < 4; ++i) {
        if ((fabs(ballcan.position.x - cube1[i].position.x) <= 6) && ballcan.position.x >= 0 &&
            (fabs(ballcan.position.y - cube1[i].position.y) <= 3.5) &&
            (fabs(ballcan.position.z - cube1[i].position.z) <= 3.5 &&
             fabs(ballcan.position.z - cube1[i].position.z) >= 0.5)) {
//        printf("yessssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n");
            cube1[i].health -= 100;
            hm = " Monster HIT ";
        }
    }
    if (boat1.health <= 0) {
//        printf("ohkkkkkkk\n");
        hm = "You DIED!!";
    }
    for (int i = 0; i < 4; ++i) {
        if (cube1[i].health <= 0) {
            cubescount++;
            cube1[i].health = 500;
            cube1[i].set_position(-10, -10, 10);
        }
    }
    if (cubescount == 1) {
        cubescount = 0;
        cuboid1.monskill = 1;
//        cuboid1.complete=1;
        cuboid1.health = 500;
        float z = static_cast<float>(-10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
        float y = static_cast<float>(-10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
        cuboid1.set_position(0, y, z);
    }
    if (cuboid1.health <= 0) {
        cuboid1.health = 500;
        cuboid1.set_position(-10, 0, 0);
        cuboid1.complete = 1;
        cuboid1.monskill = 0;
        coin.set_position(3, cuboid1.position.y, cuboid1.position.z);
//        for (int i = 0; i < 4; ++i) {
//            cube1[i].health = 500;
//            float z = static_cast<float>(-10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
//            float y = static_cast<float>(-10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
//            cube1[i].set_position(0, y, z);
//        }
        hm = "Get the coin";
    }
    if (boat1.nitrox == 1) {
        boat1.nitrotime += 1;
        if (boat1.nitrotime <= 100) {
            boat1.speedy = -1.5 * cos(boat1.rotation * M_PI / 180.0f);
            boat1.speedz = 1.5 * sin(boat1.rotation * M_PI / 180.0f);
        } else {
            boat1.nitrox = 0;
        }
        set_view(count);
    }
    if (cuboid1.complete) {
        island.set_position(0.5, -80, -80);
        treasure.set_position(0.5, -85, -105);
//        count=4;
//        set_view(count);
//        cuboid1.complete = 0;
    }
    if (fabs(man.position.x-treasure.position.x<2 && fabs(man.position.y-treasure.position.y<1.5) && fabs(man.position.z-treasure.position.z<1.5))) {
        treasure.set_position(-100,0,0);
        gamewon=1;
        boat1.score += 1000;
        hm = "You found the treasure!!";
//        exit(0);
    }
//    printf("%f   %f   %f   %f   %f   %f\n",treasure.position.x,treasure.position.y, treasure.position.z,boat1.position.x,boat1.position.y,boat1.position.z);
    std::string title = "BOAT MANIA     Score : ";
    std::string sco = std::to_string(boat1.score);
    std::string title2 = "  Health : ";
    std::string hea = std::to_string(boat1.health);
    sco = title + sco + title2 + hea + "    " + hm + "    " + hm2 + " View";
    glfwSetWindowTitle(window, const_cast<char *>(sco.c_str()));
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

//    ball1 = Ball(0, 0, 0, COLOR_RED);
    water1 = Water(0, 0, 0, COLOR_BLUE);
//    for(int i=0;i<50;i++)
//    {
//        float z = static_cast<float>(-50 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100))));
//        float y = static_cast<float>(0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100))));
//        ball1[i] = Ball(1, y, -z, COLOR_RED, 0.1);
//    }
    for (int i = 0; i < 20; ++i) {
        float z = static_cast<float>(-300 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
        float y = static_cast<float>(-300 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
        objcircle1[i] = Objcircle(3, y, z, COLOR_ORANGE, 1, 3.0f);
        plain1[i] = Plain(0, y, z, COLOR_RED, 2.0f, 1.0f);
    }
    for (int i = 0; i < 20; ++i) {
        float z = static_cast<float>(-300 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
        float y = static_cast<float>(-300 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
        nitro1[i] = Nitro(1.0, y, z, COLOR_INDIGO);
    }
    for (int i = 0; i < 50; ++i) {
        float z = static_cast<float>(-300 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
        float y = static_cast<float>(-300 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (500))));
        rocks[i] = Plain(0, y, z, COLOR_BROWN, 1.0f, 2.0f);
    }
    float z = static_cast<float>(10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
    float y = static_cast<float>(10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
    ballcan = Ball(-2, 0, 0, COLOR_BLACK, 0.5);
    cuboid1 = Cuboid(-10, y, z, COLOR_ORANGE, 2.5);
    for (int i = 0; i < 4; ++i) {
        float z = static_cast<float>(-50 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100))));
        float y = static_cast<float>(-50 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100))));
        cube1[i] = Cube(0, y, z, COLOR_RED, 1);
    }
//    cube1 = Cube(0, y+3,z+3,COLOR_RED,1);
//    cuboid2 = Cuboid(0,y+3,z+3,COLOR_RED,10);
    boat1 = Boat(1, 0, 0, COLOR_PINK);
    coin = Objcircle(-5, 0, 0, COLOR_YELLOW, 2, 0.0f);
    island = Island(-5, 0, 0, COLOR_BACKGROUND);
    treasure = Plain(-5, 0, 0, COLOR_GOLD, 2.0f, 1.0f);
    man = Cube(-15,10,0,COLOR_BLUE,5);
//    for (int i=0;i<=99;i++) {
//        fz[i] = -5;
//    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(0.9f, 0.9f, 1.0f, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL(window, width, height);
    glfwGetCursorPos(window, &prevposz, &prevposy);
    glfwSetScrollCallback(window, scroll_callback);

    audio_init();

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        audio_play();

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);

    float near = 1.0f;
    float far = 800.0;
    GLfloat fov = M_PI / 1.3f;
    Matrices.projection = glm::perspective(fov, (GLfloat) window_width / (GLfloat) window_height, near, far);
}
