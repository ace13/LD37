#pragma once

#include "Object.hpp"
#include "Drink.hpp"

#include <memory>

namespace Game
{

class Patron : public Object
{
public:
	enum
	{
		kOrderTime = 10
	};

	Patron();

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	float getTip(const Drink*);

	void giveOrder(const Drink*);
	const Drink* getOrder() const;

private:
	float mPatience,
	      mShirtHue,
	      mHairHue,
	      mOrderTime,
	      mOrderCooldown;

	float mOffset;

	std::unique_ptr<Drink> mOrder;

};

}