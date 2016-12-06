#include "InputManager.hpp"

#include <SFML/Window/Event.hpp>

InputManager::Input::Input()
	: Value(0)
	, OldValue(0)
	, PBind{ InputManager::Bind::Bind_None }
	, SBind{ InputManager::Bind::Bind_None }
{
}

InputManager::Input::operator bool() const
{
	return Value > 0.5f;
}

bool InputManager::Input::pressed() const
{
	return Value > 0.5f && OldValue < 0.5f;
}

float InputManager::Input::delta() const
{
	return Value - OldValue;
}


InputManager::InputManager()
{
}
InputManager::InputManager(const InputManager& copy)
	: mInputs(copy.mInputs)
{
}
InputManager::InputManager(InputManager&& move)
	: mInputs(std::move(move.mInputs))
{
}
InputManager::~InputManager()
{
}

InputManager& InputManager::operator=(const InputManager& rhs)
{
	if (this != &rhs)
	{
		mInputs = rhs.mInputs;
	}

	return *this;
}

void InputManager::pushEvent(const sf::Event& ev)
{
	auto bindType = Bind::Bind_None;

	if (bindType != Bind::Bind_None)
		for (auto& inp : mInputs)
		{
			if (inp.Type != bindType)
				continue;

			inp.OldValue = inp.Value;
			// inp.Value = ;
		}
}

void InputManager::addInput(int id)
{
	mInputs[id] = Input();
}

Input& InputManager::operator[](int key)
{
	return mInputs.at(key);
}
const Input& InputManager::operator[](int key) const
{
	return mInputs.at(key);
}
