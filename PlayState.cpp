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
	player.setPosition(50, 50);
	player.init();

	tree.setState(this);
	tree.setPosition(100, 60);
	tree.init();

	hud.setState(this);
	hud.init();
}

void PlayState::gotEvent(sf::Event event) {

}

void PlayState::update(sf::Time elapsed) {
	cameraPosition += (player.getPosition() - sf::Vector2f(120, 70) - cameraPosition) * elapsed.asSeconds() * 4.0f;

	player.update(elapsed);
	tree.update(elapsed);
	hud.update(elapsed);
}

void PlayState::render(sf::RenderWindow &window) {
	window.draw(tree);
	window.draw(player);
	window.draw(hud);
	window.draw(testText);
}
