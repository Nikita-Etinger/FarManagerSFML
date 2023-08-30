#pragma once
#include <SFML/Graphics.hpp>

class Field
{
	sf::RectangleShape rectangle;
	sf::Font font;
	sf::Text text;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color colorFont;
	sf::Color colorBack;
	int fontSize;
protected:
	std::string str;
	bool active;
public:
	Field(const Field& other);
	Field& operator=(const Field& other);
	Field();
	Field(sf::Vector2f size, sf::Vector2f position, sf::Color colorBack, sf::Color colorFont, int fontSize);
	void render(sf::RenderWindow& window);
	void setText(std::string str);
	std::string getText();
	void changeBackColor(sf::Color colorBack);
	void setFontColor(sf::Color color);
	sf::RectangleShape& getRectangle();
	sf::Color getFontColor();
	sf::Color getBackColor();
	bool getActive();
	void setActive(bool status);
	void setPosition(sf::Vector2f newPosition);
	

};

