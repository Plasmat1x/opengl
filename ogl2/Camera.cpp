#include "Camera.h"
#include "ResourceManager.h"

Camera::Camera()
{

}

Camera::Camera(glm::vec2 position)
{
    this->position = (glm::vec3(position.x + xOffset, position.y + yOffset, 1.0f));
    this->targetPosition = (glm::vec3(position.x + xOffset, position.y + yOffset, 0.0f));
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->view = glm::mat4(1.0f);
    this->wordlUp = up;

    updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::getMatrixView()
{
    return glm::lookAt(
        (position),
        (targetPosition),
        (wordlUp));
}

void Camera::setPosition(glm::vec2 position)
{
    this->position = (glm::vec3(position.x + xOffset, position.y + yOffset, 1.0f));
    this->targetPosition = (glm::vec3(position.x + xOffset, position.y + yOffset, 0.0f));
}

void Camera::update()
{   

}

void Camera::move(glm::vec2 offset)
{
    this->position += (glm::vec3(position.x + xOffset, position.y + yOffset, 1.0f));
    this->targetPosition += (glm::vec3(offset, 0));
}

void Camera::setOffset(GLfloat xoffset, GLfloat yoffset)
{
    this->xOffset = -400 + xoffset;
    this->yOffset = -300 + yoffset;
}

void Camera::updateCameraVectors()
{
    
    this->cameraDirection = glm::normalize(this->position - this->targetPosition);

    right = glm::normalize(glm::cross(this->wordlUp, this->cameraDirection));
    up = glm::cross(this->cameraDirection, this->right);
}