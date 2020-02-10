#ifndef SATELLITE_HPP
#define SATELLITE_HPP
#include "CGLabmain.hpp"
namespace satellite
{
class Satellite
{
public:
    Satellite();
    ~Satellite();
    void draw();
    void build();
    void drawWing();
    void drawWingStem();
    void drawTop();
    void drawBottom();
    void drawBody();
    void drawTopBody();
    void drawBottomBody();
    void drawCube(float color[]);
    void tickTime(long int elapseTime);

private:
    GLUquadricObj *pObj;
    GLfloat angle = 0.0f;
};

class MyVirtualWorld
{
    long int timeold, timenew, elapseTime;
    Satellite satellite;
public:
    void draw()
    {
        //satellite.drawBottom();
        //satellite.drawTop();
        //satellite.drawTopStem(); // IGNORE!! only for drawTop()
        //satellite.drawWing();
        //satellite.drawBody();
        satellite.draw();
    }

    void tickTime(){
        timenew = glutGet(GLUT_ELAPSED_TIME);
        elapseTime = timenew - timeold;
        timeold = timenew;
        satellite.tickTime(elapseTime);
    }

    void init(){
        timeold = glutGet(GLUT_ELAPSED_TIME);
    }
};

};
#endif
