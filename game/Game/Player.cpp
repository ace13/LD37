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
	else if (inp[Input_Right].pressed() && pos.x + 1 < size.x)
		++pos.x;

	setPosition(pos);
}
void Player::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	states.transform *= getTransform();

	auto rect = sf::RectangleShape({ 1, 1 });
	rect.setFillColor(sf::Color::Blue);

	rt.draw(rect, states);
}

