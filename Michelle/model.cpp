#include <GL/glut.h>
#include "model.hpp"
using namespace model;

Planet::Planet()
{
    //Setup Quadric Object
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
}

Planet::~Planet()
{
    gluDeleteQuadric(pObj);
}
void Planet::draw()
{
    glDisable(GL_CULL_FACE);
    srand(1); //initialize the random number generator
    glColor3f (1.0f, 0.0f, 0.0f);
    glPushMatrix();
         gluSphere(pObj, 4.5f, 24, 12);
    glPopMatrix();
    glPushMatrix();
        glColor3f (1.0f, 0.5f, 0.72f);
        glRotatef(60, 1.0f, 0, 0.0f);
        gluDisk(pObj, 6.0f, 7.5f, 24, 12);
        glRotatef(40, 1.0f, 0, 0.0f);
        gluDisk(pObj, 6.0f, 7.5f, 24, 12);
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

Rocket::Rocket()
{
    //Setup Quadric Object
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
}

Rocket::~Rocket()
{
    gluDeleteQuadric(pObj);
}
void Rocket::draw()
{
    glDisable(GL_CULL_FACE);
    srand(1); //initialize the random number generator
    glColor3f (0.2f, 0.2f, 0.2f);
    //Body of rocket
    glPushMatrix();
         glRotatef(-90, 1.0f, 0.0f, 0.0f);
         gluCylinder(pObj, 5.0f, 5.0f, 18.0f, 36, 24);
    glPopMatrix();
    //Cap of rocket
    glPushMatrix();
        glTranslatef(0.0f, 18.0f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 5.0f, 0.0f, 4.0f, 24,12);
    glPopMatrix();
    //Window
    glPushMatrix();
        glColor3f (1.0f, 0.5f, 0.72f);
        glTranslatef(0.0f, 11.0f, -6.0f);
        gluCylinder(pObj, 2.0f, 2.0f, 12.0f, 36, 24);
    glPopMatrix();
    //Bottom fan
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 3.0f, 6.0f, 3.0f, 24, 12);
    glPopMatrix();
    //Four fins
        for (int i = 0; i < 4; i++){
            glPushMatrix();
            glRotatef(i*90+45, 0.0f, 1.0f, 0.0f);
            glTranslatef(0.0f, 0.0f, 5.0f);
            drawFin();
            glPopMatrix();
        }
    glEnable(GL_CULL_FACE);
}

void Rocket::drawFin(){
    glBegin(GL_TRIANGLE_FAN);
    glPushMatrix();
        glVertex3f( 0.0f, -2.0f, 7.5f );
        glVertex3f( 0.0f, 0.0f, 0.0f );
        glVertex3f( 0.0f, 6.0f, 0.0f );
    glPopMatrix();
    glEnd();
}

Satellite1::Satellite1()
{
    //Setup Quadric Object
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
}

Satellite1::~Satellite1()
{
    gluDeleteQuadric(pObj);
}

void Satellite1::draw(){
    glDisable(GL_CULL_FACE);
    srand(1); //initialize the random number generator
    glColor3f (1.0f, 0.5f, 0.72f);
    //Body of satellite
    gluQuadricDrawStyle(pObj, GLU_FILL);
    glPushMatrix();
        gluSphere(pObj, 6.0f, 36, 12);
    glPopMatrix();
    //top two disks
    glPushMatrix();
        drawDisk();
    glPopMatrix();
    //bottom two disks
    glPushMatrix();
        glRotatef(180, 0.0f, 0.0f, 1.0f);
        drawDisk();
    glPopMatrix();
    //draw two sides
    glPushMatrix();
        for ( int i = 1; i <= 2; i++){
            glRotatef(i*90, 0.0f, 1.0f, 0.0f);
            drawSide();
        }
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

void Satellite1::drawSide(){
    gluQuadricDrawStyle(pObj, GLU_FILL);
    glColor3f (0.2f, 0.2f, 0.2f);
    //Stem
    glPushMatrix();
        gluCylinder(pObj, 0.2f, 0.2f, 18.0f, 24, 12);
    glPopMatrix();
    //Point upward
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 14.0f);
        glRotatef(-45, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.2f, 0.2f, 4.5f, 24, 12);
    glPopMatrix();
    //Point downward
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 14.0f);
        glRotatef(-315, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.2f, 0.2f, 4.5f, 24, 12);
    glPopMatrix();
    //Down small stem
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 16.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.2f, 0.2f, 2.0f, 24, 12);
    glPopMatrix();
    //Top small stem
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 16.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.2f, 0.2f, 2.0f, 24, 12);
    glPopMatrix();
}

void Satellite1::drawDisk(){
    glColor3f (0.5f, 0.2f, 0.2f);
    gluQuadricDrawStyle(pObj, GLU_LINE);
    glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, 6.0f, 7.5f, 36, 12);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 3.5f, 0.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, 4.5f, 6.0f, 36, 12);
    glPopMatrix();
}

Satellite2::Satellite2()
{
    //Setup Quadric Object
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
}

Satellite2::~Satellite2()
{
    gluDeleteQuadric(pObj);
}

void Satellite2::draw(){

}

void Satellite2::drawWing(){

}

void Satellite2::drawTop(){
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

void Satellite2::drawTopStem(){
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

void Satellite2::drawBottom(){
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

