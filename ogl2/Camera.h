#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Entity.h"
#include "Player.h"

class Camera
{
public:

    glm::mat4 view;

    Camera();
    Camera(glm::vec2 position);

    ~Camera();

    glm::mat4 getMatrixView();
    void setPosition(glm::vec2 position);
    void update();
    void move(glm::vec2 offset);
    void setOffset(GLfloat xoffset, GLfloat yoffset);

    
private:
    GLfloat yOffset;
    GLfloat xOffset;

    glm::vec3 position;
    glm::vec3 targetPosition;
    glm::vec3 up;

    glm::vec3 wordlUp;
    glm::vec3 right;
    glm::vec3 front;

    glm::vec3 cameraDirection;

    void updateCameraVectors();
};

/* bad worked  it in sycle
view = glm::lookAt(
    glm::normalize(glm::vec3(player->position.x, player->position.y, 1)),
    glm::normalize(glm::vec3(player->position.x, player->position.y, -1)),
    glm::normalize(glm::vec3(0, 1, 0))
);
ResourceManager::getShader("sprite").SetMatrix4("view", view, GL_TRUE);
*/
