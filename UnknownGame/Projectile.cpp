#include "Projectile.h"
#include "Ship.h"
#include "Utility.hpp"

Projectile::Projectile(Ship& parent, const sf::Texture& texture, sf::Vector2f position, sf::Time life)
: mParent(parent)
, mSprite(texture)
, mLife(life)
{
	centerOrigin(mSprite);
	setPosition(position);
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

unsigned int Projectile::getCategory() const
{
	return Category::PlayerProjectile;
}

void Projectile::updateSelf(sf::Time dt)
{
	mLife -= dt;
	if (mLife <= sf::seconds(0)) //Handled by ship class
	{
		setVelocity(0.f, 0.f);
		destroy();
	}
}

sf::Time Projectile::getLifeTime() const
{
	return mLife;
}

void Projectile::destroy()
{
	mParent.destroyProjectile(this);
}