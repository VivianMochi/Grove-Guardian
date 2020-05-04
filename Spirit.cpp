#include "Spirit.h"

#include "PlayState.h"

void Spirit::init() {
	if (state->day >= 4 && std::rand() % 5 == 0) {
		type = "Tall";
	}
	else if (state->day >= 8 && std::rand() % 5 == 0) {
		type = "Double";
	}
	setType(type);

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
	if (type == "Double") {
		setType("Normal");
	}
	else {
		dead = true;
		makeParticle(false);
		makeParticle(false);
		makeParticle(false);
	}
}

void Spirit::setType(std::string type) {
	this->type = type;
	if (type == "Normal") {
		sprite.setTexture(state->loadTexture("Resource/Image/Spirit.png"));
		sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
		sprite.setOrigin(5, 5);
		topSpeed = 15;
	}
	else if (type == "Tall") {
		sprite.setTexture(state->loadTexture("Resource/Image/TallSpirit.png"));
		sprite.setTextureRect(sf::IntRect(0, 0, 10, 30));
		sprite.setOrigin(5, 25);
		topSpeed = 15;
	}
	else if (type == "Double") {
		sprite.setTexture(state->loadTexture("Resource/Image/DoubleSpirit.png"));
		sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
		sprite.setOrigin(10, 10);
		topSpeed = 20;
	}
}

void Spirit::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (!dead) {
		target.draw(sprite);
	}
}

void Spirit::updateVelocity(sf::Time elapsed) {
	if (target) {
		velocity += (target->getPosition() - getPosition()) * elapsed.asSeconds() * 10.0f;
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
		makeParticle();
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
	else if (type == "Double") {
		sprite.setTextureRect(sf::IntRect(20 * frame, 0, 20, 20));
	}
	if (velocity.x < 0) {
		sprite.setScale(-1, 1);
	}
	else if (velocity.x > 0) {
		sprite.setScale(1, 1);
	}
}

void Spirit::makeParticle(bool useVelocity) {
	sf::Vector2f particleVelocity = -velocity / 10.0f + sf::Vector2f(0, 5);
	if (!useVelocity) {
		particleVelocity = sf::Vector2f(0, -6);
	}
	sf::Vector2f particlePosition = getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3);
	if (type == "Tall") {
		particlePosition = getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 20 - 20);
	}
	else if (type == "Double") {
		particlePosition = getPosition() + sf::Vector2f(std::rand() % 11 - 5, std::rand() % 11 - 5);
	}
	state->createParticle(particlePosition, particleVelocity, sf::Color::Black);
}
