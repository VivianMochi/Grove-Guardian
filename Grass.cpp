#include "Grass.h"

#include "PlayState.h"

void Grass::init() {
	sprite.setTexture(state->loadTexture("Resource/Image/Tiles.png"));
	sprite.setTextureRect(sf::IntRect(std::rand() % 4 * 10, 0, 10, 10));
	sprite.setOrigin(5, 5);
}

void Grass::update(sf::Time elapsed) {
	sprite.setPosition(getPosition() - state->cameraPosition);
}

void Grass::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
