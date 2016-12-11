#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace Game
{

enum DrinkType
{
	Drink_Beer,
	Drink_Cocktail,
	Drink_Water,

	Drink_Count
};

class Drink : public sf::Drawable, public sf::Transformable
{
public:
	Drink(DrinkType type);

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	DrinkType getType() const;

private:
	DrinkType mType;
	float mHue, mVal;
};

}
