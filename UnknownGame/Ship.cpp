#include "Ship.h"
#include "Utility.hpp"


Ship::Ship(const TextureHolder& textures)
{
	mSprite.setTexture(textures.get(TextureID::PlayerShip));
	mSprite.setScale(0.5, 0.5);
	centerOrigin(mSprite);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

unsigned int Ship::getCategory() const
{
	return Category::PlayerShip;
}