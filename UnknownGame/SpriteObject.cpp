#include "SpriteObject.h"
#include "Utility.hpp"

SpriteObject::SpriteObject(const sf::Texture& texture)
: mSprite(texture)
{
	centerOrigin(mSprite);
}

SpriteObject::SpriteObject(const sf::Texture& texture, const sf::IntRect& textRect)
: mSprite(texture, textRect)
{
	centerOrigin(mSprite);
}

void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}