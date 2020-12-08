#ifndef WORLD_HPP
#define WORLD_HPP

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "CGLabmain.hpp"
#include "include/MyModelLoader.hpp"

namespace World
{

class MyVirtualWorld
{
    long int timeold, timenew, elapseTime;
    ///MyModelLoader prometheusloader;
    MyModelLoader spaceshiploader;
    bool lighton[7]; //keep track if lights are on or off

public:
    void draw();
    void setupLights();
    void toggleLight(int lightno);

    void tickTime()
    {
        timenew = glutGet(GLUT_ELAPSED_TIME);
        elapseTime = timenew - timeold;
        timeold = timenew;
        ///prometheusloader.tickTime(elapseTime);
    }

    void init()
    {
        timeold = glutGet(GLUT_ELAPSED_TIME);
        ///prometheusloader.load("D:/ComputerGraphics/Code/data/Prometheus.txt", 3 );
        spaceshiploader.load("D:/ComputerGraphics/Code/data/spaceship.txt", 2);
        //It could be "data/Pometheus.txt" or the full path
        setupLights();
    }

    void toggleAnimation(){
        ///prometheusloader.toggleMovement();
    }

    void toggleTexture(){
    }
};

};
#endif
