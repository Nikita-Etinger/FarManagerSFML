#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "NavWindow.h"
#include "Config.h"
#include "Button.h"
#include <vector>


class App
{
private:
	sf::RenderWindow window;
	NavWindow navLeft;
	NavWindow navRight;
	std::vector <Button> buttons;
	std::string operation = "";


public:
	App();
	void run();
private:
	void render();
	void processEvent();
	void update();
	void updateFields();
	


};

