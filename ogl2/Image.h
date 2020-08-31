#pragma once
#include <GL/glew.h>

#include <vector>
#include <iostream>
#include <string>

#include <SOIL/SOIL.h>

class Image
{
public:
    int width;
    int height;
    int nrComponents;
    unsigned char* data;
    GLenum format = 0;

    Image();
    ~Image();

    bool loadImageFromFile(std::string filePath);
    void cleanup();

private:
    /*
    переместить суда переменные и также подумоть надоли класс? мб структурку?
        int width;
        int height;
        int nrComponents;
        unsigned char* data;
        GLenum format = 0;
    */
};

