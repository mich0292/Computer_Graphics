#ifndef SATELLITE_HPP
#define SATELLITE_HPP
#include "CGLabmain.hpp"
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

namespace satellite
{
class Globe
{
public:
    struct GeImageData
    {
        int width;
        int height;
        unsigned * bits;

        GeImageData( int w = 0, int h = 0, unsigned * p = 0 )
            : width( w ), height( h ), bits( p )
        { }
    };
    typedef struct _ImageRec
    {
        unsigned short imagic;
        unsigned short type;
        unsigned short dim;
        unsigned short xsize, ysize, zsize;
        unsigned int min, max;
        unsigned int wasteBytes;
        char name[80];
        unsigned long colorMap;
        FILE *file;
        unsigned char *tmp, *tmpR, *tmpG, *tmpB;
        unsigned long rleEnd;
        unsigned int *rowStart;
        int *rowSize;
    } ImageRec;
    Globe();
    ~Globe();
    void draw();
    bool ge_read_image( const char * filename, GeImageData * pImgData );
    void rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b, unsigned char *a,unsigned char *l,int n);
    void rgbtorgba(unsigned char *r,unsigned char *g,unsigned char *b, unsigned char *l,int n);
    void bwtorgba(unsigned char *b,unsigned char *l,int n);
    unsigned * ge_read_rgb( const char * name, int * width, int * height,int * components);
    static void ConvertShort(unsigned short *array, unsigned int length)
    {
        unsigned short b1, b2;
        unsigned char *ptr;

        ptr = (unsigned char *)array;
        while (length--)
        {
            b1 = *ptr++;
            b2 = *ptr++;
            *array++ = (b1 << 8) | (b2);
        }
    }
    static void ConvertUint(unsigned *array, unsigned int length)
    {
        unsigned int b1, b2, b3, b4;
        unsigned char *ptr;

        ptr = (unsigned char *)array;
        while (length--)
        {
            b1 = *ptr++;
            b2 = *ptr++;
            b3 = *ptr++;
            b4 = *ptr++;
            *array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
        }
    }
    static ImageRec * ImageOpen(const char *fileName)
    {
        union
        {
            int testWord;
            char testByte[4];
        } endianTest;
        ImageRec *image;
        int swapFlag;
        int x;

        endianTest.testWord = 1;
        if (endianTest.testByte[0] == 1)
        {
            swapFlag = 1;
        }
        else
        {
            swapFlag = 0;
        }

        image = (ImageRec *)malloc(sizeof(ImageRec));
        if (image == NULL)
        {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        if ((image->file = fopen(fileName, "rb")) == NULL)
        {
            perror(fileName);
            //exit(1);
            return NULL;
        }

        fread(image, 1, 12, image->file);

        if (swapFlag)
        {
            ConvertShort(&image->imagic, 6);
        }

        image->tmp = (unsigned char *)malloc(image->xsize*256);
        image->tmpR = (unsigned char *)malloc(image->xsize*256);
        image->tmpG = (unsigned char *)malloc(image->xsize*256);
        image->tmpB = (unsigned char *)malloc(image->xsize*256);
        if (image->tmp == NULL || image->tmpR == NULL || image->tmpG == NULL ||
                image->tmpB == NULL)
        {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }

        if ((image->type & 0xFF00) == 0x0100)
        {
            x = image->ysize * image->zsize * (int) sizeof(unsigned);
            image->rowStart = (unsigned *)malloc(x);
            image->rowSize = (int *)malloc(x);
            if (image->rowStart == NULL || image->rowSize == NULL)
            {
                fprintf(stderr, "Out of memory!\n");
                exit(1);
            }
            image->rleEnd = 512 + (2 * x);
            fseek(image->file, 512, SEEK_SET);
            fread(image->rowStart, 1, x, image->file);
            fread(image->rowSize, 1, x, image->file);
            if (swapFlag)
            {
                ConvertUint(image->rowStart, x/(int) sizeof(unsigned));
                ConvertUint((unsigned *)image->rowSize, x/(int) sizeof(int));
            }
        }
        return image;
    }
    static void ImageClose(ImageRec *image)
    {
        fclose(image->file);
        free(image->tmp);
        free(image->tmpR);
        free(image->tmpG);
        free(image->tmpB);
        free(image);
    }
    static void ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z)
    {
        unsigned char *iPtr, *oPtr, pixel;
        int count;

        if ((image->type & 0xFF00) == 0x0100)
        {
            fseek(image->file, (long) image->rowStart[y+z*image->ysize],
                  SEEK_SET);
            fread(image->tmp, 1, (unsigned int)image->rowSize[y+z*image->ysize],
                  image->file);

            iPtr = image->tmp;
            oPtr = buf;
            for (;;)
            {
                pixel = *iPtr++;
                count = (int)(pixel & 0x7F);
                if (!count)
                {
                    return;
                }
                if (pixel & 0x80)
                {
                    while (count--)
                    {
                        *oPtr++ = *iPtr++;
                    }
                }
                else
                {
                    pixel = *iPtr++;
                    while (count--)
                    {
                        *oPtr++ = pixel;
                    }
                }
            }
        }
        else
        {
            fseek(image->file,
                  512+(y*image->xsize)+(z*image->xsize*image->ysize),
                  SEEK_SET);
            fread(buf, 1, image->xsize, image->file);
        }
    }
private:
    // whether to animate
    GLboolean g_rotate = GL_TRUE;

    // texture and glu data
    GLUquadricObj * g_sphere = NULL;
    GeImageData g_imgData;
    GLuint g_img = 0;

    GLfloat g_angle_x = 27.0f;
    GLfloat g_inc = 0.0f;
    char g_filename[128] = "D:/ComputerGraphics/Michelle/map.rgb";

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
    long int timeold, timenew, elapseTime;
    Satellite satellite;
    Globe globe;
public:
    void draw()
    {
        //satellite.drawBottom();
        //satellite.drawTop();
        //satellite.drawTopStem(); // IGNORE!! only for drawTop()
        //satellite.drawWing();
        //satellite.drawBody();
        //satellite.draw();
        globe.draw();
    }

    void tickTime()
    {
        timenew = glutGet(GLUT_ELAPSED_TIME);
        elapseTime = timenew - timeold;
        timeold = timenew;
        satellite.tickTime(elapseTime);
    }

    void init()
    {
        timeold = glutGet(GLUT_ELAPSED_TIME);

    }
};

};
#endif
