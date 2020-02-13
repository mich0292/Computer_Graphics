#ifndef SATELLITE_HPP
#define SATELLITE_HPP

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "CGLabmain.hpp"
#include "include/rgbLoader.hpp"
#include "include/CGLab01.hpp"
#include "include/Lighting.hpp"
#include "include/World.hpp"
namespace satellite
{
using CGLab01::MyModelLoader;
using Lighting::YellowStar;
using Lighting::WhiteStar;
using World::Rocket;
using World::SpaceStation;

class Point{
public:
    void draw();
};

class Globe
{
public:
    Globe();
    ~Globe();
    void init();
    void draw();
private:
    // whether to animate
    GLboolean g_rotate = GL_TRUE;

    // texture and glu data
    GLUquadricObj * g_sphere = NULL;
    GeImageData g_imgData;
    GLuint g_img = 0;

    GLfloat g_angle_x = 27.0f;
    GLfloat g_inc = 0.0f;
    char g_filename[128] = "data/map.rgb";

    // light position
    GLfloat g_light_position[4] = { 2.0f, 1.2f, 4.0f, 1.0f };
};

class Planet
{
public:
    Planet();
    ~Planet();
    void init();
    void draw();
private:
    // whether to animate
    GLboolean g_rotate = GL_TRUE;

    // texture and glu data
    GLUquadricObj * g_sphere = NULL;
    GeImageData g_imgData;
    GLuint g_img = 0;

    GLfloat g_angle_x = 27.0f;
    GLfloat g_inc = 0.0f;
    char g_filename[128] = "data/planet.rgb";

    // light position
    GLfloat g_light_position[4] = { 2.0f, 1.2f, 4.0f, 1.0f };
};

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
    const int NUM_OF_STARS = 1;
    long int timeold, timenew, elapseTime;
    Satellite satellite;
    MyModelLoader prometheusloader;
    MyModelLoader capsuleloader;
    MyModelLoader satelliteloader;
    MyModelLoader tyderiumloader;
    YellowStar yellowStar;
    WhiteStar whiteStar;
    Globe globe;
    Planet planet;
    Rocket rocket;
    SpaceStation station;
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
    }

    void init()
    {
        timeold = glutGet(GLUT_ELAPSED_TIME);
        globe.init();
        planet.init();
        //prometheusloader.load("D:/CG LABBBBBB/Michelle/data/Prometheus.txt", 2 );
        prometheusloader.load("/data/Prometheus.txt", 3 );
        //capsuleloader.load("D:/CG LABBBBBB/Michelle/data/capsule.txt", 0.02, 0.75, 0.75, 0.75);
        capsuleloader.load("data/capsule.txt", 0.02, 0.560, 0.570, 0.580);
        satelliteloader.load("data/satelliteModel.txt", 0.4, 0.955, 0.637, 0.538);
        tyderiumloader.load("data/tyderium.txt",0.01, 0.314, 0.784, 0.471);
        yellowStar.init();
        whiteStar.init();
        setupLights();
    }
};

};
#endif
