#include "World.hpp"
using namespace World;


/******************************************************************************
*************   	      	 MyVirtualWorld				    	  *************
******************************************************************************/
void MyVirtualWorld::draw()
{
    ///Satellite
    glPushMatrix();
        glTranslatef(60.0f, 25.0f, -15.0f);
        glRotatef(50, 0.0f, 0.0f, 1.0f);
        glScalef(0.4f, 0.4f, 0.4f);
        satellite.draw();
    glPopMatrix();
    ///Capsule
    glPushMatrix();
        glTranslatef(6.0f, -0.9f, 25.0f);
        //glRotatef(-5, 0.0f, 0.0f, 1.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        capsuleloader.draw();
    glPopMatrix();
    ///Rocket
     glPushMatrix();
        glRotatef(-10, 0.0f, 0.0f, 1.0f);
        glTranslatef(20.0f, 0.0f, 8.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        rocket.draw();
    glPopMatrix();
    ///Planet
    glPushMatrix();
        glTranslatef(7.0f, -30.0f, 20.0f);
        glScalef(22.0f, 22.0f, 22.0f);
        planet.draw();
    glPopMatrix();
    ///Globe
    glPushMatrix();
        glTranslatef(-60.0f, 20.0f, -50.0f);
        glScalef(8.0f, 8.f, 8.0f);
        globe.draw();
    glPopMatrix();
    ///Satellite Model
    glPushMatrix();
        glTranslatef(-45.0f, 20.0f, -50.0f);
        satelliteloader.draw(1, 0, 0, 5);
    glPopMatrix();
    ///Prometheus
    glPushMatrix();
        glTranslatef(35.0f, 40.0f, -35.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        prometheusloader.draw(0, 1, 0, 0, GL_TRUE);
    glPopMatrix();
    ///Station
    glPushMatrix();
        glTranslatef(-80.0f, -10.0f, 20.0f);
        glScalef(0.4f, 0.4f, 0.4f);
        station.draw();
    glPopMatrix();
    ///Tyderium (ship)
    glPushMatrix();
        glTranslatef(-20.0f, 3.0f, -240.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        tyderiumloader.draw(0, -1, 0, 0, GL_TRUE);
    glPopMatrix();
     ///Station (MKII)
    glPushMatrix();
        glTranslatef(-20.0f, 4.0f, -270.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        stationloader.draw(0, 1, 0, 5);
    glPopMatrix();
    ///LIGHTS
    glPushMatrix();
        yellowStar.draw();
    glPopMatrix();
    glPushMatrix();
        whiteStar.draw();
    glPopMatrix();
    glPushMatrix();
        point.draw();
    glPopMatrix();

    ///Hotel
    glPushMatrix();
        glTranslatef(20, 20, -20);
        glRotatef(-45, 1, 0, 0);
        glScalef(0.5, 0.5, 0.5);
        hotel.draw();
    glPopMatrix();

    ///UFO
    glPushMatrix();
        glTranslatef(50, -6, 50);
        glScalef(0.4, 0.4, 0.4);
        ufo.draw();
    glPopMatrix();
}

void MyVirtualWorld::setupLights()
{
    glEnable(GL_LIGHTING);
    //GL_COLOR_MATERIAL
    // * relevant only if lighting is enabled
    // * disabled by default
    // * if enabled, glColor*(...) is in effect to change the color
    // tracked by glColorMaterial
    // (meaning that in our case here, glColor*(...) affect
    // the diffuse color of the frant face)
    // * if disbled, glMaterial*(...) is in effect to change the color
    // glColor*(...) will not work!
    //glColor*(...) always in effect if lighting is not enabled
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //ensure unit vectors remain unit vectors after
    // modelview scaling
    glEnable(GL_NORMALIZE);
    //define the color of light, i.e. LIGHT0
    GLfloat mycolor[] = { 0.50, 0.50, 0.50};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, mycolor);

    //enable the light, i.e. LIGHT0
    glEnable(GL_LIGHT0);
    yellowStar.setupLights();
    whiteStar.setupLights();
    capsuleloader.setupLights();
    prometheusloader.setupLights();
    satelliteloader.setupLights();
    point.setupLights();
    for (int i=0; i<7; ++i)
        lighton[i] = true;
}

void MyVirtualWorld::toggleLight(int lightno)
{
    if (lightno==0)
    {
        lighton[0] = !lighton[0];
        if (lighton[0])
            glEnable( GL_LIGHT0 );
        else
            glDisable( GL_LIGHT0 );
    }
    else if (lightno==1)
    {
        yellowStar.toggleLight();
    }
    else if (lightno==2)
    {
        whiteStar.toggleLight();
    }
    else if (lightno==3)
    {
       point.toggleLight();
    }
}
