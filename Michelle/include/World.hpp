#ifndef WORLD_HPP
#define WORLD_HPP

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
namespace World{

//class Planet{
//private:
//    GLUquadricObj *pObj;
//
//public:
//    Planet();
//    ~Planet();
//    void draw();
//};

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

//class MyVirtualWorld
//{
//public:
//    long int timeold, timenew, elapseTime;
//    Rocket rocket;
//    SpaceStation station;
////    Planet planet;
//
//    void draw()
//    {
//        station.draw();
//        rocket.draw();
//        planet.draw();
//    }
//
//    void tickTime(){
//        timenew = glutGet(GLUT_ELAPSED_TIME);
//        elapseTime = timenew - timeold;
//        timeold = timenew;
//        station.tickTime(elapseTime);
//    }
//
//    void init(){
//        timeold = glutGet(GLUT_ELAPSED_TIME);
//    }
//};
};
#endif
