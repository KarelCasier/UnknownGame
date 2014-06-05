#pragma once

#include "Entity.h"

class SpriteObject : public Entity
{
public:
					SpriteObject(const sf::Texture& texture);
					SpriteObject(const sf::Texture& texture, const sf::IntRect& textRect);
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int	getCategory() const;


private:
	sf::Sprite		mSprite;

};