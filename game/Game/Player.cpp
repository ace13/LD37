#include "Player.hpp"
#include "Patron.hpp"

#include "../Application.hpp"
#include "../Inputs.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

using namespace Game;

void Player::update(float dt)
{
	auto& inp = Application::getApplication()->getInputManager();

	auto pos = getPosition();
	auto& size = getRoom().getSize();

	if (inp[Input_Left].pressed() && pos.x > 0)
		--pos.x;
	if (inp[Input_Right].pressed() && pos.x + 1 < size.x)
		++pos.x;
	if (inp[Input_Up].pressed() && pos.y > 0)
		--pos.y;
	if (inp[Input_Down].pressed() && pos.y + 1 < size.y)
		++pos.y;
	
	auto tile = getRoom().getTile({ uint32_t(pos.x), uint32_t(pos.y) });
	if (tile == Room::Tile_Floor)
		setPosition(pos);
	else if (!mCarried)
	{
		if (tile == Room::Tile_Bottles)
			mCarried = std::make_unique<Drink>(Drink_Cocktail);
		else if (tile == Room::Tile_Taps)
			mCarried = std::make_unique<Drink>(Drink_Beer);
		else if (tile == Room::Tile_Sink)
			mCarried = std::make_unique<Drink>(Drink_Water);
	}
	else
	{
		if (tile == Room::Tile_Sink)
			mCarried.reset(nullptr);
		else if (tile == Room::Tile_Seat || tile == Room::Tile_Stool)
		{
			auto* target = dynamic_cast<Patron*>(getRoom().getObject(sf::Vector2u(pos)));
			
			if (target && target->getOrder().getType() == mCarried->getType())
				mCarried.reset(nullptr);
		}
		else if (tile == Room::Tile_Bar || tile == Room::Tile_Table)
		{
			// TODO: Delta * 2
		}
	}
}
void Player::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform *= getTransform();

	auto rect = sf::RectangleShape({ 1, 1 });
	rect.setFillColor(sf::Color::Blue);

	rt.draw(rect, states);

	if (mCarried)
	{
		auto& drink = *mCarried;

		rt.draw(drink, states);
	}
}

