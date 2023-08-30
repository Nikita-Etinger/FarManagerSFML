#include "Field.h"
#include "config.h"
#include <iostream>




Field::Field()
{

}

Field::Field(sf::Vector2f size, sf::Vector2f position, sf::Color colorBack, sf::Color colorFont, int fontSize) :
	rectangle(size)
{
	this->active = false;
	this->colorBack = colorBack;
	this->colorFont = colorFont;
	this->fontSize = fontSize;
	this->position = position;
	rectangle.setFillColor(colorBack);
	rectangle.setPosition(position);
	text.setFillColor(colorFont);
	text.setCharacterSize(fontSize);
	text.setPosition(position.x+10, position.y + BUTTON_SIZE / 2 - fontSize / 2);





}


void Field::render(sf::RenderWindow& window)
{
	window.draw(rectangle);
	text.setFont(font);
	font.loadFromFile("arial.ttf");
	window.draw(text);


}

void Field::setText(std::string str)
{
	this->text.setString(str);
	this->str = str;
}

std::string Field::getText()
{
	return text.getString();
}

void Field::changeBackColor(sf::Color colorBack)
{
	rectangle.setFillColor(colorBack);
}

void Field::setFontColor(sf::Color color)
{
	this->colorFont = color;
	text.setFillColor(color);
}

sf::RectangleShape& Field::getRectangle()
{
	return rectangle;
}

sf::Color Field::getFontColor()
{
	return colorFont;
}

sf::Color Field::getBackColor()
{
	return rectangle.getFillColor();
}

bool Field::getActive()
{
	return active;
}

void Field::setActive(bool status)
{
	active = status;
	(!active)?rectangle.setFillColor(colorBack):rectangle.setFillColor(sf::Color::Magenta);
	
}

void Field::setPosition(sf::Vector2f newPosition)
{

	rectangle.setPosition(newPosition);

	text.setPosition(newPosition.x + 10, newPosition.y + BUTTON_SIZE / 2 - fontSize / 2);

}
Field::Field(const Field& other) :
	rectangle(other.rectangle),
	text(other.text),
	font(other.font) 
{

	this->active = other.active;
	this->colorBack = other.colorBack;
	this->colorFont = other.colorFont;
	this->fontSize = other.fontSize;
	this->position = other.position;

	text.setFont(this->font);
}

Field& Field::operator=(const Field& other)
{
	if (this != &other)
	{

		this->active = other.active;
		this->colorBack = other.colorBack;
		this->colorFont = other.colorFont;
		this->fontSize = other.fontSize;
		this->position = other.position;

		this->font = other.font;


		this->rectangle = other.rectangle;
		this->text = other.text;

		this->text.setFont(this->font);
	}
	return *this;
}
