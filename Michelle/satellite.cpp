#include <GL/glut.h>
#include "satellite.hpp"
using namespace satellite;

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

void Satellite::tickTime(long int elapsedTime){
    bool reachEnd = false;
    if (reachEnd) {
        angle -= 0.1f;
    }
    else { angle = angle + 0.1f;}


    if (angle < -90.0f || angle > 90.0f ){
        reachEnd = true;
    }

}

void Satellite::draw(){
    glPushMatrix();
        glRotatef(angle, 0.5f, 0.2f, 0.5f);
        build();
    glPopMatrix();
}

void Satellite::build(){
    //drawTop, drawWing x 2, drawBody, drawBottom
    glPushMatrix();
        glTranslatef(0.0f, 8.5f, 0.0f);
        drawTop();
    glPopMatrix();
    //Left wing
    glPushMatrix();
        glTranslatef(0.0f, 3.0f, 1.5f);
        glScalef(1.2f, 1.5f, 1.2f);
        drawWing();
    glPopMatrix();
    //Right wing
    glPushMatrix();
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 3.0f, 1.5f);
        glScalef(1.2f, 1.5f, 1.2f);
        drawWing();
    glPopMatrix();

    glPushMatrix();
        glScalef(1.5f, 1.0f, 1.5f);
        drawBody();
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0f, 0.6f, 1.0f);
        glTranslatef(0.0f, -0.5f, 0.0f);
        drawBottom();
    glPopMatrix();
}

void Satellite::drawWing(){
    glDisable(GL_CULL_FACE);
    //Stem connecting the wing
    glPushMatrix();
        glTranslatef(0.0f, 2.5f, 0.0f);
        glColor3f(0.2f, 0.2f, 0.2f);
        gluCylinder(pObj, 0.1f, 0.1f, 2.0f, 24, 12);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 1.5f, 0.0f);
        glColor3f(0.2f, 0.2f, 0.2f);
        gluCylinder(pObj, 0.1f, 0.1f, 2.0f, 24, 12);
    glPopMatrix();
    //Wing
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 2.0f);
        glBegin(GL_QUADS);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 4.0f, 0.0f);
            glVertex3f(0.0f, 4.0f, 15.0f);
            glVertex3f(0.0f, 0.0f, 15.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();
    glPopMatrix();
    //Vertical lines
    for ( int x = 3; x < 17; x += 2){
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, x);
            glRotatef(-90, 1.0f, 0.0f, 0.0f);
            glColor3f(1.0f, 1.0f, 1.0f);
            gluCylinder(pObj, 0.1f, 0.1f, 4.0f, 24, 12);
        glPopMatrix();
    }
    //Horizontal line
    for ( int y = 1; y < 4; y += 2){
        glPushMatrix();
            glTranslatef(0.0f, y, 2.0f);
            glColor3f(1.0f, 1.0f, 1.0f);
            gluCylinder(pObj, 0.1f, 0.1f, 15.0f, 24, 12);
        glPopMatrix();
    }
    glEnable(GL_CULL_FACE);
}

void Satellite::drawTop(){
    glDisable(GL_CULL_FACE);
    //Big fan
    glPushMatrix();
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.0f, 7.0f, 4.0f, 24, 12);
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
void Satellite::drawBody(){
    glDisable(GL_CULL_FACE);
    //Top part
    glPushMatrix();
        glTranslatef(0.0f, 3.5f, 0.0f);
        drawTopBody();
    glPopMatrix();
    // Left Stem
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
        glTranslatef(0.75f, 2.25f, 1.3f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.1f, 0.1f, 1.5f, 24, 12);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.75f, 2.25f, 1.3f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.1f, 0.1f, 1.5f, 24, 12);
    glPopMatrix();
    // Right Stem
    glPushMatrix();
        glTranslatef(0.75f, 2.25f, -1.3f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.1f, 0.1f, 1.5f, 24, 12);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.75f, 2.25f, -1.3f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.1f, 0.1f, 1.5f, 24, 12);
    glPopMatrix();
    //Bottom part
    glPushMatrix();
        drawBottomBody();
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

void Satellite::drawTopBody(){
     glPushMatrix();
        glTranslatef(0.0f, 2.5f, 0.0f); //y = 2.75 at origin
        glScalef(3.0f, 5.0f, 3.0f);
        //Purple color
        float color[3] = { 1.0f, 0.0, 1.0f };
        drawCube(color);
     glPopMatrix();
}

void Satellite::drawBottomBody(){
    glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f); //y = 2.75 at origin
        glScalef(3.0f, 3.0f, 3.0f);
        //
        float color[3] = { 0.0f, 1.0f, 1.0f };
        drawCube(color);
     glPopMatrix();

}

// copy from https://www.wikihow.com/Make-a-Cube-in-OpenGL
void Satellite::drawCube(float color[3]){
    // FRONT
    glBegin(GL_POLYGON);
    glColor3f(  color[0], color[1], color[2] );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    // BACK
    glBegin(GL_POLYGON);
    glColor3f(  color[0], color[1], color[2] );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // RIGHT
    glBegin(GL_POLYGON);
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();

    // BOTTOM
    glBegin(GL_POLYGON);
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
}
