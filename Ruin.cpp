#include "Ruin.h"

#include "PlayState.h"

Ruin::Ruin(std::string type, std::string subType) : type(type), subType(subType) {

}

void Ruin::init() {
	setType(type, subType);
}

void Ruin::update(sf::Time elapsed) {
	playerOwned = state->getDistanceToMother(gridPosition.x, gridPosition.y) < 1000000;

	if (isCharged()) {
		sf::IntRect newRect = sprite.getTextureRect();
		newRect.top = newRect.height * 2;
		sprite.setTextureRect(newRect);
	}
	else if (playerOwned) {
		sf::IntRect newRect = sprite.getTextureRect();
		newRect.top = newRect.height;
		sprite.setTextureRect(newRect);
	}
	else {
		sf::IntRect newRect = sprite.getTextureRect();
		newRect.top = 0;
		sprite.setTextureRect(newRect);
	}

	sprite.setPosition(getPosition() - state->cameraPosition);
}

sf::Color Ruin::getMapColor() {
	if (!state->getGridTile(gridPosition.x, gridPosition.y)->visible) {
		return sf::Color(30, 30, 30);
	}
	else if (type == "Large") {
		return sf::Color(20, 20, 20);
	}
	else {
		return sf::Color(70, 70, 70);
	}
}

void Ruin::setType(std::string type, std::string subType) {
	this->type = type;
	this->subType = subType;
	if (type == "Small") {
		sprite.setTexture(state->loadTexture("Resource/Image/Ruin.png"));
		sprite.setTextureRect(sf::IntRect(state->getGridTile(gridPosition.x, gridPosition.y)->getType() == "Ocean" ? 10 : 0, 0, 10, 20));
		sprite.setOrigin(5, 15);
		maxCharge = 40;
	}
	else if (type == "Large") {
		sprite.setTexture(state->loadTexture("Resource/Image/LargeRuin.png"));
		if (subType == "Light") {
			sprite.setTextureRect(sf::IntRect(0, 0, 16, 30));
		}
		else if (subType == "Water") {
			sprite.setTextureRect(sf::IntRect(16, 0, 16, 30));
		}
		else if (subType == "Nutrients") {
			sprite.setTextureRect(sf::IntRect(32, 0, 16, 30));
		}
		sprite.setOrigin(8, 25);
		maxCharge = 500;
	}
}

std::string Ruin::getType() {
	return type;
}

std::string Ruin::getSubType() {
	return subType;
}

bool Ruin::isCharged() {
	return charge >= maxCharge;
}

void Ruin::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
}
