#include "ResourceManager.h"

std::map<std::string, Image> ResourceManager::images;
std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

Shader ResourceManager::loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name)
{
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

Image ResourceManager::loadImage(const GLchar* file, std::string name)
{
    images[name] = loadImageFromFile(file);
    return images[name];
}

Shader ResourceManager::getShader(std::string name)
{
    return shaders[name];
}

Image ResourceManager::getImage(std::string name)
{
    return images[name];
}

Texture ResourceManager::loadTexture(const GLchar* file, GLboolean alpha, std::string name)
{
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture ResourceManager::getTexture(std::string name)
{
    return textures[name];
}

void ResourceManager::clear()
{
    for (auto iter : shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : images)
        SOIL_free_image_data(iter.second.data);
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    const GLchar* gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Image ResourceManager::loadImageFromFile(const GLchar* file)
{

    Image image;

    image.loadImageFromFile(file);

    return image;
}

Texture ResourceManager::loadTextureFromFile(const GLchar* file, GLboolean alpha)
{
    Texture texture;

    if (alpha)
    {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }

    int width, height;
    unsigned char* data = SOIL_load_image(file, &width, &height, 0, texture.image_format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    
    if (!data)
    {
        std::cout << "SOIL: Can't load image by path: " << file << std::endl;
    }

    texture.generate(width, height, data);
    SOIL_free_image_data(data);
    return texture;
}
