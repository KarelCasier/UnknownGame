#include "Ship.h"
#include "Utility.hpp"


Ship::Ship(const TextureHolder& textures)
:mTextures(textures)
{
	mSprite.setTexture(textures.get(TextureID::PlayerShip));
	mSprite.setScale(0.5, 0.5);
	centerOrigin(mSprite);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);

	for (const ProjectilePtr& projectile : mProjectiles)
	{
		target.draw(*projectile);
	}
}

void Ship::updateSelf(sf::Time dt)
{
	for (const ProjectilePtr& projectile : mProjectiles)
	{
		projectile->update(dt);
	}
}

unsigned int Ship::getCategory() const
{
	return Category::PlayerShip;
}

void Ship::attack()
{
	std::unique_ptr<Projectile> newProjectile(new Projectile(*this, mTextures.get(TextureID::CannonBall), getPosition(), sf::seconds(2)));
	newProjectile->setVelocity(sf::Vector2f(500, 0));
	mProjectiles.push_back(std::move(newProjectile));
}

void Ship::destroy(Projectile* projectile)
{
	/*for (std::vector<ProjectilePtr>::iterator iter = mProjectiles.begin(); iter != mProjectiles.end(); ++iter)
	{
		if ((*iter).get() == projectile)
		{
			mProjectiles.erase(iter);
		}
	}*/
	int location = 0;
	for (ProjectilePtr& proj : mProjectiles)
	{
		if (proj.get() == projectile)
		{
			mProjectiles.erase(mProjectiles.begin() + location);
		}
		location++;
	}
}