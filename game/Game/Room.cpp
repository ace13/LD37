#include "Room.hpp"
#include "Player.hpp"

#include "../Application.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace Game;

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

	auto rect = sf::RectangleShape(sf::Vector2f{ float(mSize.x), float(mSize.y) });
	rect.setFillColor(sf::Color::White);
	rt.draw(rect, states);

	for (auto& ptr : mObjects)
	{
		if (ptr)
			rt.draw(*ptr, states);
	}
}