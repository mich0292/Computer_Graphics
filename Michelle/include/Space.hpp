#ifndef SPACE_HPP
#define SPACE_HPP



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

}; //end of namespace Space

#endif //SPACE_HPP
