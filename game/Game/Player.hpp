#pragma once

#include "Object.hpp"

#include <SFML/Graphics/Transformable.hpp>

namespace Game
{

class Player : public Object, public sf::Transformable
{
public:
	Player() = default;

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

private:
	
};

}