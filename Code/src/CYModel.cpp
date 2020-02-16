#include <GL/glut.h>
#include <cmath>
#include "../include/CYModel.hpp"
using namespace CYModel;

SpaceHotel::SpaceHotel(){
    qObj = gluNewQuadric();
    gluQuadricNormals(qObj, GLU_SMOOTH);
    posx = 20;
    posy = 20;
    posz = -20;
    rot = 45;
    velx = 2;
    vely = 0;
    velz = 2;
}

void SpaceHotel::drawConnector(){
    glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0, 8, 0);
    glRotatef(-90, 1, 0, 0);
        gluCylinder(qObj, 0.75, 0.75, 2, 32, 32);
    glTranslatef(0, -1, 0);
        gluCylinder(qObj, 0.25, 0.25, 2, 32, 32);
    glTranslatef(0, 2, 0);
        gluCylinder(qObj, 0.25, 0.25, 2, 32, 32);
}

void SpaceHotel::drawLightBulb(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0.5, 0.5);
    glTranslatef(0, 6.5, 0);
    glutSolidSphere(0.5, 32, 32);
    glDisable(GL_BLEND);
}

void SpaceHotel::draw(){
    glPushMatrix();
        glTranslatef(posx, posy, posz);
        glRotatef(rot, 1, 0, 0);
    glDisable(GL_CULL_FACE);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidTorus(1, 11, 4, 32);
    glPushMatrix();
        glTranslatef(0, 0, -1);
        gluCylinder(qObj, 8, 8, 2, 32, 32);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, -1);
        glBegin(GL_TRIANGLES);
            for (int i = 0; i <= 32; i++){
                glColor3f(0.5, 0.5, 0.5);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f((8 * cos(i*2*PI/32)),
                           (8 * sin(i*2*PI/32)), 0.0f);
                glVertex3f((8 * cos((i+1)*2*PI/32)),
                           (8 * sin((i+1)*2*PI/32)), 0.0f);
            }
        glEnd();
        glColor3f(0.8, 0.8, 0.8);
        glBegin(GL_TRIANGLES);
            for (int i = 0; i <= 32; i++){
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f((4 * cos(i*2*PI/32)),
                            (4 * sin(i*2*PI/32)), 0.0f);
                glVertex3f((4 * cos((i+1)*2*PI/32)),
                            (4 * sin((i+1)*2*PI/32)), 0.0f);
            }
        glEnd();
        glTranslatef(0, 0, 2);
        glBegin(GL_TRIANGLES);
            glColor3f(0.5, 0.5, 0.5);
            for (int i = 0; i <= 32; i++){
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f((8 * cos(i*2*PI/32)),
                           (8 *sin(i*2*PI/32)), 0.0f);
                glVertex3f((8 * cos((i+1)*2*PI/32)),
                           (8 *sin((i+1)*2*PI/32)), 0.0f);
            }
        glEnd();
        glColor3f(0.8, 0.8, 0.8);
        glBegin(GL_TRIANGLES);
            for (int i = 0; i <= 32; i++){
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f((4 * cos(i*2*PI/32)),
                            (4 * sin(i*2*PI/32)), 0.0f);
                glVertex3f((4 * cos((i+1)*2*PI/32)),
                            (4 * sin((i+1)*2*PI/32)), 0.0f);
            }
        glEnd();
    glPopMatrix();
    glPushMatrix();
    float angle = 90;
        for (int i = 0; i < 4; i++){
            glPushMatrix();
                drawConnector();
            glPopMatrix();
            glRotatef(angle, 0, 0, 1);
            angle += 90;
        }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0, 1);
    angle = 360/32.0;
        for (int i = 0; i < 32; i++){
            glPushMatrix();
                drawLightBulb();
            glPopMatrix();
            glRotatef(angle, 0, 0, 1);
            angle += (360/32.0);
        }
    glTranslatef(0, 0, -2);
    angle = 360/32.0;
        for (int i = 0; i < 32; i++){
            glPushMatrix();
                drawLightBulb();
            glPopMatrix();
            glRotatef(angle, 0, 0, 1);
            angle += (360/32.0);
        }
    glPopMatrix();
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

void SpaceHotel::tickTime(long int elapsedTime){
    if (animation){
        float elapsedTimeInSec = elapsedTime / 1000.0f;
        posx -= elapsedTimeInSec * velx;
        posz -= elapsedTimeInSec * velz;

    if (posx > 20){
        posx = 40 - posx;
        velx = -velx;
    }
    else if (posx < -70){
        posx = -140 - posx;
        velx = -velx;
    }
    if (posz > 20 ){
        posz = 40 - posz;
        velz = -velz;
    }
    else if (posz < -100){
        posz = -200 - posz;
        velz = -velz;
    }
    }
}

SpaceHotel::~SpaceHotel(){
    gluDeleteQuadric(qObj);
}

UFO::UFO(){
    posx = 50;
    posy = 50;
    posz = 50;
    velx = -160 * 0.1;
    vely = 15 * 0.1;
    velz = -145 * 0.1;
    rot = false;
    angle = 10;
}

void UFO::draw(){
    glPushMatrix();
    glTranslatef(posx, posy, posz);
    if (rot)
        glRotatef(angle, 0, 1, 0);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidTorus(3, 5, 3, 32);
    glPushMatrix();
        glTranslatef(0, 0, 2);
        glColor4f(0, 0.5, 0.8, 0.5);
        glutSolidSphere(4, 32, 32);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, -2.5);
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_TRIANGLES);
            for (int i = 0; i <= 32; i++){
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f((4 * cos(i*2*PI/32)),
                           (4 *sin(i*2*PI/32)), 0.0f);
                glVertex3f((4 * cos((i+1)*2*PI/32)),
                           (4 *sin((i+1)*2*PI/32)), 0.0f);
            }
        glEnd();
    glPopMatrix();
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0, 0.6, 0.0, 0.5);
        glTranslatef(-1, -1, -2.5);
        glutSolidSphere(0.5, 32, 32);
        glTranslatef(2, 0, 0);
        glutSolidSphere(0.5, 32, 32);
        glTranslatef(0, 2, 0);
        glutSolidSphere(0.5, 32, 32);
        glTranslatef(-2, 0, 0);
        glutSolidSphere(0.5, 32, 32);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}

void UFO::tickTime(long int elapseTime){
    if (animation){
        float elapseTimeInSec = elapseTime / 1000.0f;
        posx += elapseTimeInSec * velx;
        posy += elapseTimeInSec * vely;
        posz += elapseTimeInSec * velz;

        if(posx < -100 && posy > 60 && posz < -90){
            velx = vely = velz = 0;
            rot = true;
            angle += 10;
        }
    }
}

