#include "Leaf.h"

#include "PlayState.h"

void Leaf::init() {
	sprite.setTexture(state->loadTexture("Resource/Image/Leaf.png"));
	sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
	sprite.setOrigin(5, 5);

	generateFramePeriod();
}

void Leaf::update(sf::Time elapsed) {
	frameTime += elapsed.asSeconds();
	if (frameTime > framePeriod) {
		frameTime = 0;
		frame++;
		if (std::rand() % 4 == 0) {
			if (offset == 0) {
				offset = -1;
			}
			else {
				offset = 0;
			}
		}
	}
	if (frame > 3) {
		frame = 0;
	}

	sprite.setTextureRect(sf::IntRect(10 * frame, 0, 10, 10));
	sprite.setPosition(getPosition() - state->cameraPosition + sf::Vector2f(offset, 0));
}

void Leaf::generateFramePeriod() {
	frame = std::rand() % 4;
	framePeriod = 0.2 + std::rand() % 10 * .04;
}

void Leaf::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
