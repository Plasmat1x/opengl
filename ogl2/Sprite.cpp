#include "Sprite.h"
#include "Tools.h"
#include "ResourceManager.h"

Sprite::Sprite()
{

}

Sprite::Sprite(std::string _shader) :
    position(glm::vec2(0.0f, 0.0f)),
    size(glm::vec2(100.0f, 100.0f)),
    color(glm::vec3(1.0f)),
    scale(glm::vec2(1.0f)),
    rotation(0.0f),
    alpha(1.0f)
{

    v0 = glm::vec2(1.0f, 1.0f);
    v1 = glm::vec2(1.0f, 0.0f);
    v2 = glm::vec2(0.0f, 0.0f);
    v3 = glm::vec2(0.0f, 1.0f);

    vertices = {
        // positions  // texture
         1.0f,  1.0f, v0.x, v0.y, // top right
         1.0f,  0.0f, v1.x, v1.y, // bottom right
         0.0f,  0.0f, v2.x, v2.y, // bottom left
         0.0f,  1.0f, v3.x, v3.y  // top left
    };

    indices = {
        0,1,3,
        1,2,3
    };

    setShader(ResourceManager::getShader(_shader));

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), NULL, GL_STREAM_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

void Sprite::init()
{
    //glActiveTexture(GL_TEXTURE0);
    //glBindVertexArray(this->VAO);

    //vertices = {
    //    // positions  // texture
    //     1.0f,  1.0f, v0.x, v0.y, // top right
    //     1.0f,  0.0f, v1.x, v1.y, // bottom right
    //     0.0f,  0.0f, v2.x, v2.y, // bottom left
    //     0.0f,  1.0f, v3.x, v3.y  // top left
    //};

    ///*
    //vertices = {
    //    // positions  // texture
    //     1.0f,  1.0f, 1.0f, 1.0f, // top right
    //     1.0f,  0.0f, 1.0f, 0.0f, // bottom right
    //     0.0f,  0.0f, 0.0f, 0.0f, // bottom left
    //     0.0f,  1.0f, 0.0f, 1.0f  // top left
    //};
    //*/
    //indices = {
    //    0,1,3,
    //    1,2,3
    //};

    //texture.bind();

    //glBindVertexArray(this->VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GLfloat), &vertices[0]);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    //glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLfloat), &indices[0]);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

}


//функции-сэтеры 

void Sprite::setPosition(glm::vec2 position)
{
    this->position = position;
}

void Sprite::setPosition(GLint x, GLint y)
{
    this->position = glm::ivec2(x, y);
}

void Sprite::setSize(glm::vec2 size)
{
    this->size = size;
}

void Sprite::setSize(GLint w, GLint h)
{
    this->size = glm::ivec2(w, h);
}

void Sprite::setColor(glm::vec3 color)
{
    this->color = color;
}

void Sprite::setColor(GLfloat r, GLfloat g, GLfloat b)
{
    this->color = glm::vec3(r, g, b);
}

void Sprite::setScale(GLfloat scale)
{
    this->scale.x = scale;
    this->scale.y = scale;
}

void Sprite::setScale(GLfloat wScale, GLfloat hScale)
{
    this->scale.x = wScale;
    this->scale.y = hScale;
}

void Sprite::setShader(Shader shader)
{
    this->shader = shader;
}

void Sprite::setTextureRect(glm::vec4 textureRect)
{
    v0.x = toolkit::normalize(textureRect.x + textureRect.z, 0, texture.width);
    v0.y = toolkit::normalize(textureRect.y + textureRect.w, 0, texture.height);

    v1.x = toolkit::normalize(textureRect.x + textureRect.z, 0, texture.width);
    v1.y = toolkit::normalize(textureRect.y, 0, texture.height);

    v2.x = toolkit::normalize(textureRect.x, 0, texture.width);
    v2.y = toolkit::normalize(textureRect.y, 0, texture.height);

    v3.x = toolkit::normalize(textureRect.x, 0, texture.width);
    v3.y = toolkit::normalize(textureRect.y + textureRect.w, 0, texture.height);
}

void Sprite::setTextureRect(GLint x, GLint y, GLint w, GLint h)
{
    v0.x = toolkit::normalize(x + w, 0, texture.width);
    v0.y = toolkit::normalize(y + h, 0, texture.height);

    v1.x = toolkit::normalize(x + w, 0, texture.width);
    v1.y = toolkit::normalize(y, 0, texture.height);

    v2.x = toolkit::normalize(x, 0, texture.width);
    v2.y = toolkit::normalize(y, 0, texture.height);

    v3.x = toolkit::normalize(x, 0, texture.width);
    v3.y = toolkit::normalize(y + h, 0, texture.height);
}

void Sprite::setRotation(GLfloat rotation)
{
    this->rotation = rotation;
}

void Sprite::setTexture(Texture texture)
{
    this->texture = texture;
}

void Sprite::setAlpha(GLfloat alpha)
{
    this->alpha = alpha;
}

void Sprite::setAlpha(int alpha)
{
    this->alpha = toolkit::normalize(alpha, 0, 100);
}

//функции-гетеры

Texture& Sprite::getTexture()
{
    return this->texture;
}

Shader Sprite::getShader()
{
    return this->shader;
}

glm::vec2 Sprite::getScale()
{
    return this->scale;
}

glm::vec3 Sprite::getColor()
{
    return this->color;
}

glm::vec2 Sprite::getSize()
{
    return this->size;
}

glm::vec2 Sprite::getPosition()
{
    return this->position;
}

GLfloat Sprite::getRotation()
{
    return this->rotation;
}

GLfloat Sprite::getAlpha()
{
    return this->alpha;
}

//функции спрайта

void Sprite::draw()
{
    this->shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size * scale, 1.0f));

    this->shader.SetMatrix4("model", model);
    this->shader.SetVector4f("color", glm::vec4(color, alpha));

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    vertices = {
        // positions  // texture
         1.0f,  1.0f, v0.x, v0.y, // top right
         1.0f,  0.0f, v1.x, v1.y, // bottom right
         0.0f,  0.0f, v2.x, v2.y, // bottom left
         0.0f,  1.0f, v3.x, v3.y  // top left
    };

    texture.bind();

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GLfloat), &vertices[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLfloat), &indices[0]);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
