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

	// TODO:
	sf::Text text("", Application::getApplication()->getDefaultFont());
	rt.draw(text);
}
const sf::Shader* EndScreen::getGrayscale() const
{
	return &grayTone;
}