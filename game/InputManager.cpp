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
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
		bindType = Bind::Bind_Key; break;

	case sf::Event::JoystickMoved:
		bindType = Bind::Bind_JAxis: break;

	case sf::Event::JoystickButtonPressed:
	case sf::Event::JoystickButtonReleased:
		bindType = Bind::Bind_JButton; break;

	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		bindType = Bind::Bind_MButton; break;

	case sf::Event::MouseWheelScrolled:
		bindType = Bind::Bind_MWheel; break;
	}

	if (bindType != Bind::Bind_None)
		for (auto& inp : mInputs)
		{
			if (inp.Type != bindType)
				continue;

			float newVal = 0;
			bool found = false;
			switch (bindType)
			{
			case Bind::Bind_Key:
				newVal = ev.type == sf::Event::KeyPressed;
				found = ev.key.code == inp.Key.code;
				break;

			case Bind::Bind_JAxis:
				newVal = abs(ev.joystickMove.position)/100.f;
				found = ev.joystickMove.joystickId == inp.JAxis.id && ev.joystickMove.axis == inp.JAxis.axis && ((inp.JAxis.positive && ev.joystickMove.position > 0) || (!inp.JAxis.positive && ev.joystickMove.position < 0));
				break;

			case Bind::Bind_JButton:
				newVal = ev.type == sf::Event::JoystickButtonPressed;
				found = ev.joystickButton.joystickId == inp.JButton.id && ev.joystickButton.button == inp.JButton.button;
				break;

			case bind::Bind_MBtton:
				newVal = ev.type == sf::Event::MouseButtonPressed;
				found = ev.mouseButton.button == inp.MButton.button;
				break;
			}


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
