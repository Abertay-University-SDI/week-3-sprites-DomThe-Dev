#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	
	steps = 1;
	texture.loadFromFile("gfx/coolDuck.png");

	duck.setTexture(&texture);
	duck.setSize(sf::Vector2f(600, 600));
	duck.setPosition((window->getSize().x / 2) - (duck.getSize().x / 2), (window->getSize().y / 2) - (duck.getSize().y / 2));

	view.setSize(sf::Vector2f(480.f, 270.f));
	view.setCenter((window->getSize().x / 2) + duck.getSize().y, (window->getSize().y / 2) - (duck.getSize().y / 5));
	window->setView(view);

	// initialise game objects
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	// Close window on Escape pressed.
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}

}

// Update game objects
void Level::update(float dt)
{
	if (view.getCenter().x > (window->getSize().x / 2) - duck.getSize().x && steps == 0)
	{
		std::cout << "moving" << view.getCenter().x << std::endl;
		view.move(-150 * dt, 0);
		window->setView(view);
	}
	else if (steps == 0 && !(view.getCenter().x > (window->getSize().x / 2) - duck.getSize().x))
	{
		steps = 1;
	}

	if (steps == 1)
	{
		view.setCenter(duck.getPosition().x + (duck.getSize().x / 2), duck.getPosition().y + (duck.getSize().y / 2));
		view.setSize(1920 * 2, 1080 * 2);
		window->setView(view);
		steps = 2;
	}

	if (steps == 2)
	{
		view.setSize(view.getSize().x - (150 * dt), view.getSize().y - (150 * dt) );
		std::cout << view.getSize().x << ", " << view.getSize().y << std::endl;
		view.rotate(180.f * dt);
		window->setView(view);
	}
	
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(duck);

	endDraw();
}
