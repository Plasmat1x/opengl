#pragma once
#include <cmath>
#include <glm/glm.hpp>

namespace toolkit
{
    /// <summary>
    ///   <para>Spherical collisions</para>
    /// </summary>

    static GLfloat normalize(GLfloat value, GLfloat minValue, GLfloat maxValue)
    {
        GLfloat normValue = 0;

        normValue = (value - minValue) / (maxValue - minValue);

        return normValue;
    }

    static GLfloat clamp01(float value)
    {
        if ((GLdouble)value < 0.0)
            return 0.0f;
        if ((GLdouble)value > 1.0)
            return 1.f;
        return value;
    }

    //linear intorpolation
    static GLfloat lerp(GLfloat a, GLfloat b, GLfloat t)
    {
        return a + (b - a) * clamp01(t);
    }

    // linear interpolation vec2
    static glm::vec2 vec2Lerp(glm::vec2 a, glm::vec2 b, GLfloat t)
    {
        t = clamp01(t);
        return glm::vec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
    }
}





















/*
GLfloat normalize(GLfloat value, GLfloat minValue, GLfloat maxValue)
{
    GLfloat normValue = 0;

    normValue = (value - minValue) / (maxValue - minValue);

    return normValue;
}
*/

    /*
    bool AABB(Entity* target1, Entity* target2)
    {
        if (target1->getCollisionModel().x < target2->getCollisionModel().x + target2->getCollisionModel().z &&
            target1->getCollisionModel().x + target1->getCollisionModel().z > target2->getCollisionModel().x &&
            target1->getCollisionModel().y < target2->getCollisionModel().y + target2->getCollisionModel().w &&
            target1->getCollisionModel().y + target1->getCollisionModel().w > target2->getCollisionModel().y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool PredictionYAABB(Player* target1, Entity* target2)
    {
        if (target1->getCollisionModel().x < target2->getCollisionModel().x + target2->getCollisionModel().z &&
            target1->getCollisionModel().x + target1->getCollisionModel().z > target2->getCollisionModel().x &&
            target1->getCollisionModel().y + target1->speed.y < target2->getCollisionModel().y + target2->getCollisionModel().w &&
            target1->getCollisionModel().y + target1->getCollisionModel().w + target1->speed.y > target2->getCollisionModel().y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool PredictionXAABB(Player* target1, Entity* target2)
    {
        if (target1->getCollisionModel().x + target1->speed.x < target2->getCollisionModel().x + target2->getCollisionModel().z &&
            target1->getCollisionModel().x + target1->getCollisionModel().z + target1->speed.x > target2->getCollisionModel().x &&
            target1->getCollisionModel().y < target2->getCollisionModel().y + target2->getCollisionModel().w &&
            target1->getCollisionModel().y + target1->getCollisionModel().w > target2->getCollisionModel().y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }



    bool YAABB(Player* target1, Entity* target2)
    {
        if (target1->getCollisionModel().x < target2->getCollisionModel().x + target2->getCollisionModel().z &&
            target1->getCollisionModel().x + target1->getCollisionModel().z > target2->getCollisionModel().x &&
            target1->getCollisionModel().y < target2->getCollisionModel().y + target2->getCollisionModel().w &&
            target1->getCollisionModel().y + target1->getCollisionModel().w > target2->getCollisionModel().y)
        {
            target1->position.y = target2->getCollisionModel().y - target1->getCollisionModel().w;
            target1->speed.y = 0.0f;
            return true;
        }
        else
        {
            target1->speed.y ++;
            return false;
        }
    }

    bool XAABB(Player* target1, Entity* target2)
    {
        if (target1->getCollisionModel().x < target2->getCollisionModel().x + target2->getCollisionModel().z &&
            target1->getCollisionModel().x + target1->getCollisionModel().z > target2->getCollisionModel().x &&
            target1->getCollisionModel().y < target2->getCollisionModel().y + target2->getCollisionModel().w &&
            target1->getCollisionModel().y + target1->getCollisionModel().w > target2->getCollisionModel().y)
        {
            target1->position.x = target2->getCollisionModel().x - target1->getCollisionModel().z;
            target1->speed.x = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool groundCollision(Player* target1, Entity* target2)
    {
        //target1->position.y += target1->speed.y;

        if (target1->getCollisionModel().x < target2->getCollisionModel().x + target2->getCollisionModel().z &&
            target1->getCollisionModel().x + target1->getCollisionModel().z > target2->getCollisionModel().x &&
            target1->getCollisionModel().y < target2->getCollisionModel().y + target2->getCollisionModel().w &&
            target1->getCollisionModel().y + target1->getCollisionModel().w > target2->getCollisionModel().y)
        {
            target1->position.y = target2->getCollisionModel().y - target1->getCollisionModel().w;
            target1->speed.y = 0.0f;
            target1->jumping = false;
            target1->onGround = true;
            return true;
        }
        else
        {
            target1->speed.y ++;
            return false;
        }
    }
    */


/*
    bool YAABB(Player* target1, Entity* target2)
    {
        if (target1->getCollisionModel().x < target2->getCollisionModel().x + target2->getCollisionModel().z &&
            target1->getCollisionModel().x + target1->getCollisionModel().z > target2->getCollisionModel().x &&
            target1->getCollisionModel().y < target2->getCollisionModel().y + target2->getCollisionModel().w &&
            target1->getCollisionModel().y + target1->getCollisionModel().w > target2->getCollisionModel().y)
        {
            target1->position.y = target2->getCollisionModel().y - target1->getCollisionModel().w;
            target1->speed.y = 0;
            return true;
        }
        else
        {
            target1->speed.y ++;
            return false;
        }
    }

    bool XAABB(Player* target1, Entity* target2)
    {
        if (target1->getCollisionModel().x < target2->getCollisionModel().x + target2->getCollisionModel().z &&
            target1->getCollisionModel().x + target1->getCollisionModel().z > target2->getCollisionModel().x &&
            target1->getCollisionModel().y < target2->getCollisionModel().y + target2->getCollisionModel().w &&
            target1->getCollisionModel().y + target1->getCollisionModel().w > target2->getCollisionModel().y)
        {
            target1->position.x = target2->getCollisionModel().x - target1->getCollisionModel().z;
            target1->speed.x = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    target1->position.y += target1->speed.y;

        if (target1->getCollisionModel().y + target1->getCollisionModel().w > target2->getCollisionModel().y)
        {
            target1->position.y = target2->getCollisionModel().y - target1->getCollisionModel().w;
            target1->speed.y = 0.0f;
            target1->jump = true;
            return true;
        }
        else
        {
            target1->speed.y += 0.01f;
            return false;
        }
*/

/*
bool AABB(Entity* target1, Entity* target2)
{
    if (target1->getPosition().x                                                            < target2->getPosition().x + target2->getSize().x * target2->getSprite().getScale().x &&
        target1->getPosition().x + target1->getSize().x * target1->getSprite().getScale().x > target2->getPosition().x &&
        target1->getPosition().y                                                            < target2->getPosition().y + target2->getSize().y * target2->getSprite().getScale().y &&
        target1->getPosition().y + target1->getSize().y * target1->getSprite().getScale().y > target2->getPosition().y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
*/