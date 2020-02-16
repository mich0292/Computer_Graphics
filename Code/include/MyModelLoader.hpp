#ifndef MYMODELLOADER_HPP
#define MYMODELLOADER_HPP
#include "../CGLabmain.hpp"
#include <string>
#include <vector>

class MyModelLoader
{
 public:
    MyModelLoader()
    {
    }
    ~MyModelLoader()
    {
    }
    //load a model and scale it
    void load(string filename, float scale = 1.0f, float color1 = 1.0f, float color2 = 0.8f, float color3 = 0.4f);
    void draw(float x = 0.0f, float y = 0.0f, float z = 0.0f, float angle = 0, GLboolean movingFlag = GL_FALSE);
    void tickTime(long int elapseTime, float speed = 0.0f);
    void setupLights();
    inline void toggleMovement(){ g_movement = !g_movement;}
    void computeSurfaceNormal(GLfloat vertex1[], GLfloat vertex2[], GLfloat vertex3[], GLfloat normal[]);
 private:
    vector<GLfloat> vertices;
    vector<int> faces;
    GLuint stanforddragon; //for generating display list
    GLfloat movement;
    GLboolean g_movement = GL_TRUE;
};

#endif //CGLAB01_HPP
