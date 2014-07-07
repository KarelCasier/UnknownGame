#pragma once

#include "Entity.h"

class Ship;

class Projectile : public Entity
{
public:

	Projectile(Ship& parent, const sf::Texture& texture, sf::Vector2f position, sf::Time life);
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned int	getCategory() const;
	virtual void			updateSelf(sf::Time dt);

	void					destroy();
	sf::Time				getLifeTime() const;

private:

	Ship&					mParent;
	sf::Sprite				mSprite;
	sf::Time				mLife;
};