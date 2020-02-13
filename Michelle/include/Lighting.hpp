#ifndef LIGHTING_HPP
#define LIGHTING_HPP
#include <cmath>
#include "../CGLabmain.hpp"
#include "CGLab01.hpp"
namespace Lighting
{
using CGLab01::MyModelLoader;
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
}; //end of namespace CGLab12and13
#endif
