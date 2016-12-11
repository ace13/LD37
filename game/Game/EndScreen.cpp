#include "EndScreen.hpp"
#include "../Application.hpp"

#include "Room.hpp"
#include "Player.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace Game;

sf::Shader grayTone;

EndScreen::EndScreen(Room* room)
	: mRoom(room)
	, mTime(0)
{
	grayTone.loadFromMemory(
		"uniform float dt;\n"
		"\n"
		"void main(){\n"
		"  float gray = dot(gl_Color.rgb, vec3(0.299, 0.587, 0.114));\n"
		"  vec4 grayVec = vec4(gray, gray, gray, gl_Color.a);\n"
		"  gl_FragColor = mix(gl_Color, grayVec, dt);\n"
		"}", sf::Shader::Fragment);
}

void EndScreen::update(float dt)
{
	mTime += dt / 2;

	grayTone.setUniform("dt", std::min(mTime, 1.f));
}
void EndScreen::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
	sf::RectangleShape background(sf::Vector2f(rt.getSize()));
	background.setFillColor(sf::Color(0, 0, 0, std::min(1.f, mTime) * 180));
	rt.draw(background);

	auto& player = *mRoom->getPlayer();

	// TODO:
	sf::Text text("Game Over", Application::getApplication()->getDefaultFont());
	text.move(15, 15);
	rt.draw(text);

	auto rect = text.getGlobalBounds();
	text.move(0, rect.height + 64);
	text.setString(std::string("You managed ") + std::to_string(player.getDays()) + " days.");
	rt.draw(text);

	rect = text.getGlobalBounds();
	text.move(0, rect.height + 15);
	text.setString(std::to_string(player.getDrinksServed()) + " drinks were served.");
	rt.draw(text);

	rect = text.getGlobalBounds();
	text.move(0, rect.height + 8);
	text.setString(std::to_string(player.getDrinksPoured()) + " drinks were poured away.");
	rt.draw(text);

	rect = text.getGlobalBounds();
	text.move(0, rect.height + 5);
	text.setString(std::to_string(player.getDrinksMissed()) + " customers didn't get their orders.");
	rt.draw(text);

	rect = text.getGlobalBounds();
	text.move(0, rect.height + 32);
	text.setString(std::string("Topping out at ") + std::to_string(int(player.getMaxMoney())) + "$");
	rt.draw(text);
}
const sf::Shader* EndScreen::getGrayscale() const
{
	return &grayTone;
}