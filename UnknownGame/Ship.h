#pragma once

#include "Entity.h"

class Ship : public Entity
{
public:

					Ship(const TextureHolder& textures);

	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:

	sf::Sprite		mSprite;
};