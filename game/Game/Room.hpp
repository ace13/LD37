#pragma once

#include "Object.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <deque>
#include <list>
#include <memory>
#include <vector>

namespace Game
{

class Player;

class Room : public sf::Drawable, public sf::Transformable
{
public:
	enum TileType : uint8_t
	{
		Tile_Floor,

		Tile_Bar,
		Tile_Bottles,
		Tile_Taps,
		Tile_Sink,

		Tile_Seat,
		Tile_Stool,
		Tile_Table,

		Tile_Count
	};

	Room();

	const sf::Vector2u& getSize() const;
	void setSize(const sf::Vector2u& size);

	Player* getPlayer() const;
	Object* getObject(const sf::Vector2u& pos) const;
	TileType getTile(const sf::Vector2u& pos) const;
	void setTile(const sf::Vector2u& pos, TileType type);

	void resetClock(float start = -30);
	void depopulate();
	void repopulate();

	float getScale() const;
	void setScale(float scale);
	void scale(float scale);

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	template<typename T, typename... Args>
	T* addObject(Args&&...);
	void removeObject(Object* obj);

private:
	sf::Vector2u mSize;
	std::vector<TileType> mTiles;
	
	bool mStarted;
	float mClock, mPopulateCD;

	std::deque<std::unique_ptr<Object>> mObjects;
	std::list<std::deque<std::unique_ptr<Object>>::iterator> mToDelete;
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
