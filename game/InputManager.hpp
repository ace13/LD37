#pragma once

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <unordered_map>

class InputManager
{
public:
	struct Bind
	{
		enum Type
		{
			Bind_None,

			Bind_Key,
			Bind_JAxis,
			Bind_JButton,
			Bind_MButton,
			Bind_MWheel
		} Type;

		union
		{
			struct
			{
				sf::Keyboard::Key code;
			} Key;

			struct
			{
				unsigned int id;
				sf::Joystick::Axis axis;
				bool positive;
			} JAxis;

			struct
			{
				unsigned int id;
				unsigned int button;
			} JButton;

			struct
			{
				sf::Mouse::Button button;
			} MButton;

			struct
			{
				sf::Mouse::Wheel wheel;
				bool positive;
			} MWheel;
		};
	};

	struct Input
	{
		float Value;

		Bind PBind, SBind, TBind;

		operator bool() const;
	};

	InputManager();
	InputManager(const InputManager&);
	InputManager(InputManager&&);
	~InputManager();

	InputManager& operator=(const InputManager&);

	void pushEvent();

	void addInput(int id);

	Input& operator[](int);
	const Input& operator[](int) const;

private:
	std::unordered_map<int, Input> mInputs;
};
