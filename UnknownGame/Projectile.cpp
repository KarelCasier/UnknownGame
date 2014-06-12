#include "Projectile.h"
#include "Ship.h"

Projectile::Projectile(Ship& parent, const sf::Texture& texture, sf::Vector2f position, sf::Time life)
: mParent(parent)
, mSprite(texture)
, mLife(life)
{
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
	if (mLife <= sf::seconds(0))
		destroy();
}

void Projectile::destroy()
{
	mParent.destroy(this);
}