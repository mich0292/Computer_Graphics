#ifndef WORLD_HPP
#define WORLD_HPP

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
namespace World{

class SpaceStation{
private:
    GLUquadricObj *pObj;
    GLfloat angle;

public:
    SpaceStation();
    ~SpaceStation();
    void draw();
    void drawBody();
    void drawSolarPanel();
    void tickTime(long int elapseTime);
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
