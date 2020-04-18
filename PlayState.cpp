#include "PlayState.h"

PlayState::PlayState() {

}

PlayState::~PlayState() {

}

void PlayState::init() {
	testText.setTexture(loadTexture("Resource/Image/Font.png"));
	testText.setPosition(2, 2);
	testText.setText("LD64");
	testText.setColor(sf::Color::White);
}

void PlayState::gotEvent(sf::Event event) {

}

void PlayState::update(sf::Time elapsed) {

}

void PlayState::render(sf::RenderWindow &window) {
	window.draw(testText);
}
