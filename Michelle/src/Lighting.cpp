/*
CGLab11and12.cpp
Objective: Lab11 on Lighting &
Lab12 on Textures
INSTRUCTIONS
============
* Please refer to CGLabmain.cpp for instructions
CHANGE LOG
==========
*/
#include <GL/glut.h>

#include "../include/Lighting.hpp"
using namespace Lighting;

void YellowStar::init(){
    starLoader.load("D:/CG LABBBBBB/Michelle/data/star.txt", 0.05);
}
void YellowStar::setupLights()
{
    glLightfv(GL_LIGHT1, GL_AMBIENT, myyellow);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, myyellow);
    glLightfv(GL_LIGHT1, GL_SPECULAR, myyellow);
    glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);

    glEnable(GL_LIGHT1);
    lighton[0] = true;
}

//light 0 is a directional light
//lights 1,2,3 are lights 0,1,2 of spotlights
//lights 4,5 are lights 0,1 of swinglights
void YellowStar::toggleLight(int lightno)
{
    static GLenum tag[] = {GL_LIGHT1};
    lighton[lightno] = !lighton[lightno];
    if (lighton[lightno])
        glEnable( tag[lightno] );
    else
        glDisable( tag[lightno] );
}

void YellowStar::draw()
{
    static GLfloat position[] = {1.0f, 1.0f, 1.0f, 1.0f };
    static GLfloat direction[] = {0.0f, 0.0f, 0.0f, 1.0f };
    GLboolean cullingIsOn;
    glGetBooleanv(GL_CULL_FACE, &cullingIsOn);
    glDisable(GL_CULL_FACE);

    glPushMatrix();
        glTranslatef(20.0f, 10.0f, 12.0f);
        glColor3f(1.0f, 1.0f, 0.2f);
        starLoader.draw();
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);

    glPopMatrix();
    if (cullingIsOn==GL_TRUE)
        glEnable(GL_CULL_FACE);
}

void WhiteStar::init(){
    starLoader.load("D:/CG LABBBBBB/Michelle/data/star.txt", 0.05);
}
void WhiteStar::setupLights()
{
    glLightfv(GL_LIGHT2, GL_AMBIENT, mywhite);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, mywhite);
    glLightfv(GL_LIGHT2, GL_SPECULAR, mywhite);
    glLightf (GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf (GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5);

    glEnable(GL_LIGHT2);
    lighton[0] = true;
}

//light 0 is a directional light
//lights 1,2,3 are lights 0,1,2 of spotlights
//lights 4,5 are lights 0,1 of swinglights
void WhiteStar::toggleLight(int lightno)
{
    static GLenum tag[] = {GL_LIGHT2};
    lighton[lightno] = !lighton[lightno];
    if (lighton[lightno])
        glEnable( tag[lightno] );
    else
        glDisable( tag[lightno] );
}

void WhiteStar::draw()
{
    static GLfloat position[] = {1.0f, 1.0f, 1.0f, 1.0f };
    static GLfloat direction[] = {0.0f, 0.0f, 0.0f, 1.0f };
    GLboolean cullingIsOn;
    glGetBooleanv(GL_CULL_FACE, &cullingIsOn);
    glDisable(GL_CULL_FACE);

    glPushMatrix();
        glTranslatef(-20.0f, 5.0f, 2.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        starLoader.draw();
    glLightfv(GL_LIGHT2, GL_POSITION, position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);

    glPopMatrix();
    if (cullingIsOn==GL_TRUE)
        glEnable(GL_CULL_FACE);
}
