#ifndef LIGHTING_HPP
#define LIGHTING_HPP
#include <cmath>
#include "../CGLabmain.hpp"
#include "CGLab01.hpp"
namespace Lighting
{
using CGLab01::MyModelLoader;
class YellowStar
{
public:
    YellowStar(){;}
    ~YellowStar(){;}
    void setupLights();
    void toggleLight(int lightno);
    void draw();
    void init();
private:
    MyModelLoader starLoader;
    long int timestart;
    bool lighton[1]; //keep track if lights are on or off
};

class WhiteStar
{
public:
    WhiteStar(){;}
    ~WhiteStar(){;}
    void setupLights();
    void toggleLight(int lightno);
    void draw();
    void init();
private:
    MyModelLoader starLoader;
    long int timestart;
    bool lighton[1]; //keep track if lights are on or off
};
}; //end of namespace CGLab12and13
#endif
