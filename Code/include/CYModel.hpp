#ifndef CYMODEL_HPP
#define CYMODEL_HPP

namespace CYModel {

float const PI = 3.14159;

class SpaceHotel{
public:
    GLUquadricObj* qObj;
    SpaceHotel();
    ~SpaceHotel();
    void draw();
    void drawConnector();
    void drawLightBulb();
    void tickTime(long int elapseTime);
    inline void toggleMovement(){animation = !animation;}
private:
    GLboolean animation = GL_TRUE;
    GLfloat posx, posy, posz;
    GLfloat rot;
    GLfloat velx, vely, velz;
};

class UFO{
public:
    UFO();
    void draw();
    void tickTime(long int elapseTime);
    inline void toggleMovement(){animation = !animation;}
private:
    GLfloat posx, posy, posz;
    GLfloat velx, vely, velz;
    GLboolean rot;
    GLfloat angle;
    GLboolean animation = GL_TRUE;
};

}; //end of namespace Space

#endif //CYMODEL_HPP

