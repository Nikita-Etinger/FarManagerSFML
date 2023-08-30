#include "NavWindow.h"
#include "Config.h"
#include <iostream>

NavWindow::NavWindow(sf::Vector2f position, sf::Vector2f size):
	rectangle(size),
	inputField(
		sf::Vector2f(size.x, BUTTON_SIZE),
		position,
		sf::Color::Color(217, 217, 217, 255),
		sf::Color::Color(74, 74, 74, 255),
		24)
{
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(position);
	inputField.setText("./");

	for (int i = 0; i < 4; i++) {
		fields.push_back(Field(sf::Vector2f(size.x, BUTTON_SIZE),
			sf::Vector2f(position.x, position.y+(i+1)*(BUTTON_SIZE+2)),
			sf::Color::Color(130, 78, 100, 255),
			sf::Color::Color(255, 255, 255, 255),
			24));
		fields[fields.size()-1].setText("lorem2");
	}
	
}

void NavWindow::render(sf::RenderWindow& window)
{
	window.draw(rectangle);
	inputField.render(window);
	for (auto el : fields) {
		
		el.render(window);
	}
}


void NavWindow::updateField() {
	for (int i = 0; i < fields.size(); i++) {
		fields[i].setPosition(sf::Vector2f(rectangle.getPosition().x, (i + 1) * (BUTTON_SIZE + 2)));
	}


}

void NavWindow::copyOut(NavWindow& NW)
{
	Field fieldBuf;
	for (int i = 0; i < fields.size(); i++) {
		if (fields[i].getActive()) {
			fieldBuf = fields[i];
			NW.addField(fieldBuf);
			NW.updateField();
			break;
		}
	}

}

void NavWindow::moveOut(NavWindow& NW)
{
	Field fieldBuf;
	for (int i = 0; i < fields.size(); i++) {
		if (fields[i].getActive()) {
			fieldBuf = fields[i];
			removeField();
			NW.addField(fieldBuf);
			NW.updateField();
			break;
		}
	}
}
void NavWindow::removeField()
{
	for (int i = 0; i < fields.size(); i++) {
		if (fields[i].getActive()) {
			fields.erase(fields.begin() + i);
			updateField();
			break;
		}
	}
}

void NavWindow::addField(Field field)
{
	fields.push_back(field);
	updateField();
}

void NavWindow::processEvent(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed) {

		sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);

		if (inputField.getRectangle().getGlobalBounds().contains(localPosition)) {
			inputField.setActive(true);
			activeField = &inputField;
		}
		else {
			inputField.setActive(false);
			activeField = nullptr;
		}
		for (auto& x : fields) {

			if (x.getRectangle().getGlobalBounds().contains(localPosition)) {
				x.setActive(true);
				activeField = &x;
			}
			else {
				x.setActive(false);
				activeField = nullptr;
			}
		}
	}
	if (inputField.getActive()) {
		if (event.type == sf::Event::TextEntered)
		{
			if (event.KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
					inputField.setText(inputField.getText().erase(inputField.getText().size() - 1));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					inputField.setActive(false);
					activeField = nullptr;
					
				}
				else {
					char buf = static_cast<char>(event.text.unicode);
					inputField.setText(inputField.getText() + buf);
				}
			}
		}
	}
	
}
void NavWindow::updateFields() {
	fs::path folderPath = inputField.getText(); // Текущая папка

	std::vector<std::string> fieldTexts;

	for (const auto& entry : fs::directory_iterator(folderPath))
	{
		if (entry.is_regular_file())
		{
			std::string filename = entry.path().filename().string();
			fieldTexts.push_back(filename);
		}
	}

	createFields(fieldTexts);

}
void NavWindow::renderFields(sf::RenderWindow& window) {
	for (auto& x : fields) {
		x.render(window);
	}

}
void NavWindow::createFields(const std::vector<std::string>& fieldTexts)
{
	std::string activeFieldPath = "";
	if (activeField != nullptr) {

		std::string activeFieldPath = activeField->getText();
		std::cout<< activeField->getText();
	}
	fields.clear(); 

	for (const auto& text : fieldTexts) {
	 
		Field newField(
			sf::Vector2f(rectangle.getSize().x, BUTTON_SIZE),
			sf::Vector2f(rectangle.getPosition().x, rectangle.getPosition().y + (fields.size() + 1) * (BUTTON_SIZE + 2)),
			sf::Color::Color(130, 78, 100, 255),
			sf::Color::Color(255, 255, 255, 255),
			24
		);
		if (text == activeFieldPath)newField.setActive(true);
		


		newField.setText(text);
		fields.push_back(newField);
	}


}
Field* NavWindow::getActiveField()
{
	return activeField;
}


