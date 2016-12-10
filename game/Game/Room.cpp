#include "Room.hpp"
#include "Player.hpp"

#include "../Application.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace Game;

namespace
{
	static std::unordered_map<uint8_t, sf::Color> TileColors = {
		{ Room::Tile_Floor, sf::Color(0,0,0,0) },

		{ Room::Tile_Bar, sf::Color(110, 107, 23) },
		{ Room::Tile_Bottles, sf::Color(110, 107, 23) },
		{ Room::Tile_Seat, sf::Color(171, 89, 16) },
		{ Room::Tile_Stool, sf::Color(171, 89, 16) },
		{ Room::Tile_Table, sf::Color(110, 107, 23) }
	};

	void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
		float fC = fV * fS; // Chroma
		float fHPrime = fmod(fH / 60.0, 6);
		float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
		float fM = fV - fC;

		if (0 <= fHPrime && fHPrime < 1) {
			fR = fC;
			fG = fX;
			fB = 0;
		}
		else if (1 <= fHPrime && fHPrime < 2) {
			fR = fX;
			fG = fC;
			fB = 0;
		}
		else if (2 <= fHPrime && fHPrime < 3) {
			fR = 0;
			fG = fC;
			fB = fX;
		}
		else if (3 <= fHPrime && fHPrime < 4) {
			fR = 0;
			fG = fX;
			fB = fC;
		}
		else if (4 <= fHPrime && fHPrime < 5) {
			fR = fX;
			fG = 0;
			fB = fC;
		}
		else if (5 <= fHPrime && fHPrime < 6) {
			fR = fC;
			fG = 0;
			fB = fX;
		}
		else {
			fR = 0;
			fG = 0;
			fB = 0;
		}

		fR += fM;
		fG += fM;
		fB += fM;
	}
}

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
	mTiles.resize(size.x * size.y);
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

	auto circ = sf::CircleShape(4, 16);
	circ.setFillColor(sf::Color::White);
	circ.setScale(0.1f, 0.1f);
	circ.setOrigin({ -1.f, -1.f });
	auto rect = sf::RectangleShape(sf::Vector2f{ float(mSize.x), float(mSize.y) });
	rect.setFillColor(sf::Color::White);
	rt.draw(rect, states);

	rect.setSize({ 1, 1 });
	for (uint32_t i = 0; i < mSize.x * mSize.y; ++i)
	{
		auto x = i % mSize.x,
		     y = i / mSize.x;

		auto tile = mTiles[i];
		sf::Shape& toDraw = rect;

		switch (tile)
		{
		case Tile_Bar:
		case Tile_Bottles:
			toDraw = rect; break;

		case Tile_Seat:
			toDraw = circ; break;
		}

		toDraw.setFillColor(TileColors[tile]);
		toDraw.setPosition(x, y);
		rt.draw(rect, states);

		switch (tile)
		{
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
				h = i * 25 + j * 38 * phi;

				float r, g, b;
				HSVtoRGB(r, g, b, h, s, v);

				circ.setFillColor(sf::Color(r * 255, g * 255, b * 255));
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
}