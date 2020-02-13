/*
 CGLab01.hpp
 Objective: Header File for Lab01 Demo Models / World

 INSTRUCTIONS
 ============
 Please refer to CGLabmain.cpp for instructions

 SPECIAL NOTES
 =============
 * Try out other models from http://graphics.stanford.edu/data/3Dscanrep/
   However, you will need to modify the file to comform to the
   format that is being used in this program.
 ==========
*/

#ifndef CGLAB01_HPP
#define CGLAB01_HPP

#include "../CGLabmain.hpp"
#include <string>
#include <vector>

namespace CGLab01 {

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
    void draw(float x = 0.0f, float y = 0.0f, float z = 0.0f, float angle = 0, bool movingFlag = FALSE);
    void tickTime(long int elapseTime, float speed = 0.0f);
    void setupLights();
    inline void toggleMovement(){ g_movement = !g_movement;}
 private:
    vector<GLfloat> vertices;
    vector<int> faces;
    GLuint stanforddragon; //for generating display list
    GLfloat movement;
    GLboolean g_movement = GL_TRUE;
};

}; //end of namespace CGLab01

#endif //CGLAB01_HPP
