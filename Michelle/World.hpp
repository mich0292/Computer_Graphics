#ifndef WORLD_HPP
#define WORLD_HPP

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "CGLabmain.hpp"
#include "include/MyModelLoader.hpp"
#include "include/Lighting.hpp"
#include "include/CYModel.hpp"
#include "include/FJModel.hpp"
#include "include/MCModel.hpp"

namespace World
{
using Lighting::Point;
using Lighting::YellowStar;
using Lighting::WhiteStar;
using FJModel::Rocket;
using FJModel::SpaceStation;
using CYModel::SpaceHotel;
using CYModel::UFO;
using MCModel::Globe;
using MCModel::Planet;
using MCModel::Satellite;
using MCModel::MyModelLoader;

class MyVirtualWorld
{
    long int timeold, timenew, elapseTime;
    Satellite satellite;
    MyModelLoader prometheusloader;
    MyModelLoader capsuleloader;
    MyModelLoader satelliteloader;
    MyModelLoader tyderiumloader;
    MyModelLoader stationloader;
    YellowStar yellowStar;
    WhiteStar whiteStar;
    Globe globe;
    Planet planet;
    Rocket rocket;
    SpaceStation station;
    SpaceHotel hotel;
    UFO ufo;
    Point point;

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
        satellite.tickTime(elapseTime);
        station.tickTime(elapseTime);
        prometheusloader.tickTime(elapseTime);
        satelliteloader.tickTime(elapseTime);
        tyderiumloader.tickTime(elapseTime, 0.8f);
        stationloader.tickTime(elapseTime);
    }

    void init()
    {
        timeold = glutGet(GLUT_ELAPSED_TIME);
        globe.init();
        planet.init();
        //prometheusloader.load("C:/Users/User/Documents/GitHub/ComputerGraphics/Michelle/data/Prometheus.txt", 2 );
        prometheusloader.load("D:/ComputerGraphics/Michelle/data/Prometheus.txt", 2);
        //prometheusloader.load("/data/Prometheus.txt", 3 );
        //capsuleloader.load("C:/Users/User/Documents/GitHub/ComputerGraphics/Michelle/data/capsule.txt", 0.02, 0.75, 0.75, 0.75);
        capsuleloader.load("D:/ComputerGraphics/Michelle/data/capsule.txt", 0.02, 0.75, 0.75, 0.75);
        //capsuleloader.load("data/capsule.txt", 0.02, 0.560, 0.570, 0.580);
        //satelliteloader.load("data/satelliteModel.txt", 0.4, 0.955, 0.637, 0.538);
        //satelliteloader.load("C:/Users/User/Documents/GitHub/ComputerGraphics/Michelle/data/satelliteModel.txt", 0.4, 0.955, 0.637, 0.538);
        satelliteloader.load("D:/ComputerGraphics/Michelle/data/satelliteModel.txt", 0.4, 0.955, 0.637, 0.538);
        //tyderiumloader.load("data/tyderium.txt",0.01, 0.314, 0.784, 0.471);
        //tyderiumloader.load("C:/Users/User/Documents/GitHub/ComputerGraphics/Michelle/data/tyderium.txt",0.01, 0.314, 0.784, 0.471);
        tyderiumloader.load("D:/ComputerGraphics/Michelle/data/tyderium.txt",0.01, 0.314, 0.784, 0.471);
        stationloader.load("D:/ComputerGraphics/Michelle/data/station.txt", 0.02, 0.560, 0.570, 0.580);
        yellowStar.init();
        whiteStar.init();
        setupLights();
    }

    void toggleAnimation(){
        planet.toggleRotation();
        globe.toggleRotation();
        prometheusloader.toggleMovement();
        satelliteloader.toggleMovement();
        tyderiumloader.toggleMovement();
        stationloader.toggleMovement();
        station.toggleRotation();
        satellite.toggleRotation();
    }

    void toggleTexture(){
        planet.toggleTexture();
        globe.toggleTexture();
    }
};

};
#endif
