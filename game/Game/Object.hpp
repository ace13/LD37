#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace Game
{

class Room;

class Object : public sf::Drawable
{
public:


	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const = 0;

protected:
	Room& getRoom();
	const Room& getRoom() const;

private:
	void setRoom(Room*);

	Room* mRoom;

	friend class Room;
};

}