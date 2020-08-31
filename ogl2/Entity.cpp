#include "Entity.h"
#include "ResourceManager.h"

Entity::Entity(glm::vec2 position, glm::vec2 size, std::string texture) :
    position(position),
    size(size)
{
    this->position = position;
    this->size = size;
    this->init(texture);
}

Entity::~Entity()
{
}

void Entity::init(std::string name)
{
    this->sprite.setShader(ResourceManager::getShader("sprite"));
    this->sprite.setTexture(ResourceManager::getTexture(name)); 
}

void Entity::update(GLfloat deltaTime)
{

}

void Entity::setPosition(glm::vec2 position)
{
    this->position = position;
}

void Entity::setSize(glm::vec2 size)
{
    this->size = size;
}

Sprite& Entity::getSprite()
{
    return this->sprite;
}

glm::vec2 Entity::getPosition()
{
    return this->position;
}

glm::vec2 Entity::getSize()
{
    return this->size;
}

void Entity::draw()
{
    this->sprite.setPosition(this->position);
    this->sprite.setSize(this->size);
    this->sprite.draw();
}

