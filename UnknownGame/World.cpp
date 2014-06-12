#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>

#include "iostream"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mWorldBounds(0.f, 0.f, 10000.f, 10000.f)
{
	loadTextures();
	buildScene();
}

void World::update(sf::Time dt)
{
	//Center view on player
	mWorldView.setCenter(mPlayerShip->getPosition());

	//Handle all commands
	while (!mCommandQueue.isEmpty())
	{
		Command command = mCommandQueue.pop();
		for (const Ptr& object : mGameObjects)
		{
			object->onCommand(command, dt);
		}
		
	}

	// Apply movements
	for (const Ptr& object : mGameObjects)
	{
		object->update(dt);
	}
}

void World::draw()
{
	mWindow.setView(mWorldView);
	
	for (const Ptr&  object: mGameObjects)
	{
		mWindow.draw(*object);
	}
}


void World::loadTextures()
{
	//Player
	mTextures.load(TextureID::PlayerShip, "assets/textures/PlayerShip.png");

	//Water
	mTextures.load(TextureID::WaterTile, "assets/textures/WaterTile.png");

	//Projectile
	mTextures.load(TextureID::CannonBall, "assets/textures/CannonBall.png");

}

void World::buildScene()
{
	//Prepare the tiled background
	sf::Texture& waterTexture = mTextures.get(TextureID::WaterTile);
	sf::IntRect waterTextureRectangle(mWorldBounds);
	waterTexture.setRepeated(true);

	//Create a unique_ptr to hold the sprite
	std::unique_ptr<SpriteObject> waterSprite(new SpriteObject(waterTexture, waterTextureRectangle));
	mGameObjects.push_back(std::move(waterSprite)); //Move ownership to vector

	std::unique_ptr<Ship> playerShip(new Ship(mTextures));
	mPlayerShip = playerShip.get();
	mGameObjects.push_back(std::move(playerShip));

}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}