#include "Patron.hpp"
#include "Player.hpp"

#include "../Application.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>

using namespace Game;

Patron::Patron()
	: mPatience(std::uniform_real_distribution<float>(1, 5)(std::random_device()))
	, mShirtHue(std::uniform_real_distribution<float>(0, 360)(std::random_device()))
	, mHairHue(std::uniform_real_distribution<float>(0, 360)(std::random_device()))
	, mOrderTime(0)
	, mOrderCooldown(std::uniform_real_distribution<float>(1, 20)(std::random_device()))
	, mOffset(std::uniform_real_distribution<float>(0, 10)(std::random_device()))
{
	setOrigin(0.5f, 0.5f);
}

void Patron::update(float dt)
{
	if (mOrder)
	{
		mOrderTime -= dt / (mPatience + (mOrder->getType() == Drink_Water ? 4 : 0));

		if (mOrderTime < 0 && mOrder)
		{
			mOrderTime = 6;

			getRoom().getPlayer()->costMoney(mOrder.get(), this);

			mOrder.reset(nullptr);
			mOrderCooldown = std::uniform_real_distribution<float>(1, 20)(std::random_device());
		}
	}
	else
	{
		mOrderCooldown -= dt;
		if (mOrderCooldown < 0)
		{
			mOrderTime = kOrderTime;
			mOrder = std::make_unique<Drink>(DrinkType(std::uniform_int_distribution<int>(Drink_Beer, Drink_Water)(std::random_device())));
		}
	}
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
}

void Patron::drawPost(sf::RenderTarget& rt, sf::RenderStates states) const
{
	if (mOrder && mOrderTime >= 0)
	{
		states.transform.translate({ 0.5f,0.5f }); 
		states.transform *= getTransform();

		sf::CircleShape bubble(2);
		bubble.setScale(0.45f, 0.25f);
		bubble.setFillColor(sf::Color::Transparent);
		bubble.setOutlineColor(sf::Color::Black);
		bubble.setOutlineThickness(0.25f);
		bubble.setPosition(0, -1.5f);

		states.transform.translate({ 0.5f, 0.5f }).rotate(-getRotation());
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

		auto& drink = *mOrder;
		drink.setOrigin(0.5f, 0.5f);
		drink.setPosition(0.75f, -1.f);
		drink.setScale(0.5f, 0.5f);

		drink.setRotation(11.25 * cos(mOffset + Application::getApplication()->getTime() * ((kOrderTime - mOrderTime) / kOrderTime) * 2));

		rt.draw(drink, states);

		if (mOrderTime <= 5)
		{
			sf::Text exclamation("!", Application::getApplication()->getDefaultFont(), 12);
			exclamation.setScale(0.05f, 0.05f);
			exclamation.setPosition(1.20f, -1.20f);

			const float anger = (5.f - mOrderTime) / 5.f;
			sf::Color col = sf::Color::Black;
			col.r = anger * 255;
			exclamation.setFillColor(col);

			const float time = Application::getApplication()->getTime() * anger * 10;
			exclamation.move(cos(time + 45) * anger * 0.05f, sin(time) * anger * 0.05f);

			{
				auto rect = exclamation.getLocalBounds();
				exclamation.setOrigin(rect.width / 2.f, rect.height / 2.f);
			}

			rt.draw(exclamation, states);
		}
	}
}

float Patron::getTip(const Drink* drink) const
{
	const float price = drink->getCost();
	const float maxTip = price * 0.10f * (0.5f + (mPatience / 2.f));

	if (mOrderTime <= 5)
	{
		const float anger = (5.f - mOrderTime) / 5.f;
		return maxTip * (1.f - anger);
	}

	return maxTip;
}

void Patron::giveOrder(const Drink* drink)
{
	if (mOrder && drink && mOrder->getType() == drink->getType())
	{
		mOrder.reset(nullptr);
		mOrderCooldown = std::uniform_real_distribution<float>(1, 20)(std::random_device());
	}
}

const Drink* Patron::getOrder() const
{
	return mOrder.get();
}
