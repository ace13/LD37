#pragma once

#include "Game/EndScreen.hpp"
#include "Game/Room.hpp"

#include "InputManager.hpp"
//#include "ParticleManager.hpp"
//#include "ScriptManager.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
	enum State
	{
		State_Game,
		State_End
	};

	Application();
	Application(const Application&) = delete;
	Application(Application&&) = default;
	~Application() = default;

	Application& operator=(const Application&) = delete;

	static Application* getApplication();

	State getState() const;
	void setState(State state);

	sf::Font& getDefaultFont();
	const sf::Font& getDefaultFont() const;
	const InputManager& getInputManager() const;

	void init(int argc, char** argv);
	void run();

	float getDt() const;
	float getTime() const;

private:
	InputManager mInputs;
//	ParticleManager mParticles;
//	ScriptManager mScripts;
	sf::RenderWindow mWindow;
	sf::Font mDefaultFont;

	State mState;
	Game::Room mRoom;
	Game::EndScreen mEndScreen;

	float mDt, mTime;
};
