#pragma once

#include "Object.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <deque>
#include <memory>
#include <vector>

namespace Game
{

class Room : public sf::Drawable, public sf::Transformable
{
public:
	enum TileType : uint8_t
	{
		Tile_Floor,

		Tile_Bar,
		Tile_Bottles,
		Tile_Seat,
		Tile_Table,

		Tile_Count
	};

	Room();

	const sf::Vector2u& getSize() const;
	void setSize(const sf::Vector2u& size);

	TileType getTile(const sf::Vector2u& pos) const;
	void setTile(const sf::Vector2u& pos, TileType type);

	float getScale() const;
	void setScale(float scale);
	void scale(float scale);

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	template<typename T, typename... Args>
	T* addObject(Args&&...);

private:
	sf::Vector2u mSize;
	std::vector<TileType> mTiles;

	std::deque<std::unique_ptr<Object>> mObjects;
};

}

template<typename T, typename... Args>
T* Game::Room::addObject(Args&&... args)
{
	auto unique = std::make_unique<T>(std::forward<Args>(args)...);
	unique->setRoom(this);
	auto ptr = unique.get();
	mObjects.emplace_back(std::move(unique));
	return ptr;
}
