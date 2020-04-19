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
}

void Hud::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(dayBarBg);
	target.draw(dayBar);
	target.draw(sunSprite);
	target.draw(dayBarSprite);
}
