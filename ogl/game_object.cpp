#include "game_object.h"

GameObject::GameObject()
{

}


GameObject::~GameObject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void GameObject::Init(const char* path, std::string fileName, glm::mat4 projection)
{
    scale = 1.0f;
    setShader(fileName, projection);

    loadTexture(path);

    _ms = 240.0f;

    InitModel();
}

void GameObject::Init(int x, int y, int w, int h, const char* path, std::string fileName, glm::mat4 projection)
{
    scale = 1.0f;
    setShader(fileName, projection);

    loadTexture(path);

    position.x = static_cast<GLfloat>(x);
    position.y = static_cast<GLfloat>(y);
    size.x = static_cast<GLfloat>(w);
    size.y = static_cast<GLfloat>(h);

    _ms = 240.0f;

    InitModel();
}

void GameObject::Init(int x, int y, const char* path, std::string fileName, glm::mat4 projection)
{
    scale = 1.0f;
    setShader(fileName, projection);

    loadTexture(path);

    position.x = static_cast<GLfloat>(x);
    position.y = static_cast<GLfloat>(y);
    size.x = static_cast<GLfloat>(width);
    size.y = static_cast<GLfloat>(height);
    _ms = 240.0f;

    InitModel();
}

void GameObject::Init(int x, int y, const char* path, Shader& sh)
{
    shader = sh;
    
    loadTexture(path);

    position.x  =       static_cast<GLfloat>(x);
    position.y  =       static_cast<GLfloat>(y);
    size.x      =       static_cast<GLfloat>(width);
    size.y      =       static_cast<GLfloat>(height);
    _ms         =       240.0f;

    InitModel();
}

void GameObject::Update(float dt)
{

}

void GameObject::Draw()
{
    shader.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(scale * 0.5f * size.x, scale * 0.5f * size.y, 0.0f));

    //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); //retunr origin
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GameObject::Input(object_Direction dir, float dt)
{
    //it work but dont need now
    GLfloat velocity = _ms * dt;

    if (dir == LEFT)    { position.x += -velocity;  }
    if (dir == RIGHT)   { position.x += velocity;   }
    if (dir == UP)      { position.y += -velocity;  }
    if (dir == DOWN)    { position.y += velocity;   }

}

void GameObject::setColor(float r, float g, float b, float a)
{
    shader.use();
    shader.setVec4("objectColor", r, g, b, a); // change color
}

void GameObject::setShader(std::string fileName, glm::mat4 projection)
{
    std::string vert;
    std::string frag;

    vert = "../shaders/" + fileName + ".vert";
    frag = "../shaders/" + fileName + ".frag";

    shader.init((const GLchar*)vert.data(), (const GLchar*)frag.data());
    shader.use();
    shader.setMat4("projection", projection);
    shader.setInt("image", 0);
    shader.setFloat("scale", 1.0f);
    shader.setVec4("objectColor", 1.0f, 1.0f, 1.0f, 1.0f);

}

GLuint GameObject::loadTexture(char const* path)
{
    glGenTextures(1, &textureID);

    unsigned char* data = SOIL_load_image(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        SOIL_free_image_data(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        SOIL_free_image_data(data);
    }

    return textureID;
}

void GameObject::setScale(float _scale)
{   
    scale = _scale;
    shader.use();
    shader.setFloat("scale", scale);
}

void GameObject::setSize(int w, int h)
{
    size.x = static_cast<GLfloat>(w);
    size.y = static_cast<GLfloat>(h);
}


void GameObject::setPosition(int x, int y)
{
    position.x = static_cast<GLfloat>(x);
    position.y = static_cast<GLfloat>(y);
}


void GameObject::InitModel()
{
    vertices = {
        // positions  // texture coords
         0.5f,  0.5f, 1.0f, 1.0f, // top right
         0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f  // top left 
    };

    indices = {
        0,1,3,
        1,2,3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STREAM_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // color attribute

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


Shader GameObject::getShader()
{
    return shader;
}

glm::vec2 GameObject::getPosition()
{
    return position;
}

float GameObject::getScale()
{
    return scale;
}

glm::vec2 GameObject::getSize()
{
    return size;
}

glm::vec4 GameObject::getColor()
{
    return color;
}

int GameObject::getTexture()
{
    return textureID;
}