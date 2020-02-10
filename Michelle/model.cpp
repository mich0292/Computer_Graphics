#include <GL/glut.h>
#include "satellite.hpp"
using namespace model;

Satellite::Satellite()
{
    //Setup Quadric Object
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
}

Satellite::~Satellite()
{
    gluDeleteQuadric(pObj);
}

void Satellite::draw(){

}

void Satellite::drawWing(){

}

void Satellite::drawTop(){
    glDisable(GL_CULL_FACE);
    //Big fan
    glPushMatrix();
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.5f, 7.0f, 4.0f, 24, 12);
    glPopMatrix();
    //Inside fan
    glPushMatrix();
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.2f, 1.2f, 2.5f, 24, 12);
    glPopMatrix();
    //Extend stems
    for ( int i= 1; i <=3; i++ ){
        glPushMatrix();
            glRotatef(i*120, 0.0f, 1.0f, 0.0f);
            glTranslatef(0.0f, 4.1f, 0.7f);
            drawTopStem();
        glPopMatrix();
    }
    //Top disk
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 8.6f, 0.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, 0.0f, 1.0f, 24, 12);
    glPopMatrix();
    //Diamond on top disk
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 8.6f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.7f, 0.0f, 0.8f, 24, 12);
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

void Satellite::drawTopStem(){
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
        glTranslatef(0.0f, 4.5f, 0.0f);
        glRotatef(15, 0.0f, 1.0f, 0.0f);
        glRotatef(45, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.1f, 0.1f, 7.5f, 24, 12);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 4.5f, 0.0f);
        glRotatef(-15, 0.0f, 1.0f, 0.0f);
        glRotatef(45, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.1f, 0.1f, 7.5f, 24, 12);
    glPopMatrix();
}

void Satellite::drawBottom(){
    //Inside stem
     glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.8f, 0.8f, 5.0f, 24, 12);
    glPopMatrix();
    //Outside top stem
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.0f, 1.0f, 1.5f, 24, 12);
    glPopMatrix();
    //Outside bottom stem
    glPushMatrix();
        glTranslatef(0.0f, -2.0f, 0.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.0f, 1.0f, 2.5f, 24, 12);
    glPopMatrix();
    //Bottom fan
    glPushMatrix();
        glTranslatef(0.0f, -5.0f, 0.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.0f, 2.0f, 3.0f, 24, 12);
    glPopMatrix();
}

