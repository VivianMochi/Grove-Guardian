#include "PlayState.h"

#include "Grass.h"

PlayState::PlayState() {

}

PlayState::~PlayState() {

}

void PlayState::init() {
	testText.setTexture(loadTexture("Resource/Image/Font.png"));
	testText.setPosition(2, 2);
	testText.setText("");
	testText.setColor(sf::Color::White);

	hud.setState(this);
	hud.init();

	buildWorld(50, 50);

	player.setState(this);
	player.setPosition(worldSize.x / 2 * 10, worldSize.y / 2 * 10 + 10);
	player.init();

	cameraPosition = player.getPosition() - sf::Vector2f(120, 70);
}

void PlayState::gotEvent(sf::Event event) {

}

void PlayState::update(sf::Time elapsed) {
	cameraPosition += (player.getPosition() - sf::Vector2f(120, 70) - cameraPosition) * elapsed.asSeconds() * 4.0f;

	for (std::shared_ptr<GridObject> &object : baseGrid) {
		if (object) {
			object->update(elapsed);
		}
	}
	for (std::shared_ptr<GridObject> &object : objectGrid) {
		if (object) {
			object->update(elapsed);
		}
	}

	player.update(elapsed);
	hud.update(elapsed);
}

void PlayState::render(sf::RenderWindow &window) {
	for (std::shared_ptr<GridObject> &object : baseGrid) {
		if (object) {
			window.draw(*object);
		}
	}
	for (std::shared_ptr<GridObject> &object : objectGrid) {
		if (object) {
			window.draw(*object);
		}
	}

	window.draw(player);
	window.draw(hud);
	window.draw(testText);
}

void PlayState::buildWorld(int worldWidth, int worldHeight) {
	worldSize.x = worldWidth;
	worldSize.y = worldHeight;
	baseGrid.resize(worldSize.x * worldSize.y);
	objectGrid.resize(worldSize.x * worldSize.y);
	for (int y = 0; y < worldSize.y; y++) {
		for (int x = 0; x < worldSize.x; x++) {
			setGridObject(false, x, y, std::make_shared<Grass>());
			if (x == worldSize.x / 2 && y == worldSize.y / 2) {
				setGridObject(true, x, y, std::make_shared<Tree>());
			}
		}
	}
}

std::shared_ptr<GridObject> PlayState::getGridObject(bool useObjectGrid, int x, int y) {
	if (x < 0 || x > worldSize.x - 1) {
		return std::shared_ptr<GridObject>();
	}
	else if (y < 0 || y > worldSize.y - 1) {
		return std::shared_ptr<GridObject>();
	}
	else {
		if (useObjectGrid) {
			return objectGrid[y * worldSize.x + x];
		}
		else {
			return baseGrid[y * worldSize.x + x];
		}
	}
}

void PlayState::setGridObject(bool useObjectGrid, int x, int y, std::shared_ptr<GridObject> newObject) {
	if (x >= 0 && x <= worldSize.x - 1 && y >= 0 || y <= worldSize.y - 1) {
		newObject->setState(this);
		newObject->setPosition(x * 10, y * 10);
		newObject->init();
		if (useObjectGrid) {
			objectGrid[y * worldSize.x + x] = newObject;
		}
		else {
			baseGrid[y * worldSize.x + x] = newObject;
		}
	}
}
