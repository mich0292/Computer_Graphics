#include <GL/glut.h>
#include "../include/FJModel.hpp"
using namespace FJModel;

/******************************************************************************
*************   	      		  SpaceStation			    	  *************
******************************************************************************/
SpaceStation::SpaceStation(){
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj,GLU_SMOOTH);
    angle = 45.0;
}

SpaceStation::~SpaceStation(){
    gluDeleteQuadric(pObj);
}

void SpaceStation::draw(){
    glPushMatrix();
    glRotatef(-45.0, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -60.0f);
    drawBody();
    drawSolarPanel();
    glPopMatrix();
}

void SpaceStation::drawSolarPanel(){
    glDisable(GL_CULL_FACE);
    glColor3f(0.0f, 0.0f, 1.0f);
    //left solar panel
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 11.3f, 25.0f);
    glVertex3f(0.0f, 11.3f, 23.0f);
    glVertex3f(0.0f, 2.0f, 23.0f);
    glVertex3f(0.0f, 2.0f, 25.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 11.3f, 28.0f);
    glVertex3f(0.0f, 11.3f, 25.5f);
    glVertex3f(0.0f, 2.0f, 25.5f);
    glVertex3f(0.0f, 2.0f, 28.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, -2.0f, 23.0f);
    glVertex3f(0.0f, -2.0f, 25.0f);
    glVertex3f(0.0f, -11.3f, 25.0f);
    glVertex3f(0.0f, -11.3f, 23.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, -2.0f, 25.5f);
    glVertex3f(0.0f, -2.0f, 28.0f);
    glVertex3f(0.0f, -11.3f, 28.0f);
    glVertex3f(0.0f, -11.3f, 25.5f);
    glEnd();
    glPopMatrix();

    //right solar panel
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 11.3f, -21.0f);
    glVertex3f(0.0f, 11.3f, -18.5f);
    glVertex3f(0.0f, 2.0f, -18.5f);
    glVertex3f(0.0f, 2.0f, -21.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, 11.3f, -16.0f);
    glVertex3f(0.0f, 11.3f, -18.0f);
    glVertex3f(0.0f, 2.0f, -18.0f);
    glVertex3f(0.0f, 2.0f, -16.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, -2.0f, -21.0f);
    glVertex3f(0.0f, -2.0f, -18.5f);
    glVertex3f(0.0f, -11.3f, -18.5f);
    glVertex3f(0.0f, -11.3f, -21.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, -2.0f, -16.0f);
    glVertex3f(0.0f, -2.0f, -18.0f);
    glVertex3f(0.0f, -11.3f, -18.0f);
    glVertex3f(0.0f, -11.3f, -16.0f);
    glEnd();
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

void SpaceStation::drawBody(){
    glDisable(GL_CULL_FACE);

    //-----------------------stick link to solar panel (left)---------------------------------
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.5f, 24.0f);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    gluCylinder(pObj, 0.1f, 0.1f, 1.5f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(0.0f, -0.5f, 24.0f);
    glRotatef(-45.0, 1.0, 0.0, 0.0);
    gluCylinder(pObj, 0.1f, 0.1f, 1.5f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 1.5f, 25.3f);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.3f, 0.3f, 3.0f, 26, 13);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 11.5f, 25.3f);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.1f, 0.1f, 10.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -1.5f, 25.3f);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.1f, 0.1f, 10.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 11.5f, 23.0f);
    gluCylinder(pObj, 0.1f, 0.1f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 1.8f, 23.0f);
    gluCylinder(pObj, 0.1f, 0.1f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -1.8f, 23.0f);
    gluCylinder(pObj, 0.1f, 0.1f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -11.5f, 23.0f);
    gluCylinder(pObj, 0.1f, 0.1f, 5.0f, 26, 13);
    glPopMatrix();
    //-----------------------main body--------------------------------
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 20.0f);
    gluCylinder(pObj, 2.0f, 1.0f, 4.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 18.0f);
    gluCylinder(pObj, 3.0f, 2.0f, 2.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 8.0f);
    gluCylinder(pObj, 3.0f, 3.0f, 10.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 6.0f);
    gluCylinder(pObj, 2.0f, 3.0f, 2.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    gluCylinder(pObj, 2.0f, 2.0f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    gluCylinder(pObj, 3.0f, 2.0f, 2.0f, 26, 13); //base face -z
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -11.0f);
    gluCylinder(pObj, 3.0f, 3.0f, 10.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -13.0f);
    gluCylinder(pObj, 2.0f, 3.0f, 2.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -17.0f);
    gluCylinder(pObj, 1.0f, 2.0f, 4.0f, 26, 13);
    glPopMatrix();

    //-----------------------stick link to solar panel (right)---------------------------------
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    if (g_rotate)
        glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.5f, -18.0f);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    gluCylinder(pObj, 0.1f, 0.1f, 1.5f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(0.0f, -0.5f, -18.0f);
    glRotatef(-45.0, 1.0, 0.0, 0.0);
    gluCylinder(pObj, 0.1f, 0.1f, 1.5f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 1.5f, -18.3f);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.3f, 0.3f, 3.0f, 26, 13);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 11.5f, -18.3f);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.1f, 0.1f, 10.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -1.5f, -18.3f);
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.1f, 0.1f, 10.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 11.5f, -20.8);
    gluCylinder(pObj, 0.1f, 0.1f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 1.8f, -20.8f);
    gluCylinder(pObj, 0.1f, 0.1f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -1.8f, -20.8f);
    gluCylinder(pObj, 0.1f, 0.1f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    if (g_rotate)
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -11.5f, -20.8f);
    gluCylinder(pObj, 0.1f, 0.1f, 5.0f, 26, 13);
    glPopMatrix();

    glEnable(GL_CULL_FACE);
}

void SpaceStation::tickTime(long int elapsedTime){
    angle = angle + 0.1;
    if((angle-360) <= 0.001 && (angle-360) > 0)
        angle = 0.0;
}

/******************************************************************************
*************   	        		  Rocket		 	    	  *************
******************************************************************************/
Rocket::Rocket(){
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj,GLU_SMOOTH);
}

Rocket::~Rocket(){
    gluDeleteQuadric(pObj);
}

void Rocket::draw(){
    glPushMatrix();
    glTranslatef(-12.0f, 3.5f, 20.0f);
    drawTop();
    drawBody();
    drawBottom();
    glPopMatrix();
}

void Rocket::drawTop(){
    glDisable(GL_CULL_FACE);

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0.0f,17.5f,0.0f);
    glRotatef(-90,1.0f,0.0f,0.0f);
    gluCylinder(pObj, 2.0f, 0.0f, 5.0f, 26, 13);
    glPopMatrix();

    glEnable(GL_CULL_FACE);
}

void Rocket::drawBody(){
    glDisable(GL_CULL_FACE);
    glColor3f(0.955f, 0.637f, 0.538f);
    glPushMatrix();
    glTranslatef(0.0f,14.5f,0.0f);
    glRotatef(-90,1.0,0.0,0.0);
    gluCylinder(pObj, 2.0f, 2.0f, 3.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,12.5f,0.0f);
    glRotatef(-90,1.0,0.0,0.0);
    gluCylinder(pObj, 3.0f, 2.0f, 2.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,-2.5f,0.0f);
    glRotatef(-90,1.0,0.0,0.0);
    gluCylinder(pObj, 3.0f, 3.0f, 15.0f, 26, 13);
    glPopMatrix();

    glEnable(GL_CULL_FACE);
}

void Rocket::drawBottom(){
    glDisable(GL_CULL_FACE);

    glPushMatrix();
    glColor3f(1.0,0,0);
    glTranslatef(-1.5f,-5.5f,2.0f);
    glRotatef(-90,1.0,0.0,0.0);
    gluCylinder(pObj, 1.5f, 0.5f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f,-5.5f,2.0f);
    glRotatef(-90,1.0,0.0,0.0);
    gluCylinder(pObj, 1.5f, 0.5f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f,-5.5f,-2.0f);
    glRotatef(-90,1.0,0.0,0.0);
    gluCylinder(pObj, 1.5f, 0.5f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f,-5.5f,-2.0f);
    glRotatef(-90,1.0,0.0,0.0);
    gluCylinder(pObj, 1.5f, 0.5f, 5.0f, 26, 13);
    glPopMatrix();

    glEnable(GL_CULL_FACE);
}
