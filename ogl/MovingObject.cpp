#include "MovingObject.h"

void MovingObject::updatePhysics(float deltaTime)
{
    mOldPosition = mPosition;
    mOldSpeed = mSpeed;

    mWasOnGround = mOnGround;
    mPushedRightWall = mPushesRightWall;
    mPushedLeftWall = mPushesLeftWall;
    mWasAtCeiling = mAtCeiling;

    mPosition += mSpeed * deltaTime;

    mGroundY = 0;
    mCeil = 0;
    lwallX = 0;
    rwallX = 0;

    onWayPlatform = false;

    if (mSpeed.y >= 0.0f && hasGround(mOldPosition, mPosition, mSpeed))
    {
        mPosition.y = mGroundY - _mAABB.size.y;
        mOnGround = true;
    }
    else
    {
        mOnGround = false;
    }

    if (mSpeed.y <= 0 && hasCeiling(mOldPosition, mPosition, mSpeed))
    {
        mPosition.y = mCeil;
        mAtCeiling = true;
        mSpeed.y = 0.0f;
    }
    else
    {
        mAtCeiling = false;
    }

    if (mSpeed.x <= 0 && hasLeftWall(mOldPosition, mPosition, mSpeed))
    {
        if (mOldPosition.x - _mAABB.size.x <= lwallX)
        {
            mPosition.x = lwallX;
            mPushesLeftWall = true;
        }
        mSpeed.x = std::fmax(mSpeed.x, 0.0f);
    }
    else
    {
        mPushesLeftWall = false;
    }

    if (mSpeed.x >= 0 && hasRightWall(mOldPosition, mPosition, mSpeed))
    {
        if (mOldPosition.x + _mAABB.size.x >= rwallX)
        {
            mPosition.x = rwallX - _mAABB.size.x;
            mPushesRightWall = true;
        }
        mSpeed.x = std::fmin(mSpeed.x, 0.0f);
    }
    else
    {
        mPushesRightWall = false;
    }

    _mAABB.min = glm::vec2(mPosition.x, mPosition.y + _mAABB.size.y);
    _mAABB.max = glm::vec2(mPosition.x + _mAABB.size.x, mPosition.y);
}

bool MovingObject::hasGround(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed)
{

    //onWayPlatform = false;
    glm::vec2 oldBottomLeft = glm::vec2(oldPosition.x, oldPosition.y + _mAABB.size.y) - glm::vec2(0.f, -1.f) + glm::vec2(1.f, 0.f);
    glm::vec2 newBottomLeft = glm::vec2(position.x, position.y + _mAABB.size.y) - glm::vec2(0.f, -1.f) + glm::vec2(1.f, 0.f);
    glm::vec2 newBottomRight = glm::vec2(newBottomLeft.x + _mAABB.size.x - 2.0f , newBottomLeft.y);

    int endY = mMap->getMapTileYAtPoint(newBottomLeft.y);
    int begY = std::fmax(mMap->getMapTileYAtPoint(oldBottomLeft.y) - 1, endY);
    int dist = std::fmax(std::abs(endY - begY), 1);

    int tileIndexX;
    for (int tileIndexY = begY; tileIndexY >= endY; --tileIndexY)
    {
        glm::vec2 bottomLeft = toolkit::vec2Lerp(newBottomLeft, oldBottomLeft, (float)std::abs(endY - tileIndexY));
        glm::vec2 bottomRight = glm::vec2(bottomLeft.x + _mAABB.size.x - 2.0f, bottomLeft.y);

        for (glm::vec2 chekedTile = bottomLeft; ; chekedTile.x += mMap->tileSize.x)
        {
            chekedTile.x = std::fmin(chekedTile.x, bottomRight.x);
            tileIndexX = mMap->getMapTileXAtPoint(chekedTile.x);

            mGroundY = (float)tileIndexY * mMap->tileSize.y;

            if (mMap->isObstacle(tileIndexX, tileIndexY))
            {
                onWayPlatform = false;
                return true;
            }
            else if (mMap->isOneWay(tileIndexX, tileIndexY) 
                && std::abs(chekedTile.y - mGroundY) <= oneWayThreshold + oldPosition.y - position.y)
            {
                onWayPlatform = true;
            }
            if (chekedTile.x >= bottomRight.x)
            {
                if (onWayPlatform)
                {
                    return true;
                }
                break;
            }
        }
    }

    return false;
}


bool MovingObject::hasCeiling(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed)
{
    glm::vec2 oldTopLeft = glm::vec2(oldPosition.x, oldPosition.y) + glm::vec2(0.f, -1.f) + glm::vec2(1.f, 0.f);
    glm::vec2 newTopLeft = glm::vec2(position.x, position.y) + glm::vec2(0.f, -1.f) + glm::vec2(1.f, 0.f);
    glm::vec2 newTopRight = glm::vec2(newTopLeft.x + _mAABB.size.x - 2.0f, newTopLeft.y);

    int endY = mMap->getMapTileYAtPoint(newTopRight.y);
    int begY = std::fmin(mMap->getMapTileYAtPoint(oldTopLeft.y) + 1, endY);
    int dist = std::fmax(std::abs(endY - begY), 1);

    int tileIndexX;
    for (int tileIndexY = begY; tileIndexY <= endY; ++tileIndexY)
    {
        glm::vec2 topLeft = toolkit::vec2Lerp(newTopLeft, oldTopLeft, (float)std::abs(endY - tileIndexY));
        glm::vec2 topRight = glm::vec2(topLeft.x + _mAABB.size.x - 2.0f, topLeft.y);

        for (glm::vec2 chekedTile = topLeft; ; chekedTile.x += mMap->tileSize.x)
        {
            chekedTile.x = std::fmin(chekedTile.x, topRight.x);
            tileIndexX = mMap->getMapTileXAtPoint(chekedTile.x);       

            if (mMap->isObstacle(tileIndexX, tileIndexY))
            {
                if(speed.y < 0)
                    mCeil = (float)tileIndexY * mMap->tileSize.y + mMap->tileSize.y;
                return true;
            }
            if (chekedTile.x >= topRight.x)
            {
                break;
            }
        }
    }
    return false;
}

bool MovingObject::hasLeftWall(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed)
{
    glm::vec2 oldBottomLeft = glm::vec2(oldPosition.x, oldPosition.y + _mAABB.size.y) - glm::vec2(1.0f, 0.0f);
    glm::vec2 newBottomLeft = glm::vec2(position.x, position.y + _mAABB.size.y) - glm::vec2(1.0f, 0.0f);
    glm::vec2 newTopLeft = glm::vec2(newBottomLeft.x, newBottomLeft.y - _mAABB.size.y);
    
    int endX = mMap->getMapTileXAtPoint(newBottomLeft.x);
    int begX = std::fmax(mMap->getMapTileXAtPoint(oldBottomLeft.x) - 1, endX);
    int dist = std::fmax(std::abs(endX - begX), 1);

    int tileIndexY;
    for (int tileIndexX = begX; tileIndexX >= endX; --tileIndexX)
    {
        glm::vec2 bottomLeft = toolkit::vec2Lerp(newBottomLeft, oldBottomLeft, (float)std::abs(endX - tileIndexX));
        glm::vec2 topLeft = glm::vec2(bottomLeft.x, bottomLeft.y - _mAABB.size.y);

        for (glm::vec2 chekedTile = bottomLeft; ; chekedTile.y += mMap->tileSize.y)
        {
            chekedTile.y = std::fmin(chekedTile.y, topLeft.y);
            tileIndexY = mMap->getMapTileYAtPoint(chekedTile.y);

            if (mMap->isObstacle(tileIndexX, tileIndexY))
            {
                lwallX = (float)tileIndexX * mMap->tileSize.x + mMap->tileSize.x;
                return true;
            }
            if (chekedTile.y >= topLeft.y)
            {
                break;
            }
        }
    }
    return false;
}

bool MovingObject::hasRightWall(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed)
{
    glm::vec2 oldBottomRight = glm::vec2(oldPosition.x, oldPosition.y + _mAABB.size.y) - glm::vec2(1.0f, 1.0f);
    glm::vec2 newBottomRight = glm::vec2(position.x, position.y + _mAABB.size.y) - glm::vec2(1.0f, 1.0f);
    glm::vec2 newTopLeft = glm::vec2(newBottomRight.x, newBottomRight.y - _mAABB.size.y);

    int endX = mMap->getMapTileXAtPoint(newBottomRight.x);
    int begX = std::fmax(mMap->getMapTileXAtPoint(oldBottomRight.x) + 1, endX);
    int dist = std::fmax(std::abs(endX - begX), 1);

    int tileIndexY;
    for (int tileIndexX = begX; tileIndexX >= endX; ++tileIndexX)
    {
        glm::vec2 bottomRight = toolkit::vec2Lerp(newBottomRight, oldBottomRight, (float)std::abs(endX - tileIndexX));
        glm::vec2 topRight = glm::vec2(bottomRight.x, bottomRight.y - _mAABB.size.y);

        for (glm::vec2 chekedTile = bottomRight; ; chekedTile.y += mMap->tileSize.y)
        {
            chekedTile.y = std::fmin(chekedTile.y, topRight.y);
            tileIndexY = mMap->getMapTileYAtPoint(chekedTile.y);

            if (mMap->isObstacle(tileIndexX, tileIndexY))
            {
                rwallX = (float)tileIndexX * mMap->tileSize.x;
                return true;
            }
            if (chekedTile.y >= topRight.y)
            {
                break;
            }
        }
    }
    return false;
}



bool MovingObject::hasWall(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed)
{
    return false;
}

/* for center -> half AABB
bool MovingObject::hasGround(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed)
{
    glm::vec2 oldCenter = oldPosition + mAABBOffset;
    glm::vec2 center = position + mAABBOffset;

    glm::vec2 oldBottomLeft = glm::vec2(oldCenter.x - mAABB.halfSize.x, oldCenter.y + mAABB.halfSize.y) - glm::vec2(0.f, -1.f) + glm::vec2(1.f, 0.f);
    glm::vec2 newBottomLeft = glm::vec2(center.x - mAABB.halfSize.x, center.y + mAABB.halfSize.y) - glm::vec2(0.f, -1.f) + glm::vec2(1.f, 0.f);

    glm::vec2 newBottomRight = glm::vec2(newBottomLeft.x + mAABBOffset.x * 2.0f - 2.0f, newBottomLeft.y);

    int endY = mMap->getMapTileYAtPoint(newBottomLeft.y);
    int begY = std::fmax(mMap->getMapTileYAtPoint(oldBottomLeft.y) - 1, endY);
    int dist = std::fmax(std::abs(endY - begY), 1);

    int tileIndexX;
    for (int tileIndexY = begY; tileIndexY >= endY; --tileIndexY)
    {
        glm::vec2 bottomLeft = toolkit::vec2Lerp(newBottomLeft, oldBottomLeft, (float)std::abs(endY - tileIndexY));
        glm::vec2 bottomRight = glm::vec2(bottomLeft.x + mAABB.halfSize.x * 0.2f - 0.2f, bottomLeft.y);

        for (glm::vec2 chekedTile = bottomLeft; ; chekedTile.x += mMap->tileSize.x)
        {
            chekedTile.x = std::fmin(chekedTile.x, bottomRight.x);
            tileIndexX = mMap->getMapTileXAtPoint(chekedTile.x);
            mGroundY = (float)tileIndexY * mMap->tileSize.y / 2.0f + mMap->mapPosition.y;

            if (mMap->isObstacle(tileIndexX, tileIndexY))
            {
                return true;
            }
            else if (mMap->isGround(tileIndexX, tileIndexY))
            {
                return true;
            }  
            if (chekedTile.x >= bottomRight.x)
            {
                break;
            }
        }
    }

    return false;
}
*/
/*
bool MovingObject::hasGround(glm::vec2 oldPosition, glm::vec2 position, glm::vec2 speed)
{
    glm::vec2 oldCenter = oldPosition + mAABBOffset;
    glm::vec2 center = position + mAABBOffset;

    //glm::vec2 oldBottomLeft = oldCenter - mAABB.halfSize - glm::vec2(0, 1) + glm::vec2(1, 0);
    //glm::vec2 newBottomLeft = center - mAABB.halfSize - glm::vec2(0, 1) + glm::vec2(1, 0);
    //glm::vec2 oldBottomLeft = glm::vec2(oldCenter.x - mAABB.halfSize.x, oldCenter.y - mAABB.halfSize.y) - glm::vec2(0, -1) + glm::vec2(1, 0);
    //glm::vec2 newBottomLeft = glm::vec2(center.x - mAABB.halfSize.x, center.y - mAABB.halfSize.y) - glm::vec2(0, -1) + glm::vec2(1, 0);
    
    glm::vec2 oldBottomLeft = glm::vec2(oldCenter.x - mAABB.halfSize.x, oldCenter.y + mAABB.halfSize.y) - glm::vec2(0, 1) + glm::vec2(1, 0);
    glm::vec2 newBottomLeft = glm::vec2(center.x - mAABB.halfSize.x, center.y + mAABB.halfSize.y) - glm::vec2(0, 1) + glm::vec2(1, 0);
   

    glm::vec2 newBottomRight = glm::vec2(newBottomLeft.x + mAABBOffset.x * 2.0f - 2.0f, newBottomLeft.y);

    int endY = mMap->getMapTileYAtPoint(newBottomLeft.y);
    int begY = std::fmax(mMap->getMapTileYAtPoint(oldBottomLeft.y) - 1, endY);
    int dist = std::fmax(std::abs(endY - begY), 1);

    int tileIndexX;
    for (int tileIndexY = begY; tileIndexY >= endY; --tileIndexY)
    {
        glm::vec2 bottomLeft = toolkit::vec2Lerp(newBottomLeft, oldBottomLeft, (float)std::abs(endY - tileIndexY));
        glm::vec2 bottomRight = glm::vec2(bottomLeft.x + mAABB.halfSize.x * 0.2f - 0.2f, bottomLeft.y);

        for (glm::vec2 chekedTile = bottomLeft; ; chekedTile.x += mMap->tileSize.x)
        {
            chekedTile.x = std::fmin(chekedTile.x, bottomRight.x);
            tileIndexX = mMap->getMapTileXAtPoint(chekedTile.x);
            mGroundY = (float)tileIndexY * mMap->tileSize.y / 2.0f + mMap->mapPosition.y;

            if (mMap->isObstacle(tileIndexX, tileIndexY))
            {
                return true;
            }

            if (chekedTile.x >= bottomRight.x)
            {
                break;
            }
        }
    }

    return false;
}
*/