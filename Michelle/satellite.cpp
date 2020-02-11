#include "satellite.hpp"
using namespace satellite;

Globe::Globe(){
    // set the GL clear color - use when the color buffer is cleared
    glClearColor( 0.0f, 0.0f,0.0f, 0 );
    // set the shading model to 'smooth'
    glShadeModel( GL_SMOOTH );

    // enable depth
    glEnable( GL_DEPTH_TEST );
    // set the front faces of polygons
    glFrontFace( GL_CCW );
    // cull faces
    glEnable( GL_CULL_FACE );

    // set the initial line width
    glLineWidth( 1.0f );

    // enable lighting
    glEnable( GL_LIGHTING );
    // enable lighting for front
    glLightModeli( GL_FRONT, GL_TRUE );
    // material have diffuse and ambient lighting
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    // enable color
    glEnable( GL_COLOR_MATERIAL );
    // enable light 0
    glEnable( GL_LIGHT0 );

    // initialize our sphere
    g_sphere = gluNewQuadric( );
    gluQuadricNormals( g_sphere, ( GLenum )GLU_SMOOTH );
    gluQuadricTexture( g_sphere, GL_TRUE );

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

void Globe::draw() {
    static GLfloat x = 0.0f;
    // clear the color and depth buffers
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if( g_img )
    {
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, g_img );
    }

    // save the current matrix
    glPushMatrix( );

        // rotate the planet
        glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
        glRotatef( x, 0.0f, 0.0f, 1.0f );
        x += .4f;

        // draw the sphere
        glColor3f( 1.0f, 1.0f, 1.0f );
        gluSphere( g_sphere, 1.28f, 24, 24 );

    glPopMatrix( );

    if( g_img )
        glDisable( GL_TEXTURE_2D );

    glFlush( );
    //glutSwapBuffers( );
}

bool Globe::ge_read_image( const char * filename, GeImageData * pImgData )
{
    int c;
    if( !filename || !pImgData )
        return false;

    // zero out the memory
    memset( pImgData, 0, sizeof( GeImageData ) );

    pImgData->bits = ge_read_rgb( filename, &pImgData->width, &pImgData->height, &c );

    return ( pImgData->bits != 0 );
}

//-----------------------------------------------------------------------------
/* texture loading - by David Blythe, SGI */
/* a simplistic routine for reading an SGI .rgb image file. */
//-----------------------------------------------------------------------------

void Globe::bwtorgba(unsigned char *b,unsigned char *l,int n) {
    while(n--) {
        l[0] = *b;
        l[1] = *b;
        l[2] = *b;
        l[3] = 0xff;
        l += 4; b++;
    }
}

void Globe::rgbtorgba(unsigned char *r,unsigned char *g,unsigned char *b, unsigned char *l,int n) {
    while(n--) {
        l[0] = r[0];
        l[1] = g[0];
        l[2] = b[0];
        l[3] = 0xff;
        l += 4; r++; g++; b++;
    }
}

void Globe::rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b, unsigned char *a,unsigned char *l,int n) {
    while(n--) {
        l[0] = r[0];
        l[1] = g[0];
        l[2] = b[0];
        l[3] = a[0];
        l += 4; r++; g++; b++; a++;
    }
}

unsigned* Globe::ge_read_rgb( const char * name, int * width, int * height,int * components) {

    unsigned *base, *lptr;
    unsigned char *rbuf, *gbuf, *bbuf, *abuf;
    ImageRec *image;
    int y;

    image = ImageOpen(name);

    if(!image)
        return NULL;
    (*width)=image->xsize;
    (*height)=image->ysize;
    (*components)=image->zsize;
    base = (unsigned *)malloc(image->xsize*image->ysize*sizeof(unsigned));
    rbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
    gbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
    bbuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
    abuf = (unsigned char *)malloc(image->xsize*sizeof(unsigned char));
    if(!base || !rbuf || !gbuf || !bbuf)
        return NULL;
    lptr = base;
    for(y=0; y<image->ysize; y++) {
        if(image->zsize>=4) {
            ImageGetRow(image,rbuf,y,0);
            ImageGetRow(image,gbuf,y,1);
            ImageGetRow(image,bbuf,y,2);
            ImageGetRow(image,abuf,y,3);
            rgbatorgba(rbuf,gbuf,bbuf,abuf,
              (unsigned char *)lptr,image->xsize);
            lptr += image->xsize;
        } else if(image->zsize==3) {
            ImageGetRow(image,rbuf,y,0);
            ImageGetRow(image,gbuf,y,1);
            ImageGetRow(image,bbuf,y,2);
            rgbtorgba(rbuf,gbuf,bbuf,(unsigned char *)lptr,image->xsize);
            lptr += image->xsize;
        } else {
            ImageGetRow(image,rbuf,y,0);
            bwtorgba(rbuf,(unsigned char *)lptr,image->xsize);
            lptr += image->xsize;
        }
    }
    ImageClose(image);
    free(rbuf);
    free(gbuf);
    free(bbuf);
    free(abuf);

    return (unsigned *) base;
}

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
