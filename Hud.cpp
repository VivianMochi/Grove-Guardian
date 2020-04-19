#include "Hud.h"

#include "PlayState.h"

void Hud::init() {
	dayBarSprite.setTexture(state->loadTexture("Resource/Image/DayBar.png"));
	dayBarSprite.setTextureRect(sf::IntRect(0, 0, 124, 10));
	dayBarSprite.setPosition(58, 0);

	dayBar.setFillColor(sf::Color(200, 200, 200));
	dayBar.setPosition(dayBarSprite.getPosition() + sf::Vector2f(3, 3));

	dayBarBg.setTexture(state->loadTexture("Resource/Image/DayBar.png"));
	dayBarBg.setTextureRect(sf::IntRect(0, 20, 124, 10));
	dayBarBg.setPosition(58, 0);

	sunSprite.setTexture(state->loadTexture("Resource/Image/DayBar.png"));
	sunSprite.setTextureRect(sf::IntRect(0, 10, 16, 8));
	sunSprite.setPosition(dayBarSprite.getPosition() + sf::Vector2f(state->hour * 11 - 1, 9));

	resourcesHud.setTexture(state->loadTexture("Resource/Image/ResourcesHud.png"));

	dayText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	dayText.setColor(sf::Color::White);
	dayText.setPosition(4, 4);

	lightText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	lightText.setColor(state->getResourceColor("Light"));
	lightText.setPosition(14, 18);

	waterText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	waterText.setColor(state->getResourceColor("Water"));
	waterText.setPosition(14, 28);

	nutrientsText.setTexture(state->loadTexture("Resource/Image/Font.png"));
	nutrientsText.setColor(state->getResourceColor("Nutrients"));
	nutrientsText.setPosition(14, 38);
}

void Hud::update(sf::Time elapsed) {
	dayBar.setSize(sf::Vector2f(11 * state->hour + std::floor(8 * state->time / state->secondsPerDay), 4));

	if (state->getTimeOfDay() == "Night") {
		sunSprite.setTextureRect(sf::IntRect(32, 10, 16, 8));
	}
	else if (state->getTimeOfDay() == "Transition") {
		sunSprite.setTextureRect(sf::IntRect(16, 10, 16, 8));
	}
	else {
		sunSprite.setTextureRect(sf::IntRect(0, 10, 16, 8));
	}
	sf::Vector2f sunSpriteDesiredLocation = dayBarSprite.getPosition() + sf::Vector2f(state->hour * 11 - 1, 9);
	if (sunSpriteDesiredLocation.x < dayBarSprite.getPosition().x + 1) {
		sunSpriteDesiredLocation.x = dayBarSprite.getPosition().x + 1;
	}
	else if (sunSpriteDesiredLocation.x > dayBarSprite.getPosition().x + 107) {
		sunSpriteDesiredLocation.x = dayBarSprite.getPosition().x + 107;
	}
	sunSprite.move((sunSpriteDesiredLocation - sunSprite.getPosition()) * elapsed.asSeconds() * 4.0f);

	dayText.setText("Day " + std::to_string(state->day));
	lightText.setText(std::to_string(int(state->light)) + "/" + std::to_string(state->maxLight));
	waterText.setText(std::to_string(int(state->water)) + "/" + std::to_string(state->maxWater));
	nutrientsText.setText(std::to_string(int(state->nutrients)) + "/" + std::to_string(state->maxNutrients));
}

void Hud::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(resourcesHud);
	target.draw(dayText);
	target.draw(lightText);
	target.draw(waterText);
	target.draw(nutrientsText);

	target.draw(dayBarBg);
	target.draw(dayBar);
	target.draw(sunSprite);
	target.draw(dayBarSprite);
}
