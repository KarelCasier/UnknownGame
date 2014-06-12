#pragma once

#include "Entity.h"
#include "Projectile.h"
#include <vector>
#include <memory>

class Ship : public Entity
{
	typedef std::unique_ptr<Projectile> ProjectilePtr;

public:
							Ship(const TextureHolder& textures);
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateSelf(sf::Time dt);
	virtual unsigned int	getCategory() const;

	void					attack();

	void					destroy(Projectile* projectile);

private:

	sf::Sprite									mSprite;
	const TextureHolder&						mTextures;
	std::vector<ProjectilePtr>					mProjectiles;

};