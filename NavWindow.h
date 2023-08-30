#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "InputField.h"
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
class NavWindow
{
	Field* activeField = nullptr;
	std::vector<Field> fields;

	sf::RectangleShape rectangle;
	sf::Font font;
	sf::Text text;
	sf::Vector2f position;
	sf::Vector2f size;
	int fontSize;

	InputField inputField;
	std::string activeText;
	std::string oldPath;

public:
	NavWindow(sf::Vector2f position, sf::Vector2f size);
	void render(sf::RenderWindow& window);
	void removeField();
	void addField(Field field);
	void processEvent(sf::Event event, sf::RenderWindow& window);
	Field* getActiveField();
	void updateField();
	void copyOut(NavWindow& NW);
	void moveOut(NavWindow& NW);
	void createFields(const std::vector<std::string>& fieldTexts);
	void updateFields();
	void renderFields(sf::RenderWindow& window);
	
};

