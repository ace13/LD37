#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace Game
{

class Room;

class EndScreen : public sf::Drawable
{
public:
	EndScreen(Room*);

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	const sf::Shader* getGrayscale() const;

private:
	float mTime;
	Room* mRoom;
};

}