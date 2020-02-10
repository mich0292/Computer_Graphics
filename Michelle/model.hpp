#ifndef MODEL_HPP
#define MODEL_HPP
#include "CGLabmain.hpp"
namespace model
{
class Planet
{
public:
    Planet();
    ~Planet();
    void draw();
private:
    GLUquadricObj *pObj;
};

class Rocket
{
public:
    Rocket();
    ~Rocket();
    void draw();
    void drawFin();
private:
    GLUquadricObj *pObj;
};

class Satellite1
{
public:
    Satellite1();
    ~Satellite1();
    void draw();
    void drawSide();
    void drawDisk();
private:
    GLUquadricObj *pObj;
};

class Satellite2
{
public:
    Satellite2();
    ~Satellite2();
    void draw();
    void drawWing();
    void drawTop();
    void drawBottom();
    void drawTopStem();
private:
    GLUquadricObj *pObj;
};

class MyVirtualWorld
{
    Planet planet;
    Rocket rocket;
    Satellite1 satellite1;
    Satellite2 satellite2;
public:
    draw()
    {
        //planet.draw();
        //rocket.draw();
        //satellite.drawSide();
        //satellite1.draw();
        //satellite2.drawBottom();
        satellite2.drawTop();
        //satellite2.drawTopStem();
    }

    init() {;}
    tickTime() {;}
};

};
#endif
