#pragma once

#include <unordered_map>

namespace sf {

}

struct Input
{
	float Value;

	operator bool() const;

	void bind();
};

template<typename T>
class InputManager
{
public:
	InputManager();
	InputManager(const InputManager&);
	InputManager(InputManager&&);
	~InputManager();

	InputManager& operator=(const InputManager&);

	void pushEvent();

	Input& operator[](const T&);
	const Input& operator[](const T&) const;

private:
	std::unordered_map<T, Input> mInputs;
};
