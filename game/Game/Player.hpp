#pragma once

#include "Object.hpp"

namespace Game
{

class Player : public Object
{
public:
	Player() = default;

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

private:
	
};

}