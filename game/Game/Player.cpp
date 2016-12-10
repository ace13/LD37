#include "Player.hpp"

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
	
	if (getRoom().getTile({ uint32_t(pos.x), uint32_t(pos.y) }) == Room::Tile_Floor)
		setPosition(pos);
}
void Player::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform *= getTransform();

	auto rect = sf::RectangleShape({ 1, 1 });
	rect.setFillColor(sf::Color::Blue);

	rt.draw(rect, states);
}

