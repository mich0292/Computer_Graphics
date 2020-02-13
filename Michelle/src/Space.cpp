#include <GL/glut.h>
#include <cmath>
#include "../include/Space.hpp"
using namespace Space;

SpaceHotel::SpaceHotel(){
    qObj = gluNewQuadric();
    gluQuadricNormals(qObj, GLU_SMOOTH);
}

void SpaceHotel::drawConnector(){
    glTranslatef(0, 8, 0);
    glRotatef(-90, 1, 0, 0);
        gluCylinder(qObj, 0.75, 0.75, 2, 32, 32);
    glTranslatef(0, -1, 0);
        gluCylinder(qObj, 0.25, 0.25, 2, 32, 32);
    glTranslatef(0, 2, 0);
        gluCylinder(qObj, 0.25, 0.25, 2, 32, 32);
}

void SpaceHotel::draw(){
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
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f((8 * cos(i*2*PI/32)),
                           (8 *sin(i*2*PI/32)), 0.0f);
                glVertex3f((8 * cos((i+1)*2*PI/32)),
                           (8 *sin((i+1)*2*PI/32)), 0.0f);
            }
        glEnd();
        glTranslatef(0, 0, 2);
        glBegin(GL_TRIANGLES);
            for (int i = 0; i <= 32; i++){
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f((8 * cos(i*2*PI/32)),
                           (8 *sin(i*2*PI/32)), 0.0f);
                glVertex3f((8 * cos((i+1)*2*PI/32)),
                           (8 *sin((i+1)*2*PI/32)), 0.0f);
            }
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 8, 0);
        glRotatef(-90, 1, 0, 0);
            gluCylinder(qObj, 1, 1, 2, 32, 32);
    glPopMatrix();
    float angle = 90;
        for (int i = 0; i < 4; i++){
            glPushMatrix();
                drawConnector();
            glPopMatrix();
            glRotatef(angle, 0, 0, 1);
            angle += 90;
        }
    glEnable(GL_CULL_FACE);
}

void UFO::draw(){
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
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}
