#ifndef MCMODEL_HPP
#define MCMODEL_HPP
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "rgbLoader.hpp"
#include "../CGLabmain.hpp"
namespace MCModel
{
class Globe
{
public:
    Globe();
    ~Globe();
    void init();
    void draw();
    inline void toggleTexture()
    {
        g_texture = !g_texture;
    }
    inline void toggleRotation()
    {
        g_rotate = !g_rotate;
    }
private:
    // whether to animate
    GLboolean g_rotate = GL_TRUE;
    GLboolean g_texture = GL_TRUE;

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
    inline void toggleTexture()
    {
        g_texture = !g_texture;
    }
    inline void toggleRotation()
    {
        g_rotate = !g_rotate;
    }
private:
    // whether to animate
    GLboolean g_rotate = GL_TRUE;
    GLboolean g_texture = GL_TRUE;

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
    inline void toggleRotation()
    {
        g_rotate = !g_rotate;
    }

private:
    GLUquadricObj *pObj;
    GLfloat angle = 0.0f;
    // whether to animate
    GLboolean g_rotate = GL_TRUE;

};
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

};
#endif // MCMODEL_HPP
