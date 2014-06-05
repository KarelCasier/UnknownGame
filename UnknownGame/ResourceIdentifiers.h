#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

enum class TextureID
{
	//Tiles
	WaterTile,

	//Ship
	PlayerShip,
};

enum class FontID
{
	Main,
};

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, TextureID>	TextureHolder;
typedef ResourceHolder<sf::Font, FontID>		FontHolder;