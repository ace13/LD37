#pragma once

class Application
{
public:
	Application() = default;
	Application(const Application&) = delete;
	Application(Application&&) = default;
	~Application() = default;

	Application& operator=(const Application&) = delete;

	void init(int argc, char** argv);
	void run();

private:
};
