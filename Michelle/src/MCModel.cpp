#include <GL/glut.h>
#include <iostream>
#include <string>
#include <fstream>
#include "../include/MCModel.hpp"
using namespace MCModel;
/******************************************************************************
*************   	      		  Globe					    	  *************
******************************************************************************/
Globe::Globe()
{
    // initialize our sphere
    g_sphere = gluNewQuadric( );
    gluQuadricNormals( g_sphere, ( GLenum )GLU_SMOOTH );
    gluQuadricTexture( g_sphere, GL_TRUE );
}
void Globe::init()
{
    // set the shading model to 'smooth'
    glShadeModel( GL_SMOOTH );

    // set the initial line width
    glLineWidth( 1.0f );

    // set texture state
    glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    // read the texture
    if( !ge_read_image( g_filename, &g_imgData ) )
    {
        printf( "couldn't open file '%s'...\n", g_filename );
        printf( "usage: globe <filename>.rgb\n" );
        exit(1);
    }

    // generate OpenGL texture
    glGenTextures( 1, &g_img );
    glBindTexture( GL_TEXTURE_2D, g_img );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, g_imgData.width, g_imgData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, g_imgData.bits );
}

Globe::~Globe()
{
    gluDeleteQuadric(g_sphere);
}

void Globe::draw()
{
    static GLfloat x = 0.0f;
    // clear the color and depth buffers
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if( g_img && g_texture)
    {
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, g_img );
    }

    // save the current matrix
    glPushMatrix( );
    if (g_rotate)
    {
        // rotate the planet
        glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
        glRotatef( x, 0.0f, 0.0f, 1.0f );
        x += .4f;
    }

    // draw the sphere
    glColor3f( 1.0f, 1.0f, 1.0f );
    gluSphere( g_sphere, 1.28f, 24, 24 );

    glPopMatrix( );

    if( g_img )
        glDisable( GL_TEXTURE_2D );

    glFlush( );
    //glutSwapBuffers( );
}
/******************************************************************************
*************   	      		  Planet				    	  *************
******************************************************************************/
Planet::Planet()
{
    // initialize our sphere
    g_sphere = gluNewQuadric( );
    gluQuadricNormals( g_sphere, ( GLenum )GLU_SMOOTH );
    gluQuadricTexture( g_sphere, GL_TRUE );

}
void Planet::init()
{
    // set the shading model to 'smooth'
    glShadeModel( GL_SMOOTH );

    // set the initial line width
    glLineWidth( 1.0f );

    // set texture state
    glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    // read the texture
    if( !ge_read_image( g_filename, &g_imgData ) )
    {
        printf( "couldn't open file '%s'...\n", g_filename );
        printf( "usage: globe <filename>.rgb\n" );
        exit(1);
    }

    // generate OpenGL texture
    glGenTextures( 1, &g_img );
    glBindTexture( GL_TEXTURE_2D, g_img );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, g_imgData.width, g_imgData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, g_imgData.bits );
}

Planet::~Planet()
{
    gluDeleteQuadric(g_sphere);
}

void Planet::draw()
{
    static GLfloat x = 0.0f;
    // clear the color and depth buffers
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if( g_img && g_texture)
    {
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, g_img );
    }


    glPushMatrix( );

    if (g_rotate)
    {
        // rotate the planet
        glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
        glRotatef( x, 0.0f, 0.0f, 1.0f );
        x += .02f;
    }

    // draw the sphere
    glColor3f( 1.0f, 1.0f, 1.0f );
    gluSphere( g_sphere, 1.28f, 24, 24 );

    glPopMatrix( );

    if( g_img )
        glDisable( GL_TEXTURE_2D );

    glFlush( );
    //glutSwapBuffers( );
}


/******************************************************************************
*************   	      		  Satellite				    	  *************
******************************************************************************/
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

void Satellite::tickTime(long int elapsedTime)
{
    if (g_rotate)
        angle = angle + 0.01f;
}

void Satellite::draw()
{
    glPushMatrix();
    glRotatef(angle, 0.5f, 0.2f, 0.5f);
    build();
    glPopMatrix();
}

void Satellite::build()
{
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

void Satellite::drawWing()
{
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
    for ( int x = 3; x < 17; x += 2)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, x);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        gluCylinder(pObj, 0.1f, 0.1f, 4.0f, 24, 12);
        glPopMatrix();
    }
    //Horizontal line
    for ( int y = 1; y < 4; y += 2)
    {
        glPushMatrix();
        glTranslatef(0.0f, y, 2.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        gluCylinder(pObj, 0.1f, 0.1f, 15.0f, 24, 12);
        glPopMatrix();
    }
    glEnable(GL_CULL_FACE);
}

void Satellite::drawTop()
{
    glDisable(GL_CULL_FACE);
    //Big fan
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 1.0f, 7.0f, 4.0f, 24, 12);
    glPopMatrix();
    //Inside fan
    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.2f, 1.2f, 2.5f, 24, 12);
    glPopMatrix();
    //Extend stems
    for ( int i= 1; i <=3; i++ )
    {
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

void Satellite::drawBottom()
{
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
void Satellite::drawBody()
{
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

void Satellite::drawTopBody()
{
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f); //y = 2.75 at origin
    glScalef(3.0f, 5.0f, 3.0f);
    //Purple color
    float color[3] = { 1.0f, 0.0, 1.0f };
    drawCube(color);
    glPopMatrix();
}

void Satellite::drawBottomBody()
{
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); //y = 2.75 at origin
    glScalef(3.0f, 3.0f, 3.0f);
    //
    float color[3] = { 0.0f, 1.0f, 1.0f };
    drawCube(color);
    glPopMatrix();

}

// copy from https://www.wikihow.com/Make-a-Cube-in-OpenGL
void Satellite::drawCube(float color[3])
{
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

/******************************************************************************
*************   	      	 MyModelLoader				    	  *************
******************************************************************************/
void MyModelLoader::computeSurfaceNormal( GLfloat vertex1[],
                           GLfloat vertex2[],
                           GLfloat vertex3[],
                           GLfloat normal[])
{
    GLfloat v1[3], v2[3];
    v1[0] = vertex3[0] - vertex2[0];
    v1[1] = vertex3[1] - vertex2[1];
    v1[2] = vertex3[2] - vertex2[2];
    v2[0] = vertex1[0] - vertex2[0];
    v2[1] = vertex1[1] - vertex2[1];
    v2[2] = vertex1[2] - vertex2[2];
    normal[0] = v1[1]*v2[2] - v1[2]*v2[1];
    normal[1] = v1[2]*v2[0] - v1[0]*v2[2];
    normal[2] = v1[0]*v2[1] - v1[1]*v2[0];
    GLfloat magnitude = sqrt(   normal[0]*normal[0]
                                + normal[1]*normal[1]
                                + normal[2]*normal[2] );
    normal[0] /= magnitude;
    normal[1] /= magnitude;
    normal[2] /= magnitude;
}

void MyModelLoader::load(string filename, float scale, float color1, float color2, float color3)
{
    int numberOfVertices;
    int numberOfFaces;
    ifstream fin;
    fin.open(filename.c_str());

    if (fin.good())
    {
        fin >> numberOfVertices;
        fin >> numberOfFaces;
        int varraysize = numberOfVertices*3;
        vertices.reserve(varraysize);
        //Put dummy element for vertices [0],[1],[2]
        faces.reserve(numberOfFaces*65); //this is just the minimum

        float coord;
        for (int i=0; i<varraysize && fin.good(); i++)
        {
            fin >> coord;
            vertices.push_back(coord*scale);
        }
        int vcount,index;
        for (int i=0; i<numberOfFaces && fin.good(); ++i)
        {
            fin >> vcount;
            faces.push_back(vcount);
            for (int j=0; j<vcount && fin.good(); ++j)
            {
                fin >> index;
                faces.push_back(index);
            }
        }
        fin.close();
    }

    vector<int>::iterator itr;
    GLfloat normal[3];

    stanforddragon = glGenLists(1);
    glNewList(stanforddragon, GL_COMPILE);
    //glColor3f(1.0f, 0.8f, 0.4f);
    glColor3f(color1, color2, color3);
    int vcount;  //number of vertices for a particular polygon
    for (itr = faces.begin(); itr!=faces.end();)
    {
        vcount = *itr;  //first element of faces (number of vertices)
        itr++; //second element of faces (first face)
        int i1, i2, i3;
        i1 = (*itr)     * 3; // 24
        i2 = (*(itr+1)) * 3; // 27
        i3 = (*(itr+2)) * 3; // 33

        computeSurfaceNormal( &vertices[i1],&vertices[i2],&vertices[i3], normal );
        glBegin(GL_POLYGON);
        glNormal3fv(normal);
        for (int k=0; k<vcount; k++)
        {
            glVertex3fv( &vertices[(*itr)*3] );
            itr++;
        }
        glEnd();
    }
    glEndList();
}

void MyModelLoader::draw(float x, float y, float z, float angle, GLboolean movingFlag)
{
    glDisable(GL_CULL_FACE);
        if (angle && g_movement)
            glRotatef(angle*movement, x, y, z);
        if ( movingFlag && g_movement)
            glTranslatef(x*movement, y*movement, z*movement);
        glCallList(stanforddragon);
    glEnable(GL_CULL_FACE);
}

void MyModelLoader::tickTime(long int elapsedTime, float speed){
    movement = movement + 0.05 + speed;
}

void MyModelLoader::setupLights(){
    static GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    short shininess = 80;

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, shininess);
}
