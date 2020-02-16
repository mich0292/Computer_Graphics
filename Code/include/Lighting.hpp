#ifndef LIGHTING_HPP
#define LIGHTING_HPP
#include <cmath>
#include "../CGLabmain.hpp"
#include "MyModelLoader.hpp"
namespace Lighting
{
class Point{
public:
    void draw();
    void setupLights();
    void toggleLight();
private:
    GLboolean lighton;
};

class YellowStar
{
public:
    YellowStar(){;}
    ~YellowStar(){;}
    void setupLights();
    void toggleLight();
    void draw();
    void init();
private:
    MyModelLoader starLoader;
    long int timestart;
    GLboolean lighton; //keep track if lights are on or off
};

class WhiteStar
{
public:
    WhiteStar(){;}
    ~WhiteStar(){;}
    void setupLights();
    void toggleLight();
    void draw();
    void init();
private:
    MyModelLoader starLoader;
    long int timestart;
    GLboolean lighton; //keep track if lights are on or off
};
}; //end of namespace
#endif
