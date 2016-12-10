#pragma once

#include "Object.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <deque>
#include <memory>

namespace Game
{

class Room : public sf::Drawable, public sf::Transformable
{
public:
	Room();

	const sf::Vector2u& getSize() const;
	void setSize(const sf::Vector2u& size);

	float getScale() const;
	void setScale(float scale);
	void scale(float scale);

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	template<typename T, typename... Args>
	T* addObject(Args&&...);

private:
	sf::Vector2u mSize;
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
