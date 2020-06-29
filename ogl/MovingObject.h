#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#include "Map.h"
#include "Tools.h"

class MovingObject
{
public:
    glm::vec2 mOldPosition;
    glm::vec2 mPosition;

    glm::vec2 mOldSpeed;
    glm::vec2 mSpeed;

    glm::vec2 mScale;

    toolkit::AABB mAABB;
    toolkit::AABB_mm _mAABB;
    glm::vec2 mAABBOffset;

    Map *mMap;
    GLfloat mGroundY;
    GLfloat lwallX;
    GLfloat rwallX;
    GLfloat mCeil;

    GLint oneWayThreshold = 10.0f;
    bool onWayPlatform = false;

    bool mPushedRightWall;
    bool mPushesRightWall;

    bool mPushedLeftWall;
    bool mPushesLeftWall;

    bool mWasOnGround;
    bool mOnGround;

    bool mWasAtCeiling;
    bool mAtCeiling;

    MovingObject() { ; }
    ~MovingObject() { delete mMap; }

    void updatePhysics(float deltaTime);

    bool hasGround(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed);
    bool hasCeiling(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed);
    bool hasLeftWall(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed);
    bool hasRightWall(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed);
    bool hasWall(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed);
};

