#include "Entity.h"

Entity::Entity()
: mVelocity(0.f, 0.f)
, mFriction(.99)
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Handled by derived classes
}

void Entity::update(sf::Time dt)
{
	mVelocity *= mFriction;
	this->move(mVelocity * dt.asSeconds());
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