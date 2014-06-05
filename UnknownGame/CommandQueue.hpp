#pragma once

#include "Category.h"

class Entity;

#include <SFML/System/Time.hpp>
#include <functional>
#include <queue>

struct Command
{
															Command();
	std::function < void(Entity& object, sf::Time dt) >		action;
	unsigned int											category;
};

class CommandQueue
{
public:
	void					push(const Command& c);
	Command					pop();
	bool					isEmpty() const;

private:
	std::queue<Command>		mQueue;
};

template <typename GameObject, typename Function>
std::function<void(Entity&, sf::Time)> derivedAction(Function fn)
{
	return [=](Entity& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}