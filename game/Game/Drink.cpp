#include "Drink.hpp"
#include "Object.hpp"

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <random>

using namespace Game;

Drink::Drink(DrinkType type)
	: mType(type)
	, mHue(std::uniform_real_distribution<float>(0, 360)(std::random_device()))
	, mVal(std::uniform_real_distribution<float>(0.1f, 0.8f)(std::random_device()))
{

}

void Drink::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform *= getTransform();
	
	// TODO: Liquid leveling
	switch (mType)
	{
	case Drink_Beer: {
		sf::RectangleShape stein({ 0.5f, 1.f });

		stein.move(0.25f, 0);
		stein.setFillColor(sf::Color::Transparent);
		stein.setOutlineThickness(0.05f);
		stein.setOutlineColor(sf::Color::Black);

		rt.draw(stein, states);

		sf::ConvexShape beer(4);

		beer.setPoint(0, { 0.25f, 0.25f });
		beer.setPoint(1, { 0.25f, 1 });
		beer.setPoint(2, { 0.75f, 1 });
		beer.setPoint(3, { 0.75f, 0.25f });

		beer.setFillColor(Object::HSVtoRGB(45, 0.9f, mVal));

		rt.draw(beer, states);
	} break;

	case Drink_Cocktail: {
		sf::ConvexShape glass(8);

		glass.setPoint(0, { 0, 0 });
		glass.setPoint(1, { 0.5f, 0.5f });
		glass.setPoint(2, { 0.5f, 0.9f });
		glass.setPoint(3, { 0.25f, 1.f });
		glass.setPoint(4, { 0.75f, 1.f });
		glass.setPoint(5, { 0.5f, 0.9f });
		glass.setPoint(6, { 0.5f, 0.5f });
		glass.setPoint(7, { 1, 0 });

		glass.setFillColor(sf::Color::Transparent);
		glass.setOutlineThickness(0.05f);
		glass.setOutlineColor(sf::Color::Black);

		rt.draw(glass, states);

		glass.setPointCount(3);
		glass.setPoint(0, { 0.5f, 0.5f });
		glass.setPoint(1, { 0.1f, 0.1f });
		glass.setPoint(2, { 0.9f, 0.1f });
		glass.setOutlineThickness(0);
		glass.setOutlineColor(sf::Color::Transparent);

		glass.setFillColor(Object::HSVtoRGB(mHue, 0.5f, 0.95f));

		rt.draw(glass, states);
	} break;

	case Drink_Water: {
		sf::ConvexShape glass(4);

		glass.setPoint(0, { 0, 0 });
		glass.setPoint(1, { 0.1f, 1 });
		glass.setPoint(2, { 0.9f, 1 });
		glass.setPoint(3, { 1, 0 });

		glass.setFillColor(sf::Color::Transparent);
		glass.setOutlineColor(sf::Color::Black);
		glass.setOutlineThickness(0.05f);

		rt.draw(glass, states);

		glass.setPoint(0, { 0.025f, 0.25f });
		glass.setPoint(1, { 0.1f, 1 });
		glass.setPoint(2, { 0.9f, 1 });
		glass.setPoint(3, { 0.975f, 0.25f });
		
		glass.setFillColor(sf::Color(105, 185, 240, 120));
		glass.setOutlineColor(sf::Color::Transparent);
		glass.setOutlineThickness(0);

		rt.draw(glass, states);

	} break;
	}
}

DrinkType Drink::getType() const
{
	return mType;
}
