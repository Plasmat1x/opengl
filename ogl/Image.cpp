#include "Image.h"



Image::Image()
{
}


Image::~Image()
{
}

void Image::loadImageFromFile(std::string filePath)
{
    data = SOIL_load_image(filePath.data(), &width, &height, &nrComponents, 0);

    if (data)
    {
        if (nrComponents == 1)
        {
            format = GL_RED;
        }
        if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        if (nrComponents == 4)
        {
            format = GL_RGBA;
        }
    }
    else
    {
        std::cout << "Image failed to load at path: " << filePath.data() << std::endl;
        SOIL_free_image_data(data);
    }
}

void Image::cleanup()
{
    SOIL_free_image_data(data);
}