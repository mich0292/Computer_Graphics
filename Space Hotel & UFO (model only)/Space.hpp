#ifndef SPACE_HPP
#define SPACE_HPP

#include "main.hpp"
#include <string>
#include <vector>

namespace Space {

float const PI = 3.14159;

class SpaceHotel{
public:
    GLUquadricObj* qObj;
    SpaceHotel();
    void draw();
    void drawConnector();
};

class UFO{
public:
    void draw();
};

//------------------------------------
//the main program will call methods from this class
class MyVirtualWorld
{
 public:
    SpaceHotel spaceHotel;
    UFO ufo;
    void draw(){
        //spaceHotel.draw();
        ufo.draw();
    }

    void tickTime()
    {

    }

    //   for any one-time only initialization of the
    //   virtual world before any rendering takes place
    //   BUT after OpenGL has been initialized
    void init()
    {

    }
};

}; //end of namespace Space

#endif //SPACE_HPP
