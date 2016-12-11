#include "Patron.hpp"

#include "../Application.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <random>

using namespace Game;

Patron::Patron()
	: mPatience(std::uniform_real_distribution<float>(1, 5)(std::random_device()))
	, mShirtHue(std::uniform_real_distribution<float>(0, 360)(std::random_device()))
	, mHairHue(std::uniform_real_distribution<float>(0, 360)(std::random_device()))
	, mOrderTime(1)
	, mOrder(Drink_Cocktail)
{
	setOrigin(0.5f, 0.5f);
}

void Patron::update(float dt)
{
}

void Patron::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform.translate({ 0.5f,0.5f });
	states.transform *= getTransform();

	sf::RectangleShape rect({ 1.f, 1.f });
	rect.setScale(0.8f, 0.8f);
	rect.move(0.1f, 0.1f);
	rect.setFillColor(HSVtoRGB(mShirtHue, 0.7f, 0.5f));
	rt.draw(rect, states);

	rect.setScale(0.6f, 0.6f);
	rect.move(0.1f, 0.1f);
	rect.setFillColor(HSVtoRGB(mShirtHue, 0.7f, 0.9f));
	rt.draw(rect, states);

	rect.setScale(0.3f, 0.3f);
	rect.move(0.2f, 0.15f);
	rect.setFillColor(HSVtoRGB(mHairHue, 0.5f, 0.35f));
	rt.draw(rect, states);

	if (mOrderTime >= 0)
	{
		sf::CircleShape bubble(2);
		bubble.setScale(0.45f, 0.25f);
		bubble.setFillColor(sf::Color::Transparent);
		bubble.setOutlineColor(sf::Color::Black);
		bubble.setOutlineThickness(0.25f);
		bubble.setPosition(0, -1.5f);

		states.transform.translate(0.5f, 0.5F).rotate(-getRotation());
		rt.draw(bubble, states);

		sf::ConvexShape point(3);
		point.setFillColor(sf::Color::White);
		point.setOutlineColor(sf::Color::Black);
		point.setOutlineThickness(0.2f);
		point.setScale(0.3f, 0.3f);

		point.setPosition(0.2f, -0.45f);
		point.setRotation(-98);

		point.setPoint(0, { 0, 0 });
		point.setPoint(1, { 1.5f, 1 });
		point.setPoint(2, { 1, 1.5f });

		rt.draw(point, states);

		bubble.setOutlineColor(sf::Color::Transparent);
		bubble.setFillColor(sf::Color::White);
		rt.draw(bubble, states);

		Drink drink(mOrder);
		drink.setOrigin(0.5f, 0.5f);
		drink.setPosition(0.75f, -1.f);
		drink.setScale(0.5f, 0.5f);

		drink.setRotation(11.25 * cos(Application::getApplication()->getTime()));

		rt.draw(drink, states);
	}
}
