#include "Application.hpp"
#include "Inputs.hpp"

#include "Game/Patron.hpp"

#include <SFML/Window/Event.hpp>

#include <chrono>

namespace
{
	Application* gApplication;
}

Application::Application()
	: mDt(0)
	, mTime(0)
{
	gApplication = this;
}

Application* Application::getApplication()
{
	return gApplication;
}

const InputManager& Application::getInputManager() const
{
	return mInputs;
}

void Application::init(int argc, char** argv)
{
	mScripts.init();
	
	for (int i = 0; i < Input_Count; ++i)
		mInputs.addInput(i);

	mInputs[Input_Left].PBind = InputManager::Bind{
		InputManager::Bind::Bind_Key,
		{ sf::Keyboard::A }
	};
	mInputs[Input_Right].PBind = InputManager::Bind{
		InputManager::Bind::Bind_Key,
		{ sf::Keyboard::D }
	};
	mInputs[Input_Up].PBind = InputManager::Bind{
		InputManager::Bind::Bind_Key,
		{ sf::Keyboard::W }
	};
	mInputs[Input_Down].PBind = InputManager::Bind{
		InputManager::Bind::Bind_Key,
		{ sf::Keyboard::S }
	};

	mRoom.setPosition({ 375, 370 });
	mRoom.setSize({ 10, 10 });
	mRoom.setScale(50);

	for (unsigned int i = 0; i < 10; ++i)
	{
		if (i == 7)
			continue;

		mRoom.setTile({ i, 0 }, Game::Room::Tile_Bottles);
		mRoom.setTile({ i, 3 }, Game::Room::Tile_Bar);
		mRoom.setTile({ i, 4 }, Game::Room::Tile_Stool);
	}

	mRoom.setTile({ 4, 0 }, Game::Room::Tile_Sink);
	mRoom.setTile({ 5, 0 }, Game::Room::Tile_Taps);
	mRoom.setTile({ 6, 0 }, Game::Room::Tile_Taps);
	mRoom.setTile({ 7, 0 }, Game::Room::Tile_Taps);
	mRoom.setTile({ 8, 0 }, Game::Room::Tile_Bar);
	mRoom.setTile({ 9, 0 }, Game::Room::Tile_Bar);

	mRoom.setTile({ 1, 8 }, Game::Room::Tile_Table);
	mRoom.setTile({ 0, 8 }, Game::Room::Tile_Seat);
	mRoom.setTile({ 1, 9 }, Game::Room::Tile_Seat);

	{
		auto& pat = *mRoom.addObject<Game::Patron>();
		pat.setPosition(0, 4);
		pat.setRotation(-90);
	}

	{
		auto& pat = *mRoom.addObject<Game::Patron>();
		pat.setPosition(2, 4);
		pat.setRotation(-90);
	}

	{
		auto& pat = *mRoom.addObject<Game::Patron>();
		pat.setPosition(4, 4);
		pat.setRotation(-90);
	}

	{
		auto& pat = *mRoom.addObject<Game::Patron>();
		pat.setPosition(6, 4);
		pat.setRotation(-90);
	}

	{
		auto& pat = *mRoom.addObject<Game::Patron>();
		pat.setPosition(8, 4);
		pat.setRotation(-90);
	}

	{
		auto& pat = *mRoom.addObject<Game::Patron>();
		pat.setPosition(0, 8);
		pat.setRotation(0);
	}

	{
		auto& pat = *mRoom.addObject<Game::Patron>();
		pat.setPosition(1, 9);
		pat.setRotation(-90);
	}
	
	uint32_t aaLevel = 0;
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];

		if (arg == "-a")
			aaLevel = 8;
	}

	mWindow.create(sf::VideoMode(1280, 720), "LD37", 7U, sf::ContextSettings(0, 0, aaLevel));
}

void Application::run()
{
	sf::Event ev;

	typedef std::chrono::high_resolution_clock clock;
	auto tick = clock::now(),
	     last = clock::now();

	clock::duration dt;

	while (mWindow.isOpen())
	{
		tick = clock::now();

		dt = tick - last;
		mDt = std::chrono::duration<float>(dt).count();
		mTime += mDt;
		
		last = tick;

		mInputs.tick();
		while (mWindow.pollEvent(ev))
		{
			mInputs.pushEvent(ev);

			if (ev.type == sf::Event::Closed)
				mWindow.close();
		}

		mRoom.update(mDt);

		mWindow.clear();

		mWindow.draw(mRoom);

		mWindow.display();
	}
}

float Application::getTime() const
{
	return mTime;
}
float Application::getDt() const
{
	return mDt;
}