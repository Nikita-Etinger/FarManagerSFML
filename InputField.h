#pragma once
#include "Field.h"
class InputField: public Field
{
public:
	InputField(sf::Vector2f size, sf::Vector2f position, sf::Color colorBack, sf::Color colorFont, int fontSize);
};

