#include "Player.hpp"
#include "Patron.hpp"

#include "../Application.hpp"
#include "../Inputs.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

using namespace Game;

Player::Player()
	: mMoney(100)
{

}

void Player::update(float dt)
{
	auto& inp = Application::getApplication()->getInputManager();

	auto& size = getRoom().getSize();
	sf::Vector2u pos = sf::Vector2u(getPosition());
	sf::Vector2u delta;

	if (inp[Input_Left].pressed() && pos.x > 0)
		--delta.x;
	if (inp[Input_Right].pressed() && pos.x + 1 < size.x)
		++delta.x;
	if (inp[Input_Up].pressed() && pos.y > 0)
		--delta.y;
	if (inp[Input_Down].pressed() && pos.y + 1 < size.y)
		++delta.y;
	
	auto newPos = pos + delta;
	auto tile = getRoom().getTile({ newPos.x, newPos.y });
	if (tile == Room::Tile_Floor)
		setPosition(sf::Vector2f(newPos));
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
		{
			costMoney(mCarried.get());
			mCarried.reset(nullptr);
		}
		else if (tile == Room::Tile_Seat || tile == Room::Tile_Stool)
		{
			auto* target = dynamic_cast<Patron*>(getRoom().getObject(newPos));
			
			if (target && target->getOrder() && target->getOrder()->getType() == mCarried->getType())
			{
				mMoney += target->getTip(mCarried.get());
				target->giveOrder(mCarried.get());
				mCarried.reset(nullptr);
			}
		}
		else if (tile == Room::Tile_Bar || tile == Room::Tile_Table)
		{
			auto* target = dynamic_cast<Patron*>(getRoom().getObject(pos + delta * 2u));
			
			if (target && target->getOrder() && target->getOrder()->getType() == mCarried->getType())
			{
				mMoney += target->getTip(mCarried.get());
				target->giveOrder(mCarried.get());
				mCarried.reset(nullptr);
			}
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

		drink.setOrigin(0.5f, 0.5f);
		drink.setScale(0.5f, 0.5f);
		drink.setPosition(0.75f, 0);
		drink.setRotation(6 * sin(Application::getApplication()->getTime() * 2));

		rt.draw(drink, states);
	}
}

void Player::costMoney(const Drink* drink)
{
	mMoney -= drink->getCost();
}

float Player::getMoney() const
{
	return mMoney;
}
