#include "Ship.h"
#include "Utility.hpp"

const sf::Texture& Ship::getSpriteTexture(TypeID type)
{
	switch (type)
	{
	case TypeID::Player:
		return mTextures.get(TextureID::PlayerShip);
	case TypeID::Enemy:
		return mTextures.get(TextureID::EnemyShip);
	}
}

const sf::Texture& Ship::getShadowTexture(TypeID type)
{
	switch (type)
	{
	case TypeID::Player:
		return mTextures.get(TextureID::PlayerShipShadow);
	case TypeID::Enemy:
		return mTextures.get(TextureID::EnemyShipShadow);
	}
}

Ship::Ship(const TextureHolder& textures, TypeID type)
: mTextures(textures)
, mType(type)
, mReloadCooldown(sf::seconds(1))
{
	mSprite.setTexture(getSpriteTexture(type));
	mSprite.setScale(0.5, 0.5);
	centerOrigin(mSprite);

	mShadow.setTexture(getShadowTexture(type));
	mShadow.setScale(0.5, 0.5);
	centerOrigin(mShadow);
	mShadow.setPosition(mSprite.getPosition() + sf::Vector2f(10.f, -10.f));
	mShadow.setRotation(10);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mShadow);
	target.draw(mSprite, states);

	for (const Projectile* projectile : mProjectiles)
	{
		target.draw(*projectile);
	}
}

void Ship::updateSelf(sf::Time dt)
{
	mShadow.setRotation(this->getRotation());
	mShadow.setPosition(this->getPosition() + sf::Vector2f(10.f, -10.f));

	for (Projectile* projectile : mProjectiles)
	{
		projectile->update(dt);
	}

	while (!mProjectilesToDelete.empty())
	{
		Projectile* projectileToDelete = mProjectilesToDelete.back();
		mProjectilesToDelete.pop_back();
		mProjectiles.erase(std::remove(mProjectiles.begin(), mProjectiles.end(), projectileToDelete), mProjectiles.end());
		delete projectileToDelete;
	}

	//Add elapsed time to attack Timer
	mTimeSinceLastFire += dt;
}

unsigned int Ship::getCategory() const
{
	switch (mType)
	{
	case Ship::TypeID::Player:
		return Category::PlayerShip;
	case Ship::TypeID::Enemy:
		return Category::EnemyShip;
	default:
		break;
	}
}

void Ship::fire()
{
	if (mTimeSinceLastFire >= mReloadCooldown)
	{
		//std::unique_ptr<Projectile> newProjectile(new Projectile(*this, mTextures.get(TextureID::CannonBall), getPosition(), sf::seconds(2)));
		//Projectile 1;
		Projectile* firstProjectile = new Projectile(*this, mTextures.get(TextureID::CannonBall), getPosition(), sf::seconds(1));
		firstProjectile->disableFriction();
		firstProjectile->setRotation(this->getRotation()- 90);
		firstProjectile->accelerate(500.f);
		//mProjectiles.push_back(std::move(newProjectile));
		mProjectiles.push_back(firstProjectile);

		//Projectile 2;
		Projectile* secondProjectile = new Projectile(*this, mTextures.get(TextureID::CannonBall), getPosition(), sf::seconds(1));
		secondProjectile->disableFriction();
		secondProjectile->setRotation(this->getRotation() + 90);
		secondProjectile->accelerate(500.f);
		mProjectiles.push_back(secondProjectile);

		mTimeSinceLastFire = sf::seconds(0);
	}
}

void Ship::destroyProjectile(Projectile* projectile)
{
	mProjectilesToDelete.push_back(projectile);
}