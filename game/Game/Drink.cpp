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
{

}

void Drink::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform *= getTransform();

	switch (mType)
	{
	case Drink_Beer: {
		
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

	} break;
	}
}
