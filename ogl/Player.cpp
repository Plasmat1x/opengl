#include "Player.h"
#include "AnimationManager.h"
#include "ResourceManager.h"

Player::Player(glm::vec2 position, glm::vec2 size, std::string texture) :
    Entity(position, size, texture),
    MovingObject(),
    currentState(IDLE),
    direction(_RIGHT),
    curInput(NPK)
{
    mPosition = position;
    _mAABB.size = size;
    _mAABB.min = glm::vec2(mPosition.x, mPosition.y + _mAABB.size.y);
    _mAABB.max = glm::vec2(mPosition.x + _mAABB.size.x, mPosition.y);

    mSpeed = speed;
    mScale = glm::vec2(1.0f);
}


Player::~Player()
{
}

void Player::setupCollisionModel(glm::vec2 size)
{
    this->collisionModelSize = size;
    //this->collisionModelSize_in = this->position.x + ((this->size.x / 2) - size.x / 2);
    this->collisionModelSize_in =((this->size.x / 2) - size.x / 2);

    collisionModel = glm::vec4(
        this->position.x + ((this->size.x / 2) - size.x / 2),
        this->position.y + size.y,
        this->position.x + ((this->size.x / 2) - size.x / 2) + size.x,
        this->position.y
        );

    _mAABB.size = collisionModelSize;

    _mAABB.min = glm::vec2(collisionModel.x, collisionModel.y);
    _mAABB.max = glm::vec2(collisionModel.z, collisionModel.w);
}

void Player::update(float deltaTime)
{
    //std::cout << mPosition.x << " | " << mPosition.y << std::endl;
    position = mPosition;
    characterUpdate(deltaTime);
    updatePhysics(deltaTime);

    collisionModel = glm::vec4(
        this->position.x + ((this->size.x / 2) - collisionModelSize.x / 2),
        this->position.y + collisionModelSize.y,
        this->position.x + ((this->size.x / 2) - collisionModelSize.x / 2) + collisionModelSize.x,
        this->position.y
    );
    _mAABB.min = glm::vec2(collisionModel.x, collisionModel.y);
    _mAABB.max = glm::vec2(collisionModel.z, collisionModel.w);

    updatePrevInput(deltaTime);
}

void Player::characterUpdate(float deltaTime)
{
    switch (currentState)
    {
    case IDLE:
        mSpeed = glm::vec2(0.0f);
        if (direction == _RIGHT) animation_idle.playAnimation("idle", deltaTime, sprite);
        else if (direction == _LEFT) animation_idle.playAnimation("_idle", deltaTime, sprite);

        if (!mOnGround)
        {
            currentState = FALL;
            break;
        }

        if ((mInputs[(int)RIGHT]) != (mInputs[(int)LEFT]))
        {
            currentState = RUN;
            break;
        }
        else if ((mInputs[(int)UP]))
        {
            mSpeed.y = -1.0f*speed.y;
            currentState = JUMP;
            break;
        }
        if ((mInputs[(int)DOWN]))
        {
            if(onWayPlatform)
                mPosition.y += oneWayThreshold;
        }
        break;
    case RUN:
        if (direction == _RIGHT) animation_run.playAnimation("run", deltaTime, sprite);
        else if (direction == _LEFT) animation_run.playAnimation("_run", deltaTime, sprite);

        if (!(mInputs[(int)LEFT]) && !(mInputs[(int)RIGHT]))
        {
            currentState = IDLE;
            mSpeed = glm::vec2(0, 0);
            break;
        }
        else if ((mInputs[(int)RIGHT]))
        {
            direction = _RIGHT;
            if (mPushedRightWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = speed.x;
            }
            mScale.x = std::abs(mScale.x);
        }
        else if ((mInputs[(int)LEFT]))
        {
            direction = _LEFT;
            if (mPushedLeftWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = -speed.x;
            }
            mScale.x = -std::abs(mScale.x);
        } 
        if ((mInputs[(int)UP]))
        {
            mSpeed.y = -1.0f*speed.y;
            currentState = JUMP;
            break;
        }
        else if (!mOnGround || mSpeed.y > 0)
        {
            currentState = FALL;
            break;
        }
        if ((mInputs[(int)DOWN]))
        {
            if (onWayPlatform)
                mPosition.y += oneWayThreshold;
        }
        break;
    case JUMP:
        if (direction == _RIGHT) animation_jump.playAnimation("jump", deltaTime, sprite);
        else if (direction == _LEFT) animation_jump.playAnimation("_jump", deltaTime, sprite);

        mSpeed.y += std::fmax(1.0f * deltaTime, 10.0f);
        if (!(mInputs[(int)LEFT]) && !(mInputs[(int)RIGHT]))
        {
            mSpeed.x = 0.0f;
        }
        else if ((mInputs[(int)RIGHT]))
        {
            direction = _RIGHT;
            if (mPushedRightWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = speed.x;
            }
            mScale.x = std::abs(mScale.x);
        }
        else if ((mInputs[(int)LEFT]))
        {
            direction = _LEFT;
            if (mPushedLeftWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = -speed.x;
            }
            mScale.x = -std::abs(mScale.x);
        }
        if (!(mInputs[(int)UP]) && mSpeed.y < 0.0f)
        {
            mSpeed.y = std::fmin(mSpeed.y, 5.0f);
        }
        if (mSpeed.y > 0 && !mOnGround)
        {
            currentState = FALL;
        }
        if (mOnGround)
        {
            currentState = IDLE;
        }

        break;
    case WALL:
        break;
    case FALL:
        if (direction == _RIGHT) animation_fall.playAnimation("fall", deltaTime, sprite);
        else if (direction == _LEFT) animation_fall.playAnimation("_fall", deltaTime, sprite);

        mSpeed.y += std::fmax(1.0f * deltaTime, 20.0f);

        if (!(mInputs[(int)LEFT]) && !(mInputs[(int)RIGHT]))
        {
            mSpeed.x = 0.0f;
        }
        else if ((mInputs[(int)RIGHT]))
        {
            direction = _RIGHT;
            if (mPushedRightWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = speed.x;
            }
            mScale.x = std::abs(mScale.x);
        }
        else if ((mInputs[(int)LEFT]))
        {
            direction = _LEFT;
            if (mPushedLeftWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = -speed.x;
            }
            mScale.x = -std::abs(mScale.x);
        }
        if (!(mInputs[(int)UP]) && mSpeed.y < 0.0f)
        {
            mSpeed.y = std::fmin(mSpeed.y, 5.0f);
        }
        if (mOnGround)
        {
            mSpeed.y = 0.0f;
            currentState = IDLE;
        }
        break;
    }
}

void Player::updatePrevInput(float deltaTime)
{
    auto c = (GLbyte)count;

    for (GLbyte i = 0; i < count; ++i)
    {
        mPrevInputs[i] = mInputs[i];
        mInputs[i] = false;
    }
}


void Player::draw()
{
    this->sprite.setPosition(glm::vec2(this->position.x - collisionModelSize_in,this->position.y));
    this->sprite.setSize(this->size);
    this->sprite.draw();
}

bool Player::released(KeyInput key)
{
    return (!mInputs[(int)key] && mPrevInputs[(int)key]);
}

bool Player::keyState(KeyInput key)
{
    return (mInputs[(int)key]);
}

bool Player::pressed(KeyInput key)
{
    return (mInputs[(int)key] && !mPrevInputs[(int)key]);
}


/*
case IDLE:
        mSpeed = glm::vec2(0.0f);
        if(direction == _RIGHT) animation_idle.playAnimation("idle", deltaTime, sprite);
        else if (direction == _LEFT) animation_idle.playAnimation("_idle", deltaTime, sprite);

        if (!mOnGround)
        {
            currentState = FALL;
            break;
        }

        if ((curInput == RIGHT ) != (curInput == LEFT))
        {
            currentState = RUN;
            break;
        }
        else if ((curInput == UP))
        {
            mSpeed.y = speed.y;
            currentState = JUMP;
            break;
        }
        break;
    case RUN:
        if (direction == _RIGHT) animation_run.playAnimation("run", deltaTime, sprite);
        else if (direction == _LEFT) animation_run.playAnimation("_run", deltaTime, sprite);

        if (!(curInput == RIGHT) || !(curInput == LEFT))
        {
            currentState = IDLE;
            mSpeed = glm::vec2(0, 0);
            break;
        }
        else if ((curInput == RIGHT))
        {
            direction = _RIGHT;
            if (mPushedRightWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = speed.x;
            }
            mScale.x = std::abs(mScale.x);
        }
        else if (keyState(LEFT))
        {
            direction = _LEFT;
            if (mPushedLeftWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = -speed.x;
            }
            mScale.x = -std::abs(mScale.x);
        }

        if (keyState(UP))
        {
            mSpeed.y = speed.y;
            currentState = JUMP;
            break;
        }
        else if (!mOnGround)
        {
            currentState = FALL;
            break;
        }
        break;
    case JUMP:
        if (direction == _RIGHT) animation_idle.playAnimation("idle", deltaTime, sprite);
        else if (direction == _LEFT) animation_idle.playAnimation("_idle", deltaTime, sprite);

        mSpeed.y += std::fmax(1.0f * deltaTime, 5.0f);
        if (!keyState(RIGHT) || !keyState(LEFT))
        {
            mSpeed = glm::vec2(0, 0);
        }
        else if (keyState(RIGHT))
        {
            direction = _RIGHT;
            if (mPushedRightWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = speed.x;
            }
            mScale.x = std::abs(mScale.x);
        }
        else if (keyState(LEFT))
        {
            direction = _LEFT;
            if (mPushedLeftWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = -speed.x;
            }
            mScale.x = -std::abs(mScale.x);
        }
        if (!keyState(UP) && mSpeed.y > 0.0f)
        {
            mSpeed.y = std::fmin(mSpeed.y, 4.0f);
        }
        if (mSpeed.y > 0)
        {
            currentState = FALL;
        }

        break;
    case WALL:
        break;
    case FALL:
        if (direction == _RIGHT) animation_idle.playAnimation("idle", deltaTime, sprite);
        else if (direction == _LEFT) animation_idle.playAnimation("_idle", deltaTime, sprite);

        mSpeed.y += std::fmax(1.0f * deltaTime, 5.0f);

        if (!keyState(RIGHT) || !keyState(LEFT))
        {
            mSpeed = glm::vec2(0, 0);
        }
        else if (keyState(RIGHT))
        {
            direction = _RIGHT;
            if (mPushedRightWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = speed.x;
            }
            mScale.x = std::abs(mScale.x);
        }
        else if (keyState(LEFT))
        {
            direction = _LEFT;
            if (mPushedLeftWall)
            {
                mSpeed.x = 0.0f;
            }
            else
            {
                mSpeed.x = -speed.x;
            }
            mScale.x = -std::abs(mScale.x);
        }
        if (!keyState(UP) && mSpeed.y > 0.0f)
        {
            mSpeed.y = std::fmin(mSpeed.y, 4.0f);
        }
        if (mOnGround)
        {
            currentState = IDLE;
        }
        break;
    }
*/