#pragma once

#include "Object.hpp"
#include "Drink.hpp"

#include <memory>

namespace Game
{

class Player : public Object
{
public:
	Player();

	void update(float dt);
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
	void drawPost(sf::RenderTarget& rt, sf::RenderStates states) const;
	
	void costMoney(const Drink* drink, const Object* source);
	float getMoney() const;

	void newDay();

	float getMaxMoney() const;
	int getDays() const;
	int getDrinksServed() const;
	int getDrinksPoured() const;
	int getDrinksMissed() const;

private:
	std::unique_ptr<Drink> mCarried;

	float mMoney, mMaxMoney;

	int mDays;
	int mDrinksServed, mDrinksPoured, mDrinksMissed;
};

}