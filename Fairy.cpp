#include "Fairy.h"

#include "PlayState.h"

void Fairy::init() {
	bodySprite.setTexture(state->loadTexture("Resource/Image/Fairy.png"));
	bodySprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
	bodySprite.setOrigin(5, 5);

	color = sf::Color(234, 136, 155);
}

void Fairy::update(sf::Time elapsed) {
	updateVelocity(elapsed);
	move(velocity * elapsed.asSeconds());
	// Tether player to tree
	tetherPoint = state->getNearestOwned(getPosition()) ? state->getNearestOwned(getPosition())->getPosition() : getPosition();
	tetherDistance = std::sqrt(std::pow(tetherPoint.x - getPosition().x, 2) + std::pow(tetherPoint.y - getPosition().y, 2));
	if (tetherDistance > maxTetherDistance) {
		move((tetherPoint - getPosition()) * elapsed.asSeconds());
	}

	updateAnimation(elapsed);

	bodySprite.setPosition(getPosition() - state->cameraPosition);
}

void Fairy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (tetherDistance > maxTetherDistance / 2) {
		sf::Color tetherColor = color;
		tetherColor.a = std::min(255.0f, 255 * (tetherDistance - maxTetherDistance / 2) / (maxTetherDistance / 2));
		sf::Color transparent = color;
		transparent.a = 0;
		sf::Vertex tether[] = {
			sf::Vertex(getPosition() - state->cameraPosition, tetherColor),
			sf::Vertex(tetherPoint - state->cameraPosition, transparent)
		};
		target.draw(tether, 2, sf::Lines);
	}

	target.draw(bodySprite);
}

void Fairy::updateVelocity(sf::Time elapsed) {
	// Take player input
	bool acceleratingX = false;
	bool acceleratingY = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity.y -= acceleration * elapsed.asSeconds();
		acceleratingY = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		velocity.y += acceleration * elapsed.asSeconds();
		acceleratingY = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x -= acceleration * elapsed.asSeconds();
		acceleratingX = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x += acceleration * elapsed.asSeconds();
		acceleratingX = true;
	}
	// Cap velocity
	float speed = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
	if (speed > topSpeed) {
		velocity *= topSpeed / speed;
	}

	// Slow down if no input is detected
	if (!acceleratingX) {
		if (velocity.x > 0) {
			velocity.x -= acceleration * elapsed.asSeconds();
			if (velocity.x < 0) {
				velocity.x = 0;
			}
		}
		else if (velocity.x < 0) {
			velocity.x += acceleration * elapsed.asSeconds();
			if (velocity.x > 0) {
				velocity.x = 0;
			}
		}
	}
	if (!acceleratingY) {
		if (velocity.y > 0) {
			velocity.y -= acceleration * elapsed.asSeconds();
			if (velocity.y < 0) {
				velocity.y = 0;
			}
		}
		else if (velocity.y < 0) {
			velocity.y += acceleration * elapsed.asSeconds();
			if (velocity.y > 0) {
				velocity.y = 0;
			}
		}
	}
}

void Fairy::updateAnimation(sf::Time elapsed) {
	frameTime += elapsed.asSeconds();
	if (((velocity.x != 0 || velocity.y != 0) && frameTime > 0.08) || frameTime > 0.1) {
		frameTime = 0;
		frame++;
		if ((velocity.x != 0 || velocity.y != 0)) {
			state->createParticle(getPosition() + sf::Vector2f(std::rand() % 5 - 2, std::rand() % 7 - 3), -velocity / 10.0f + sf::Vector2f(0, 5), color);
		}
	}
	if (frame > 6) {
		frame = 0;
	}

	bodySprite.setTextureRect(sf::IntRect(10 * frame, 0, 10, 10));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		bodySprite.setScale(-1, 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		bodySprite.setScale(1, 1);
	}
}
