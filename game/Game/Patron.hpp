#pragma once

#include "Object.hpp"
#include "Drink.hpp"

namespace Game
{

class Patron : public Object
{
public:
	Patron();

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	const Drink& getOrder() const;

private:
	float mPatience,
	      mShirtHue,
	      mHairHue,
	      mOrderTime;

	float mOffset;

	Drink mOrder;

};

}