#pragma once

#include "Game/Room.hpp"

#include "InputManager.hpp"
//#include "ScriptManager.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
	Application();
	Application(const Application&) = delete;
	Application(Application&&) = default;
	~Application() = default;

	Application& operator=(const Application&) = delete;

	static Application* getApplication();

	sf::Font& getDefaultFont();
	const sf::Font& getDefaultFont() const;
	const InputManager& getInputManager() const;

	void init(int argc, char** argv);
	void run();

	float getDt() const;
	float getTime() const;

private:
	InputManager mInputs;
//	ScriptManager mScripts;
	sf::RenderWindow mWindow;
	sf::Font mDefaultFont;

	Game::Room mRoom;

	float mDt, mTime;
};
