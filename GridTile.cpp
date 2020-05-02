#include "GridTile.h"

#include "PlayState.h"

void GridTile::init() {
	sprite.setTexture(state->loadTexture("Resource/Image/Tiles.png"));
	setType(type);
	sprite.setOrigin(5, 5);
	extraSprite.setTexture(state->loadTexture("Resource/Image/Tiles.png"));
	extraSprite.setOrigin(5, 5);
}

void GridTile::update(sf::Time elapsed) {
	if (getType() != "Grass" && quantity <= 0) {
		//setType("Grass");
		quantity = 10;
	}
	sprite.setPosition(getPosition() - state->cameraPosition);
	extraSprite.setPosition(getPosition() - state->cameraPosition);
}

void GridTile::setType(std::string type) {
	this->type = type;
	useExtraSprite = false;
	if (type == "Grass") {
		sprite.setTextureRect(sf::IntRect(std::rand() % 4 * 10, 0, 10, 10));
	}
	else if (type == "Water") {
		sprite.setTextureRect(sf::IntRect(40 + std::rand() % 4 * 10, 0, 10, 10));
		quantity = 10 + std::rand() % 6;
	}
	else if (type == "Ocean") {
		sprite.setTextureRect(sf::IntRect(130, 10, 10, 10));
	}
	else if (type == "Shore") {
		setShoreTexture();
	}
	else if (type == "Nutrients") {
		sprite.setTextureRect(sf::IntRect(80 + std::rand() % 4 * 10, 0, 10, 10));
		quantity = 10 + std::rand() % 6;
	}
}

std::string GridTile::getType() {
	return type;
}

sf::Color GridTile::getMapColor() {
	if (!visible) {
		return sf::Color(30, 30, 30);
	}
	else if (type == "Water") {
		return sf::Color(146, 203, 219);
	}
	else if (type == "Ocean") {
		return sf::Color(47, 146, 216);
	}
	else if (type == "Shore") {
		return sf::Color(129, 185, 210);
	}
	else if (type == "Nutrients") {
		return sf::Color(188, 77, 77);
	}
	else {
		return sf::Color(91, 130, 68);
	}
}

void GridTile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite);
	if (useExtraSprite) {
		target.draw(extraSprite);
	}
}

void GridTile::setShoreTexture() {
	int tile = 0;
	std::shared_ptr<GridTile> test;
	test = state->getGridTile(gridPosition.x, gridPosition.y - 1);
	if (test && test->getType() != "Ocean" && test->getType() != "Shore") {
		tile += 1;
	}
	test = state->getGridTile(gridPosition.x + 1, gridPosition.y);
	if (test && test->getType() != "Ocean" && test->getType() != "Shore") {
		tile += 2;
	}
	test = state->getGridTile(gridPosition.x, gridPosition.y + 1);
	if (test && test->getType() != "Ocean" && test->getType() != "Shore") {
		tile += 4;
	}
	test = state->getGridTile(gridPosition.x - 1, gridPosition.y);
	if (test && test->getType() != "Ocean" && test->getType() != "Shore") {
		tile += 8;
	}
	sprite.setTextureRect(sf::IntRect(tile * 12, 40, 10, 10));

	useExtraSprite = true;
	int extraTile = 0;
	test = state->getGridTile(gridPosition.x - 1, gridPosition.y - 1);
	if (test && test->getType() != "Ocean" && test->getType() != "Shore" && !(tile & 1) && !(tile & 8)) {
		extraTile += 1;
	}
	test = state->getGridTile(gridPosition.x + 1, gridPosition.y - 1);
	if (test && test->getType() != "Ocean" && test->getType() != "Shore" && !(tile & 1) && !(tile & 2)) {
		extraTile += 2;
	}
	test = state->getGridTile(gridPosition.x + 1, gridPosition.y + 1);
	if (test && test->getType() != "Ocean" && test->getType() != "Shore" && !(tile & 2) && !(tile & 4)) {
		extraTile += 4;
	}
	test = state->getGridTile(gridPosition.x - 1, gridPosition.y + 1);
	if (test && test->getType() != "Ocean" && test->getType() != "Shore" && !(tile & 4) && !(tile & 8)) {
		extraTile += 8;
	}
	extraSprite.setTextureRect(sf::IntRect(extraTile * 12, 60, 10, 10));
}
