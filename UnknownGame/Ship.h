#pragma once

#include "Entity.h"
#include "Projectile.h"
#include <vector>
#include <memory>

class Ship : public Entity
{
	typedef std::unique_ptr<Projectile> ProjectilePtr;

public:
	enum class TypeID
	{
		Player,
		Enemy,
	};
							Ship(const TextureHolder& textures, TypeID type);
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateSelf(sf::Time dt);
	virtual unsigned int	getCategory() const;

	void					fire();

	void					destroyProjectile(Projectile* projectile);

	std::vector<Projectile*>					mProjectiles;

private:

	const sf::Texture&			getSpriteTexture(TypeID type);
	const sf::Texture&			getShadowTexture(TypeID type);

private:

	sf::Sprite									mSprite;
	sf::Sprite									mShadow;
	const TextureHolder&						mTextures;
	TypeID										mType;
	sf::Time									mReloadCooldown;
	sf::Time									mTimeSinceLastFire;
	std::vector<Projectile*>					mProjectilesToDelete;

};