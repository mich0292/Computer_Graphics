#include "World.hpp"
using namespace World;


/******************************************************************************
*************   	      	 MyVirtualWorld				    	  *************
******************************************************************************/
void MyVirtualWorld::draw()
{
    ///Prometheus
    /*
    glPushMatrix();
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        prometheusloader.draw(0, 1, 0, 0, GL_TRUE);
    glPopMatrix();*/

    glPushMatrix();

        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        spaceshiploader.draw(0, 1, 0, 0, GL_TRUE);
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
    ///prometheusloader.setupLights();
    spaceshiploader.setupLights();
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
}

