#include "Application.h"



Application::Application() :
	windowName("NULL"),
	window(sf::VideoMode(1280, 720), "Ascii Streaming")
{

}

Application & Application::getInstance()
{
	static Application instance;
	return instance;
}


void Application::setWindowName(const std::string newName) {
	getInstance().windowName = newName;
}

void Application::run() {
	Application &instance = getInstance();
	instance.hwnd = FindWindow(NULL, instance.windowName.c_str());
	if (instance.hwnd == NULL)
		return;

	ImageSource raw(sf::IntRect(0, 0, 1280, 720), instance.hwnd);

	//sf::Vector2u asciiSize = { (unsigned int)(150*1.5),(unsigned int)(100*1.5) };//{ 426, 144 };
	const sf::Vector2u asciiSize = { 426, 144 };
	AsciiDisplay ascii(asciiSize, 5);
	sf::Clock clock;

	float movingSpeed = 10.f;

	while (instance.window.isOpen()) {
		std::cout << "FPS: " << 1.f / clock.getElapsedTime().asSeconds() << std::endl;
		clock.restart();
		input();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			raw.move({ 0.f,movingSpeed });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			raw.move({ 0.f,-movingSpeed });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			raw.move({ -movingSpeed,0.f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			raw.move({ movingSpeed,0.f });


		raw.update();
		ascii.update(raw, asciiSize);

		instance.window.clear(sf::Color::Black);
		//instance.window.draw(raw);
		instance.window.draw(ascii);
		instance.window.display();
	}
}

void Application::input() {
	sf::Event event;
	Application &instance = getInstance();
	while (instance.window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			instance.window.close();
	}
}