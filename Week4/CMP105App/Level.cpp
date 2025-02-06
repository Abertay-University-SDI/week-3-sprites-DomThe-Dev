#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	
	steps = 0;
	texture.loadFromFile("gfx/coolDuck.png");
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "cant load font" << std::endl;
	}
	text.setFont(font);
	text.setString("Duck.");
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(-100000, -100000);
	text.setCharacterSize(24);

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
		view.move(-250 * dt, 0);
		window->setView(view);
	}
	else if (steps == 0 && !(view.getCenter().x > (window->getSize().x / 2) - duck.getSize().x))
	{
		steps = 1;
	}

	if (steps == 1)
	{
		view.setCenter(duck.getPosition().x + (duck.getSize().x / 2), duck.getPosition().y + (duck.getSize().y / 2));
		view.setSize(1920 * 15, 1080 * 15);
		window->setView(view);
		steps = 2;
	}

	if (steps == 2)
	{
		view.setSize(view.getSize().x - (zoomX * dt), view.getSize().y - (zoomY * dt) );
		std::cout << view.getSize().x << ", " << view.getSize().y << std::endl;
		view.rotate(360.f * dt);
		window->setView(view);
		zoomX += zoomX * dt;
		zoomY += zoomY * dt;
	}
	if (steps == 2 && view.getSize().x <= 600)
	{
		steps = 3;
	}
	if (steps == 3)
	{
		text.setPosition(window->getSize().x / 2, window->getSize().y / 2);
		//text.setPosition(duck.getPosition().x, duck.getPosition().y - duck.getSize().y);
		text.setRotation(view.getRotation());

		//text.setColor(sf::Color::Red);
		window->setView(view);
	}
	
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(duck);
	window->draw(text);

	endDraw();
}
