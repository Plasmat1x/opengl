#pragma once
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>

#include <SOIL/SOIL.h>

#include "Image.h"
#include "Texture.h"
#include "Shader.h"

class ResourceManager
{
public:
    static std::map<std::string, Image> images;
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;

    static Shader loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
    static Shader getShader(std::string name);
    static Image loadImage(const GLchar* file, std::string name);
    static Image getImage(std::string name);

    static void clear();
private:
    ResourceManager() {}

    static Shader loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
    static Image loadImageFromFile(const GLchar* file);
};

