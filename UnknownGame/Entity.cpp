#include "Entity.h"
#include <math.h>

const double Entity::FRICTION = .99;
const double Entity::GRAVITY = 200;

Entity::Entity()
: mVelocity(0.f, 0.f)
, hasFriction(true)
, hasGravity(false)
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Handled by derived classes
}

void Entity::update(sf::Time dt)
{
	if (hasFriction)
	{
		mVelocity.x *= FRICTION;
		mVelocity.y *= FRICTION;
	}
	if (hasGravity)
	{
		mVelocity.y += GRAVITY * dt.asSeconds();
	}
	move(mVelocity * dt.asSeconds());
}

void Entity::setVelocity(sf::Vector2f vel)
{
	mVelocity = vel;
}

void Entity::setVelocity(float x, float y)
{
	mVelocity.x = x;
	mVelocity.y = y;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float v)
{
	if (sqrt(pow(mVelocity.x, 2) + pow(mVelocity.y, 2)) <= mMaxSpeed)
	{
		mVelocity.x += v * (cos((this->getRotation() - 90) * 3.14159 / 180));
		mVelocity.y += v * (sin((this->getRotation() - 90) * 3.14159 / 180));
	}
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

unsigned int Entity::getCategory() const
{
	return Category::None;
}

void Entity::onCommand(Command& command, sf::Time dt)
{
	if (command.category & this->getCategory())
	{
		command.action(*this, dt);
	}
}

void Entity::enableFriction()
{
	hasFriction = true;
}

void Entity::enableGravity()
{
	hasGravity = true;
}
