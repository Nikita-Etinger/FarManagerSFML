#include "App.h"
#include <filesystem>
#include <fstream>

App::App():
	window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML window"),
	navLeft(sf::Vector2f(0,0), sf::Vector2f(350,600)),
	navRight(sf::Vector2f(450, 0), sf::Vector2f(350, 600))
{
	for (int i = 0; i < 3; i++) {
		buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE),
			sf::Vector2f(window.getSize().x / 2 - BUTTON_SIZE/2,
				BUTTON_SIZE*2*i+BUTTON_SIZE*2),
				sf::Color::Color(217, 217, 217, 255),
				sf::Color::Color(74, 74, 74, 255),
				24));
		
	}
	buttons[0].setText("C");
	buttons[1].setText("M");
	buttons[2].setText("D");
	
}

void App::run()
{
	while (window.isOpen()) {
		processEvent();
		update();
		render();
	}

}

void App::render()
{

	window.clear();
	navLeft.render(window);
	navRight.render(window);
	for (auto but : buttons) {
		but.render(window);
	}
	window.display();

}

void App::processEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

	
		if (event.type == sf::Event::MouseButtonPressed) {

			sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);

			for (int i = 0; i < buttons.size(); i++) {
				//std::cout << event.mouseButton.x << " : " << button.getRectangle().getGlobalBounds().contains(localPosition) << std::endl;
				//std::cout << event.mouseButton.y << " : " << button.getRectangle().getGlobalBounds().contains(localPosition) << std::endl;
				if (buttons[i].getRectangle().getGlobalBounds().contains(localPosition)) {
					std::cout << "yes" << std::endl;;
					std::cout << buttons[i].getFontColor().toInteger() << std::endl;
					std::cout << buttons[i].getBackColor().toInteger() << std::endl;
					sf::Color buf = buttons[i].getBackColor();
					buttons[i].changeBackColor(buttons[i].getFontColor());
					buttons[i].setFontColor(buf);
					switch (i) {
					case 0:
						operation = "C";
						break;
					case 1:
						operation = "M";
						break;
					case 2:
						operation = "D";
						break;
					}
					
				}
			}

		}
		if (event.type == sf::Event::MouseButtonReleased) {
			sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);

			for (int i = 0; i < buttons.size(); i++) {
				if (buttons[i].getRectangle().getGlobalBounds().contains(localPosition)) {
					std::cout << "yes" << std::endl;;
					std::cout << buttons[i].getFontColor().toInteger() << std::endl;
					std::cout << buttons[i].getBackColor().toInteger() << std::endl;
					sf::Color buf = buttons[i].getBackColor();
					buttons[i].changeBackColor(buttons[i].getFontColor());
					buttons[i].setFontColor(buf);


				}
			}
		}

		if (operation == "D") {
				navLeft.removeField();
				navRight.removeField();
			operation = "";
		}
		if (operation == "C") {
				navLeft.copyOut(navRight);
				navRight.copyOut(navLeft);
			operation = "";
		}
		if (operation == "M") {
				navLeft.moveOut(navRight);
				navRight.moveOut(navLeft);
			operation = "";
		}

		navLeft.processEvent(event, window);
		navRight.processEvent(event, window);
		

	}

}

void App::update()
{
	navLeft.updateFields();

	navRight.updateFields();

	

}
