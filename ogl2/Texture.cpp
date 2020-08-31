#include "Texture.h"
#include <iostream>

Texture::Texture() :
    width(0),
    height(0),
    mipmap(false),
    smooth(false),
    repeated(false)
{
    glGenTextures(1, &this->ID);
}

Texture::~Texture()
{

}

void Texture::loadTextureFromFile(const GLchar* fileName)
{
    unsigned char* data = SOIL_load_image(fileName, &width, &height, &nrComponents, 0);
    if (data)
    {
        if (nrComponents == 1)
        {
            internal_format = GL_RED;
            image_format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            internal_format = GL_RGB;
            image_format = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            internal_format = GL_RGBA;
            image_format = GL_RGBA;
        }

        if (repeated)
        {
            wrap_s = GL_REPEAT;
            wrap_t = GL_REPEAT;
        }
        else
        {
            wrap_s = GL_CLAMP_TO_BORDER;
            wrap_t = GL_CLAMP_TO_BORDER;
        }

        if (smooth)
        {
            filter_min = GL_LINEAR;
            filter_max = GL_LINEAR;
        }
        else
        {
            filter_min = GL_NEAREST;
            filter_max = GL_NEAREST;
        }

        glBindTexture(GL_TEXTURE_2D, this->ID);
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);
        
        if (mipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);

        SOIL_free_image_data(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << fileName << std::endl;
        SOIL_free_image_data(data);
    }
}

void Texture::loadTextureFromImage(Image image)
{
    this->width = image.width;
    this->height = image.height;

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeated ? GL_REPEAT : GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeated ? GL_REPEAT : GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
    if (mipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    image.cleanup();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::generate(int width, int height, unsigned char* data)
{
    this->width = width;
    this->height = height;

    if (repeated)
    {
        wrap_s = GL_REPEAT;
        wrap_t = GL_REPEAT;
    }
    else
    {
        wrap_s = GL_CLAMP_TO_BORDER;
        wrap_t = GL_CLAMP_TO_BORDER;
    }

    if (smooth)
    {
        filter_min = GL_LINEAR;
        filter_max = GL_LINEAR;
    }
    else
    {
        filter_min = GL_NEAREST;
        filter_max = GL_NEAREST;
    }

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, this->width, this->height, 0, image_format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);
    if (mipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::generateFromImage(Image image)
{
    this->width = image.width;
    this->height = image.height;

    if (repeated)
    {
        wrap_s = GL_REPEAT;
        wrap_t = GL_REPEAT;
    }
    else
    {
        wrap_s = GL_CLAMP_TO_BORDER;
        wrap_t = GL_CLAMP_TO_BORDER;
    }

    if (smooth)
    {
        filter_min = GL_LINEAR;
        filter_max = GL_LINEAR;
    }
    else
    {
        filter_min = GL_NEAREST;
        filter_max = GL_NEAREST;
    }

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);
    if (mipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    image.cleanup();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
