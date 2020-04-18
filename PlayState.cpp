#include "PlayState.h"

#include "Grass.h"
#include "Root.h"

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

	cursor.setTexture(loadTexture("Resource/Image/Cursor.png"));
	cursor.setOrigin(6, 6);

	buildWorld(50, 50);

	player.setState(this);
	player.setPosition(worldSize.x / 2 * 10, worldSize.y / 2 * 10 + 10);
	player.init();

	cameraPosition = player.getPosition() - sf::Vector2f(120, 70);
}

void PlayState::gotEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (!getGridObject(getCursorGridLocation().x, getCursorGridLocation().y)) {
				setGridObject(getCursorGridLocation().x, getCursorGridLocation().y, std::make_shared<Root>());
			}
		}
	}
}

void PlayState::update(sf::Time elapsed) {
	cameraPosition += (player.getPosition() - sf::Vector2f(120, 70) - cameraPosition) * elapsed.asSeconds() * 4.0f;

	for (std::shared_ptr<GridTile> &object : tileGrid) {
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

	cursor.setPosition(getCursorGridLocation().x * 10 - cameraPosition.x, getCursorGridLocation().y * 10 - cameraPosition.y);
}

void PlayState::render(sf::RenderWindow &window) {
	for (std::shared_ptr<GridTile> &object : tileGrid) {
		if (object) {
			window.draw(*object);
		}
	}
	for (std::shared_ptr<GridObject> &object : objectGrid) {
		if (object) {
			window.draw(*object);
		}
	}

	window.draw(cursor);

	window.draw(player);
	window.draw(hud);
	window.draw(testText);
}

void PlayState::buildWorld(int worldWidth, int worldHeight) {
	worldSize.x = worldWidth;
	worldSize.y = worldHeight;
	tileGrid.resize(worldSize.x * worldSize.y);
	objectGrid.resize(worldSize.x * worldSize.y);
	for (int y = 0; y < worldSize.y; y++) {
		for (int x = 0; x < worldSize.x; x++) {
			setGridTile(x, y, std::make_shared<Grass>());
			if (x == worldSize.x / 2 && y == worldSize.y / 2) {
				setGridObject(x, y, std::make_shared<Tree>());
			}
		}
	}
}

std::shared_ptr<GridTile> PlayState::getGridTile(int x, int y) {
	if (x < 0 || x > worldSize.x - 1) {
		return std::shared_ptr<GridTile>();
	}
	else if (y < 0 || y > worldSize.y - 1) {
		return std::shared_ptr<GridTile>();
	}
	else {
		return tileGrid[y * worldSize.x + x];
	}
}

void PlayState::setGridTile(int x, int y, std::shared_ptr<GridTile> newObject) {
	if (x >= 0 && x <= worldSize.x - 1 && y >= 0 || y <= worldSize.y - 1) {
		newObject->setState(this);
		newObject->setPosition(x * 10, y * 10);
		newObject->init();
		tileGrid[y * worldSize.x + x] = newObject;
	}
}

std::shared_ptr<GridObject> PlayState::getGridObject(int x, int y) {
	if (x < 0 || x > worldSize.x - 1) {
		return std::shared_ptr<GridObject>();
	}
	else if (y < 0 || y > worldSize.y - 1) {
		return std::shared_ptr<GridObject>();
	}
	else {
		return objectGrid[y * worldSize.x + x];
	}
}

void PlayState::setGridObject(int x, int y, std::shared_ptr<GridObject> newObject) {
	if (x >= 0 && x <= worldSize.x - 1 && y >= 0 || y <= worldSize.y - 1) {
		newObject->setState(this);
		newObject->setPosition(x * 10, y * 10);
		newObject->init();
		objectGrid[y * worldSize.x + x] = newObject;
	}
}

sf::Vector2i PlayState::worldLocationToGrid(sf::Vector2f location) {
	return sf::Vector2i((location.x + 5) / 10, (location.y + 5) / 10);
}

sf::Vector2f PlayState::screenLocationToWorld(sf::Vector2f location) {
	return sf::Vector2f(location + cameraPosition);
}

sf::Vector2f PlayState::getCursorLocation() {
	return (sf::Vector2f(sf::Mouse::getPosition(*game->getWindow())) - game->screenOffset) / float(game->scale);
}

sf::Vector2i PlayState::getCursorGridLocation() {
	return worldLocationToGrid(screenLocationToWorld(getCursorLocation()));
}
