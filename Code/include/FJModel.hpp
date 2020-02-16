#ifndef FJMODEL_HPP
#define FJMODEL_HPP

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
namespace FJModel{

class SpaceStation{
private:
    GLUquadricObj *pObj;
    GLfloat angle;
    GLboolean g_rotate = GL_TRUE;

public:
    SpaceStation();
    ~SpaceStation();
    void draw();
    void drawBody();
    void drawSolarPanel();
    void tickTime(long int elapseTime);
    inline void toggleRotation(){ g_rotate = !g_rotate;}
};

class Rocket{
private:
    GLUquadricObj *pObj;
public:
    Rocket();
    ~Rocket();
    void draw();
    void drawTop();
    void drawBody();
    void drawBottom();
};

};
#endif
