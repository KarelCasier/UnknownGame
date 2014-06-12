#include "GameState.h"

struct ShipMover
{
	ShipMover(float v)
	:speed(v)
	{
	}

	void operator() (Ship& ship, sf::Time) const
	{
		ship.accelerate(speed);
	}

	float speed;
};

struct ShipRotater
{
	ShipRotater(float a)
	:angle(a)
	{
	}

	void operator() (Ship& ship, sf::Time) const
	{
		ship.rotate(angle);
	}

	float angle;
};

struct ShipAttack
{
	ShipAttack()
	{
	}

	void operator() (Ship& ship, sf::Time) const
	{
		ship.attack();
	}
};


GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	//Real Time Events - Act while key pressed
	CommandQueue& commands = mWorld.getCommandQueue();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Accelerate
	{
		Command accelerateCommand;
		accelerateCommand.category = Category::PlayerShip;
		accelerateCommand.action = derivedAction<Ship>(ShipMover(2));
		commands.push(accelerateCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Rotate left
	{
		Command rotateCommand;
		rotateCommand.category = Category::PlayerShip;
		rotateCommand.action = derivedAction<Ship>(ShipRotater(-.3));
		commands.push(rotateCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Rotate right
	{
		Command rotateCommand;
		rotateCommand.category = Category::PlayerShip;
		rotateCommand.action = derivedAction<Ship>(ShipRotater(.3));
		commands.push(rotateCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //Fire
	{
		Command fireCommand;
		fireCommand.category = Category::PlayerShip;
		fireCommand.action = derivedAction<Ship>(ShipAttack());
		commands.push(fireCommand);
	}
	

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling - Act when key pressed
	CommandQueue& commands = mWorld.getCommandQueue();
	//mPlayer.handleEvent(event, commands);

	// P pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		requestStackPush(StateID::Pause);

	return true;
}
