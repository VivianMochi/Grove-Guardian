#include "PlayState.h"

PlayState::PlayState() {

}

PlayState::~PlayState() {

}

void PlayState::init() {
	testText.setTexture(loadTexture("Resource/Image/Font.png"));
	testText.setPosition(2, 2);
	testText.setText("");
	testText.setColor(sf::Color::White);

	player.setState(this);
	player.init();
	player.setPosition(50, 50);
}

void PlayState::gotEvent(sf::Event event) {

}

void PlayState::update(sf::Time elapsed) {
	player.update(elapsed);
}

void PlayState::render(sf::RenderWindow &window) {
	window.draw(player);
	window.draw(testText);
}
