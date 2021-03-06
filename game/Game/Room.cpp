#include "Room.hpp"
#include "Player.hpp"
#include "Patron.hpp"

#include "../Application.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <algorithm>
#include <random>

using namespace Game;

namespace
{
	static std::unordered_map<uint8_t, sf::Color> TileColors = {
		{ Room::Tile_Floor, sf::Color(0,0,0,0) },

		{ Room::Tile_Bar, sf::Color(110, 107, 23) },
		{ Room::Tile_Taps, sf::Color(110, 107, 23) },
		{ Room::Tile_Sink, sf::Color(110, 107, 23) },
		{ Room::Tile_Bottles, sf::Color(110, 107, 23) },
		{ Room::Tile_Seat, sf::Color(171, 89, 16) },
		{ Room::Tile_Stool, sf::Color(171, 89, 16) },
		{ Room::Tile_Table, sf::Color(110, 107, 23) }
	};

	template<typename T, typename U>
	float distance(const sf::Vector2<T>& a, const sf::Vector2<U>& b)
	{
		const float dX = b.x - a.x;
		const float dY = b.y - a.y;

		const float dDot = dX * dX + dY * dY;
		return sqrt(dDot);
	}
}

Room::Room()
	: mStarted(false)
	, mClock(-30)
	, mPopulateCD(0)
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
	mTiles.resize(size.x * size.y);
	setOrigin(size.x / 2, size.y / 2);
}
Player* Room::getPlayer() const
{
	for (auto& obj : mObjects)
	{
		auto* ply = dynamic_cast<Player*>(obj.get());
		if (ply)
			return ply;
	}
	return nullptr;
}
Object* Room::getObject(const sf::Vector2u& pos) const
{
	for (auto& obj : mObjects)
		if (distance(pos, obj->getPosition()) <= 0.5)
			return obj.get();

	return nullptr;
}
Room::TileType Room::getTile(const sf::Vector2u& pos) const
{
	if (pos.x < mSize.x && pos.y < mSize.y)
	{
		uint32_t i = pos.y * mSize.x + pos.x;
		
		return mTiles[i];
	}

	return Tile_Floor;
}
void Room::setTile(const sf::Vector2u& pos, TileType type)
{
	if (pos.x < mSize.x && pos.y < mSize.y)
	{
		uint32_t i = pos.y * mSize.x + pos.x;

		mTiles[i] = type;
	}
}

void Room::resetClock(float start)
{
	mClock = start;
}

void Room::depopulate()
{
	auto it = std::remove_if(mObjects.begin(), mObjects.end(), [](auto& obj) { return dynamic_cast<Patron*>(obj.get()); });
	if (it != mObjects.end())
		mObjects.erase(it, mObjects.end());
}

void Room::repopulate()
{
	int i = 0;
	const auto seats = std::count_if(mTiles.begin(), mTiles.end(), [&i, this](auto t) {
		const int j = i++;

		const uint32_t x = j % mSize.x,
		               y = j / mSize.x;

		return (t == Tile_Seat || t == Tile_Stool) && !this->getObject(sf::Vector2u{ x, y });
	});
	const auto maxSeats = 1 * (seats / 4);
	
	if (maxSeats <= 1)
		return;

	auto toFill = std::uniform_int_distribution<int>(0, maxSeats)(Object::Random());

	auto xDist = std::uniform_int_distribution<int>(0, mSize.x);
	auto yDist = std::uniform_int_distribution<int>(0, mSize.y);

	for (int i = 0; i < toFill; ++i)
	{
		sf::Vector2u pos;
		do
		{
			pos = sf::Vector2u(xDist(Object::Random()), yDist(Object::Random()));
			const auto tile = getTile(pos);
			if ((tile == Tile_Seat || tile == Tile_Stool) && !getObject(pos))
				break;
		} while (true);

		auto* patron = addObject<Patron>();
		patron->setPosition(sf::Vector2f(pos));

		const auto tileTop = getTile(pos - sf::Vector2u{ 0, 1 }),
		           tileLeft = getTile(pos - sf::Vector2u{ 1, 0 }),
		           tileBottom = getTile(pos + sf::Vector2u{ 0, 1 }),
		           tileRight = getTile(pos + sf::Vector2u{ 1, 0 });

		if (tileTop == Tile_Table || tileTop == Tile_Bar)
			patron->setRotation(-90);
		else if (tileLeft == Tile_Table || tileLeft == Tile_Bar)
			patron->setRotation(180);
		else if (tileBottom == Tile_Table || tileBottom == Tile_Bar)
			patron->setRotation(90);
	}
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
	mClock += dt * 2;

	if (!mStarted && mClock >= 0)
	{
		mStarted = true;
		mPopulateCD = 0;
	}

	if (mStarted)
		mPopulateCD -= dt;

	if (mPopulateCD < 0)
	{
		repopulate();
		mPopulateCD = std::uniform_real_distribution<float>(5, 15)(Object::Random());
	}

	if (mClock >= 60 * 8)
	{
		if (getPlayer()->getMoney() <= 0)
			Application::getApplication()->setState(Application::State_End);
		else
		{
			getPlayer()->newDay();

			depopulate();
			resetClock();
			mStarted = false;
		}
	}

	for (auto& ptr : mObjects)
	{
		if (ptr)
			ptr->update(dt);
	}

	for (auto& it : mToDelete)
		mObjects.erase(it);
	mToDelete.clear();
}

void Room::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform *= getTransform();

	auto circ = sf::CircleShape(4, 16);
	circ.setFillColor(sf::Color::White);
	circ.setScale(0.1f, 0.1f);
	circ.setOrigin({ -1.f, -1.f });

	auto rect = sf::RectangleShape(sf::Vector2f{ float(mSize.x), float(mSize.y) });
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color(63, 54, 21));
	rect.setOutlineThickness(2.f);

	rt.draw(rect, states);

	rect.setOutlineColor(sf::Color::Transparent);
	rect.setSize({ 1, 1 });
	for (uint32_t i = 0; i < mSize.x * mSize.y; ++i)
	{
		const auto x = i % mSize.x,
		           y = i / mSize.x;

		const auto tile = mTiles[i];

		if (tile == Tile_Floor)
			continue;

		sf::Shape* choice = nullptr;
		switch (tile)
		{
		case Tile_Bar:
		case Tile_Bottles:
		case Tile_Taps:
		case Tile_Sink:
			choice = &rect; break;

		case Tile_Seat:
		case Tile_Stool:
		case Tile_Table:
			choice = &circ; break;
		}

		sf::Shape& toDraw = *choice;
		toDraw.setFillColor(TileColors[tile]);
		toDraw.setPosition(x, y);

		if (tile == Tile_Table)
		{
			toDraw.setScale(0.15f, 0.15f);
			toDraw.move(-0.25f, -0.25f);
		}

		rt.draw(toDraw, states);

		switch (tile)
		{
		case Tile_Table: {
			circ.setScale(0.13f, 0.13f);
			circ.move(0.1f, 0.1f);
			circ.setFillColor(sf::Color(136, 109, 16));
			rt.draw(circ, states);

			circ.setScale(0.1f, 0.1f);
		} break;

		case Tile_Sink: {
			rect.setScale(0.75f, 0.75f);
			rect.move(0.15f, 0.20f);
			rect.setFillColor(sf::Color(80, 80, 80));
			rt.draw(rect, states);

			rect.setScale(0.65f, 0.65f);
			rect.setFillColor(sf::Color(120, 120, 120));
			rect.move(0.05f, 0.05f);
			rt.draw(rect, states);

			rect.setScale(1, 1);
		} break;

		case Tile_Taps: {
			rect.setScale(0.1f, 0.5f);
			rect.setFillColor(sf::Color(90, 90, 90));
			rect.move(0.5f, 0.25f);

			rect.setRotation(-25);
			rt.draw(rect, states);

			rect.setRotation(25);
			rt.draw(rect, states);

			rect.setRotation(0);
			rt.draw(rect, states);
			
			rect.setScale(1, 1);
		} break;

		case Tile_Bottles: {
			rect.setScale(0.1f, 0.1f);

			rect.setFillColor(sf::Color(75, 70, 70));
			rect.setSize({ 10, 2 });
			rt.draw(rect, states);
			rect.setSize({ 1, 1 });
			rect.setScale(1.f, 1.f);

			const float phi = 1.618033988;
			float h, s, v;
			s = 0.9f;
			v = 0.7f;

			circ.setOrigin({ 0.f, 0.f });
			circ.setScale(0.01f, 0.01f);
			circ.setPosition(x, y);

			circ.move(0.1f, 0.2f);
			for (int j = 0; j < 8; ++j)
			{
				h = i * 195 + j * 62 * phi;

				circ.setFillColor(Object::HSVtoRGB(h, s, v));
				rt.draw(circ, states);
				circ.move(0.1f, 0);
			}

			circ.setOrigin({ -1.f, -1.f });
			circ.setScale(0.1f, 0.1f);
		} break;
		}
	}

	for (auto& ptr : mObjects)
	{
		if (ptr)
			rt.draw(*ptr, states);
	}
	for (auto& ptr : mObjects)
	{
		if (ptr)
			ptr->drawPost(rt, states);
	}


	auto money = dynamic_cast<Player*>(mObjects.front().get())->getMoney();

	char text[256];
	sprintf(text, "%.2f", money);

	sf::Text moneyText(std::string(text) + "$", Application::getApplication()->getDefaultFont());
	rt.draw(moneyText);

	if (mClock < 0)
	{
		sprintf(text, "Time until opening: %02i", int(abs(mClock / 2)));
	}
	else
		sprintf(text, "%02i:%02i", (18 + (int(mClock) / 60)) % 24, (int(mClock) % 60));
	moneyText.setString(std::string(text));
	const auto tRect = moneyText.getGlobalBounds();
	moneyText.setPosition(rt.getSize().x - tRect.width - 15, 0);

	rt.draw(moneyText);
}

void Room::removeObject(Object* obj)
{
	auto it = std::find_if(mObjects.begin(), mObjects.end(), [obj](auto& it) { return it.get() == obj; });
	if (it != mObjects.end())
		mToDelete.push_back(it);
}