#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class Entity : public sf::Drawable, public sf::Transformable
{
public:

					Entity();

	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void	update(sf::Time dt);

	void			setVelocity(sf::Vector2f vel);
	void			setVelocity(float x, float y);

private:

	sf::Vector2f	mVelocity;
	float			mFriction;
};