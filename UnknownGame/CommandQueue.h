#pragma once

#include "Category.h"

class Entity;

#include <SFML/System/Time.hpp>
#include <functional>
#include <queue>

struct Command
{
															Command();
	std::function < void(Entity* object, sf::Time dt) >		action;
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