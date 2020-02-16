#ifndef RGBLOADER_HPP
#define RGBLOADER_HPP

//-----------------------------------------------------------------------------
// Name: struct GeImageData
// Desc: holds basic image data
//-----------------------------------------------------------------------------
struct GeImageData
{
    int width;
    int height;
    unsigned * bits;

    GeImageData( int w = 0, int h = 0, unsigned * p = 0 )
        : width( w ), height( h ), bits( p )
    { }
};
bool ge_read_image( const char * filename, GeImageData * pImgData );
#endif
