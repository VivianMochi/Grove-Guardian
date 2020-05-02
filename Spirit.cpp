#include "Spirit.h"

#include "PlayState.h"

void Spirit::init() {
	if (state->day >= 4 && std::rand() % 5 == 0) {
		type = "Tall";
		topSpeed = 20;
	}

	if (type == "Normal") {
		sprite.setTexture(state->loadTexture("Resource/Image/Spirit.png"));
		sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
		sprite.setOrigin(5, 5);
	}
	else if (type == "Tall") {
		sprite.setTexture(state->loadTexture("Resource/Image/TallSpirit.png"));
		sprite.setTextureRect(sf::IntRect(0, 0, 10, 30));
		sprite.setOrigin(5, 25);
	}

	target = state->getNearestOwned(getPosition());
	if (target) {
		float distance = std::sqrt(std::pow(target->getPosition().x - getPosition().x, 2) + std::pow(target->getPosition().y - getPosition().y, 2));
		move((target->getPosition() - getPosition()) * (distance - (180 + std::rand() % 320)) / distance);
	}

	framePeriod = std::rand() % 6 * .01 + 0.08;
}

void Spirit::update(sf::Time elapsed) {
	if (!dead) {
		if (target && target->dead) {
			target = state->getNearestOwned(getPosition());
			if (!target) {
				kill();
			}
		}
		updateVelocity(elapsed);
		move(velocity * elapsed.asSeconds());
		if (target && std::abs(target->getPosition().x - getPosition().x) < 4 && std::abs(target->getPosition().y - getPosition().y) < 4) {
			target->kill();
			if (type == "Normal") {
				kill();
			}
		}

		updateAnimation(elapsed);

		sprite.setPosition(getPosition() - state->cameraPosition);
	}
}

void Spirit::kill() {
	dead = true;
	state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(0, -6), sf::Color::Black);
	state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(1, -5), sf::Color::Black);
	state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(-1, -5), sf::Color::Black);
}

void Spirit::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (!dead) {
		target.draw(sprite);
	}
}

void Spirit::updateVelocity(sf::Time elapsed) {
	if (target) {
		velocity += (target->getPosition() - getPosition()) * elapsed.asSeconds() * 5.0f;
	}
	// Cap velocity
	float speed = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
	if (speed > topSpeed) {
		velocity *= topSpeed / speed;
	}
}

void Spirit::updateAnimation(sf::Time elapsed) {
	frameTime += elapsed.asSeconds();
	if (frameTime > framePeriod) {
		frameTime = 0;
		frame++;
		state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), -velocity / 10.0f + sf::Vector2f(0, 5), sf::Color::Black);
	}
	if (frame > 3) {
		frame = 0;
	}

	if (type == "Normal") {
		sprite.setTextureRect(sf::IntRect(10 * frame, 0, 10, 10));
	}
	else if (type == "Tall") {
		sprite.setTextureRect(sf::IntRect(10 * frame, 0, 10, 30));
	}
	if (velocity.x < 0) {
		sprite.setScale(-1, 1);
	}
	else if (velocity.x > 0) {
		sprite.setScale(1, 1);
	}
}
