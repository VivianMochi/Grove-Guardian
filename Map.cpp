#include "Map.h"

#include "PlayState.h"

void Map::init() {
	tab.setTexture(state->loadTexture("Resource/Image/MapTab.png"));
	tab.setTextureRect(sf::IntRect(0, 0, 35, 12));
	tab.setPosition(0, 123);

	map.setTexture(state->loadTexture("Resource/Image/MapTab.png"));
	map.setTextureRect(sf::IntRect(0, 10, 109, 109));
	map.setPosition(0, 135);
}

void Map::update(sf::Time elapsed) {
	sf::Vector2f tabDesiredPosition = sf::Vector2f(0, 123);
	sf::Vector2f mapDesiredPosition = sf::Vector2f(0, 135);
	if (open) {
		tabDesiredPosition.y = 16;
		tabDesiredPosition.x = 74;
		mapDesiredPosition.y = 26;
	}
	tab.move((tabDesiredPosition - tab.getPosition()) * elapsed.asSeconds() * 7.0f);
	map.move((mapDesiredPosition - map.getPosition()) * elapsed.asSeconds() * 7.0f);

	if (!open && tab.getPosition().x < 1 && tab.getPosition().x > 0) {
		tab.setPosition(tabDesiredPosition);
		tab.setTextureRect(sf::IntRect(0, 0, 35, 13));
	}
	else if (open) {
		tab.setTextureRect(sf::IntRect(35, 0, 35, 13));
	}

	blinkTime += elapsed.asSeconds();
	if (blinkTime >= 0.8) {
		blinkTime = 0;
	}
}

bool Map::isCursorOnButton() {
	sf::FloatRect buttonBox;
	buttonBox.left = tab.getPosition().x;
	buttonBox.top = tab.getPosition().y;
	buttonBox.width = 35;
	buttonBox.height = 12;
	return buttonBox.contains(state->getCursorLocation());
}

bool Map::isCursorOnMap() {
	sf::Vector2f cursorLocation = state->getCursorLocation();
	if (isCursorOnButton()) {
		return true;
	}
	else if (open && cursorLocation.x < 109 && cursorLocation.y >= 135 - 109) {
		return true;
	}
	else {
		return false;
	}
}

void Map::toggleMap() {
	open = !open;
}

void Map::setMapOpen(bool open) {
	this->open = open;
}

bool Map::isMapOpen() {
	return open;
}

void Map::renderMap(sf::RenderTarget &target) const {
	sf::RectangleShape pixel(sf::Vector2f(1, 1));
	sf::Vector2f topLeft = map.getPosition() + sf::Vector2f(54, 54) - sf::Vector2f(state->worldSize / 2);
	for (int y = 0; y < state->worldSize.y; y++) {
		for (int x = 0; x < state->worldSize.x; x++) {
			if (!((x == 0 || x == 104) && (y == 0 || y == 104))) {
				pixel.setPosition(topLeft.x + x, topLeft.y + y);
				if (state->getGridObject(x, y)) {
					pixel.setFillColor(state->getGridObject(x, y)->getMapColor());
					target.draw(pixel);
				}
				else if (state->getGridTile(x, y)) {
					pixel.setFillColor(state->getGridTile(x, y)->getMapColor());
					target.draw(pixel);
				}
			}
		}
	}

	// Render spirits
	for (const std::shared_ptr<Spirit> &spirit : state->spirits) {
		if (!spirit->dead && state->getGridTile(spirit->getPosition().x / 10, spirit->getPosition().y / 10)) {
			pixel.setPosition(topLeft + spirit->getPosition() / 10.0f);
			pixel.setFillColor(sf::Color(0, 0, 0));
			if (blinkTime >= 0.4) {
				pixel.setFillColor(sf::Color(0, 0, 0, 50));
			}
			target.draw(pixel);
		}
	}

	// Render player
	if (state->getGridTile(state->getPlayerLocation().x / 10, state->getPlayerLocation().y / 10)) {
		pixel.setPosition(topLeft + state->getPlayerLocation() / 10.0f);
		pixel.setFillColor(sf::Color(255, 0, 0));
		if (blinkTime < 0.4) {
			pixel.setFillColor(sf::Color(255, 0, 0, 50));
		}
		target.draw(pixel);
	}
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(tab);
	target.draw(map);
	if (map.getPosition().y < 133) {
		renderMap(target);
	}
}
