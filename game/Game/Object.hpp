#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace Game
{

class Room;

class Object : public sf::Drawable, public sf::Transformable
{
public:
	static sf::Color HSVtoRGB(float fH, float fS, float fV);

	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const = 0;
	virtual void drawPost(sf::RenderTarget& rt, sf::RenderStates states) const { }

protected:
	Room& getRoom();
	const Room& getRoom() const;

private:
	void setRoom(Room*);

	Room* mRoom;

	friend class Room;
};

}