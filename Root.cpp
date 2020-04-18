#include "Root.h"

#include "PlayState.h"

void Root::init() {
	sprite.setTexture(state->loadTexture("Resource/Image/Tiles.png"));
	sprite.setTextureRect(sf::IntRect(0, 10, 10, 10));
	sprite.setOrigin(5, 5);
}

void Root::update(sf::Time elapsed) {
	sprite.setPosition(getPosition() - state->cameraPosition);
}

void Root::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
