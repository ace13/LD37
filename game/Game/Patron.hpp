#pragma once

#include "Object.hpp"

namespace Game
{

class Patron : public Object
{
public:
	Patron();

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

private:
	float mPatience,
	      mShirtHue,
	      mHairHue,
	      mOrderTime;

	int mOrder;

};

}