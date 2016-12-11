#include "EndScreen.hpp"
#include "../Application.hpp"

#include "Room.hpp"
#include "Player.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace Game;

EndScreen::EndScreen(Room* room)
	: mRoom(room)
	, mTime(0)
{

}

void EndScreen::update(float dt)
{
	mTime += dt;
}
void EndScreen::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	sf::RectangleShape background(sf::Vector2f(rt.getSize()));
	background.setFillColor(sf::Color(0, 0, 0, std::min(1.f, mTime) * 196));
	rt.draw(background);

	// TODO:
	sf::Text text("", Application::getApplication()->getDefaultFont());
	rt.draw(text);
}