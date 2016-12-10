#include "Object.hpp"

using namespace Game;

void Object::setRoom(Room* room)
{
	mRoom = room;
}
Room& Object::getRoom()
{
	return *mRoom;
}
const Room& Object::getRoom() const
{
	return *mRoom;
}