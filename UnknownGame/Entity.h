#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include "Category.h"
#include "CommandQueue.hpp"

class Entity : public sf::Drawable, public sf::Transformable
{
public:

							Entity();

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			update(sf::Time dt);
	virtual void			updateSelf(sf::Time dt);

	virtual unsigned int	getCategory() const;

	void					onCommand(Command& command, sf::Time dt);

	void				setVelocity(sf::Vector2f vel);
	void				setVelocity(float x, float y);
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float v);
	void				enableFriction();
	void				disableFriction();
	void				enableGravity();
	void				disableGravity();

	sf::Vector2f		getVelocity() const;

private:

	static const double	FRICTION;
	static const double	GRAVITY;

	float				mMaxSpeed;
	sf::Vector2f		mVelocity;
	bool				hasFriction;
	bool				hasGravity;
};
