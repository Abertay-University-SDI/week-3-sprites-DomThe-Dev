#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/GameObject.h"
#include <string.h>
#include <iostream>


class Level : BaseLevel {
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;

private:
	// Level objects
	int steps;
	float zoomX = 1920;
	float zoomY = 1080;
	sf::View view;
	sf::Text text;
	sf::Font font;

	GameObject duck;
	sf::Texture texture;
	GameObject explosion;
	sf::Texture extexture;

};