#ifndef TEXTURELIST_H
#define TEXTURELIST_H
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <qt_windows.h>
#include <vector>
#include <string>

#define BITMAP_ID 0x4D42

class TextureList
{
public:
    static constexpr int nrTex = 9;
    static constexpr char tex[][100] = {
        "bianzhiwu.bmp",
        "haubu.bmp",
        "huagangyan.bmp",
        "shensemu.bmp",
        "shuidi.bmp",
        "xiewenbu.bmp",
        "xinzhi.bmp",
        "zaishengzhi.bmp",
        "zhidai.bmp",
    };

public:
    TextureList();
    void add(int i, char *path, float *color);

public:
    GLuint list[1000];
    GLfloat color[1000][4];
    int index = 0;
    unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
    void texload(const char *filename);
};

#endif // TEXTURELIST_H
