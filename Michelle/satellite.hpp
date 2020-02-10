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
    void drawWing();
    void drawTop();
    void drawTopStem();
    void drawBottom();
    void drawBody();
    void drawTopBody();
    void drawBottomBody();
    void drawCube(float color[]);

private:
    GLUquadricObj *pObj;
};

class MyVirtualWorld
{
    Satellite satellite;
public:
    draw()
    {
        //satellite.drawBottom();
        //satellite.drawTop();
        //satellite.drawTopStem(); // IGNORE!! only for drawTop()
        //satellite.drawWing();
        //satellite.drawBody();
        satellite.draw();
    }

    init() {;}
    tickTime() {;}
};

};
#endif
