#include "Room.hpp"
#include "Player.hpp"

#include "../Application.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace Game;

namespace
{
	static std::unordered_map<Room::TileType, sf::Color> TileColors = {
		{ Room::Tile_Floor, sf::Color(0,0,0,0) },

		{ Room::Tile_Bar, sf::Color(110, 107, 23) },
		{ Room::Tile_Bottles, sf::Color(110, 107, 23) },
		{ Room::Tile_Seat, sf::Color(171, 89, 16) },
		{ Room::Tile_Table, sf::Color(110, 107, 23) }
	};
}

Room::Room()
{
	auto* ply = addObject<Player>();
	ply->setPosition(0, 1);

	setScale(10);
}

const sf::Vector2u& Room::getSize() const
{
	return mSize;
}
void Room::setSize(const sf::Vector2u& size)
{
	mSize = size;
	mTiles.resize(size.x * size.y);
}
Room::TileType Room::getTile(const sf::Vector2u& pos) const
{
	if (pos.x < mSize.x && pos.y < mSize.y)
	{
		uint32_t i = pos.y * mSize.x + pos.x;
		
		return mTiles[i];
	}

	return Tile_Floor;
}
void Room::setTile(const sf::Vector2u& pos, TileType type)
{
	if (pos.x < mSize.x && pos.y < mSize.y)
	{
		uint32_t i = pos.y * mSize.x + pos.x;

		mTiles[i] = type;
	}
}
float Room::getScale() const
{
	return sf::Transformable::getScale().x;
}
void Room::setScale(float scale)
{
	sf::Transformable::setScale({ scale, scale });
}
void Room::scale(float scale)
{
	sf::Transformable::scale(scale, scale);
}

void Room::update(float dt)
{

	for (auto& ptr : mObjects)
	{
		if (ptr)
			ptr->update(dt);
	}
}

void Room::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform *= getTransform();

	auto circ = sf::CircleShape(5, 8);
	circ.setFillColor(sf::Color::White);
	circ.setScale(0.1f, 0.1f);
	auto rect = sf::RectangleShape(sf::Vector2f{ float(mSize.x), float(mSize.y) });
	rect.setFillColor(sf::Color::White);
	rt.draw(rect, states);

	rect.setSize({ 1, 1 });
	for (uint32_t i = 0; i < mSize.x * mSize.y; ++i)
	{
		auto x = i % mSize.x,
		     y = i / mSize.x;

		auto tile = mTiles[i];
		sf::Shape& toDraw = rect;

		switch (tile)
		{
		case Tile_Bar:
		case Tile_Bottles:
			toDraw = rect; break;

		case Tile_Seat:
			toDraw = circ; break;
		}

		toDraw.setFillColor(TileColors[tile]);
		toDraw.setPosition(x, y);
		rt.draw(rect, states);

	}

	for (auto& ptr : mObjects)
	{
		if (ptr)
			rt.draw(*ptr, states);
	}
}