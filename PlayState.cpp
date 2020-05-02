#include "PlayState.h"

#include "Tree.h"
#include "Ruin.h"

PlayState::PlayState() {

}

PlayState::~PlayState() {

}

void PlayState::init() {
	gameOverlay.setSize(sf::Vector2f(240, 135));
	gameOverlay.setFillColor(sf::Color::Black);

	gameText.setTexture(loadTexture("Resource/Image/Font.png"));
	gameText.setPosition(135 / 2 - 5, 30);
	gameText.setText("Protect the Grove");
	gameText.setColor(sf::Color::White);

	cursor.setTexture(loadTexture("Resource/Image/Cursor.png"));
	cursor.setOrigin(6, 6);

	transitionOverlay.setSize(sf::Vector2f(240, 135));
	transitionOverlay.setFillColor(sf::Color::Transparent);
	rainOverlay.setSize(sf::Vector2f(240, 135));
	rainOverlay.setFillColor(sf::Color::Transparent);
	nightOverlay.setSize(sf::Vector2f(240, 135));
	nightOverlay.setFillColor(sf::Color::Transparent);

	oceanBase.setSize(sf::Vector2f(240, 135));
	oceanBase.setFillColor(sf::Color(0, 148, 255));
	loadTexture("Resource/Image/Ocean.png").setRepeated(true);
	oceanOverlay.setTexture(loadTexture("Resource/Image/Ocean.png"));
	oceanOverlay.setTextureRect(sf::IntRect(0, 0, 240, 135));
	oceanOverlay.setColor(sf::Color(119, 198, 255));
	oceanUnderlay.setTexture(loadTexture("Resource/Image/Ocean.png"));
	oceanUnderlay.setTextureRect(sf::IntRect(0, 0, 240, 135));
	oceanUnderlay.setOrigin(240, 0);
	oceanUnderlay.setScale(-1, 1);
	oceanUnderlay.setColor(sf::Color(57, 172, 255));

	rangeFinder.setFillColor(sf::Color::Transparent);
	rangeFinder.setOutlineColor(sf::Color::White);
	rangeFinder.setOutlineThickness(2);

	//dayMusic.openFromFile("Resource/Music/Day.ogg");
	//rainMusic.openFromFile("Resource/Music/RainyDay.ogg");
	//nightMusic.openFromFile("Resource/Music/Night.ogg");

	buildWorld(105, 105);

	player.setState(this);
	player.setPosition(worldSize.x / 2 * 10, worldSize.y / 2 * 10 + 10);
	player.init();

	cameraPosition = player.getPosition() - sf::Vector2f(120, 70);

	calculateMaxResources();
	water = maxWater;
	nutrients = maxNutrients / 2;

	hud.setState(this);
	hud.init();

	map.setState(this);
	map.init();

	dayMusic.play();
}

void PlayState::gotEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (!isCursorOnHud()) {
				std::shared_ptr<GridObject> object = getGridObject(getCursorGridLocation().x, getCursorGridLocation().y);
				if (object && !object->dead && object->playerOwned) {
					clickedObject = object;
				}
			}
			if (!map.isCursorOnMap() && selectedObject) {
				sf::IntRect closeButton(240 - 14, 135 - 110, 12, 12);
				sf::IntRect trashButton(240 - 14, 135 - 56, 12, 12);
				sf::IntRect upgrade1Button(240 - 14, 135 - 42, 12, 13);
				sf::IntRect upgrade2Button(240 - 14, 135 - 28 - 1, 12, 14);
				sf::IntRect upgrade3Button(240 - 14, 135 - 14 - 1, 12, 13);
				if (closeButton.contains(getCursorLocation().x, getCursorLocation().y)) {
					selectedObject = std::shared_ptr<GridObject>();
					ignoreThisClick = true;
				}
				if (isOwnedTree(selectedObject) && trashButton.contains(getCursorLocation().x, getCursorLocation().y)) {
					selectedObject->kill();
					ignoreThisClick = true;
				}
				if (upgrade1Button.contains(getCursorLocation().x, getCursorLocation().y)) {
					hud.chooseUpgrade(0);
				}
				if (upgrade2Button.contains(getCursorLocation().x, getCursorLocation().y)) {
					hud.chooseUpgrade(1);
				}
				if (upgrade3Button.contains(getCursorLocation().x, getCursorLocation().y)) {
					hud.chooseUpgrade(2);
				}
			}
			if (map.isCursorOnButton()) {
				map.toggleMap();
				ignoreThisClick = true;
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Right) {
			if (selectedObject) {
				selectedObject = std::shared_ptr<GridObject>();
				ignoreThisClick = true;
			}
			if (map.isMapOpen()) {
				map.toggleMap();
				ignoreThisClick = true;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (!isCursorOnHud()) {
				std::shared_ptr<GridObject> object = getGridObject(getCursorGridLocation().x, getCursorGridLocation().y);
				if (object && object == clickedObject && !object->dead && object->playerOwned) {
					selectedObject = object;
					clickedObject = std::shared_ptr<GridObject>();
					hud.populateInfo(selectedObject);
				}
			}
		}
	}
	else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Tab || event.key.code == sf::Keyboard::Escape) {
			if (selectedObject) {
				selectedObject = std::shared_ptr<GridObject>();
			}
			if (map.isMapOpen()) {
				map.toggleMap();
			}
		}
		else if (event.key.code == sf::Keyboard::Num1) {
			if (selectedObject) {
				hud.chooseUpgrade(0);
			}
		}
		else if (event.key.code == sf::Keyboard::Num2) {
			if (selectedObject) {
				hud.chooseUpgrade(1);
			}
		}
		else if (event.key.code == sf::Keyboard::Num3) {
			if (selectedObject) {
				hud.chooseUpgrade(2);
			}
		}
		else if (event.key.code == sf::Keyboard::E) {
			map.toggleMap();
		}
		else if (godMode && event.key.code == sf::Keyboard::O) {
			revealMap(sf::Vector2i(), 200);
		}
		else if (godMode && event.key.code == sf::Keyboard::P) {
			game->changeState(new PlayState());
		}
		else if (godMode && (event.key.code == sf::Keyboard::B || event.key.code == sf::Keyboard::N || event.key.code == sf::Keyboard::M)) {
			std::shared_ptr<Spirit> spirit = std::make_shared<Spirit>();
			spirit->setState(this);
			spirit->setPosition(getCursorLocation() + cameraPosition);
			spirit->init();
			spirit->setPosition(getCursorLocation() + cameraPosition);
			spirit->setType(event.key.code == sf::Keyboard::B ? "Normal" : event.key.code == sf::Keyboard::N ? "Tall" : "Double");
			spirits.push_back(spirit);
		}
		else if (godMode && event.key.code == sf::Keyboard::X) {
			gainNutrients(500);
			gainWater(500);
			gainLight(500);
		}
	}
}

void PlayState::update(sf::Time elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && hud.isCursorOnFastButton())) {
		timeSpeed = 10;
	}
	else {
		timeSpeed = 1;
	}

	sf::Time adjustedElapsed = sf::seconds(elapsed.asSeconds() * timeSpeed);
	if (timeSpeed <= 0) {
		adjustedElapsed = sf::Time::Zero;
	}

	if (std::fmod(time + adjustedElapsed.asSeconds(), 0.5f) < std::fmod(time, 0.5f)) {
		for (std::shared_ptr<GridObject> &object : objectGrid) {
			if (object) {
				object->onHalfSecond();
			}
		}
	}
	if (timeSpeed > 0) {
		time += elapsed.asSeconds() * timeSpeed;
		totalTime += elapsed.asSeconds() * timeSpeed;
	}
	
	if (time >= secondsPerDay) {
		time = 0;
		for (std::shared_ptr<GridObject> &object : objectGrid) {
			if (object) {
				object->onHour(hour);
			}
		}
		hour += 1;
		if (hour > 10) {
			hour = 0;
			rainCooldown -= 1;
			if (rainCooldown == 0) {
				rainCooldown = 3 + std::rand() % 3;
				weather = rainy;
			}
			else {
				weather = sunny;
			}
			for (std::shared_ptr<GridObject> &object : objectGrid) {
				if (object) {
					object->onDay();
				}
			}
			day += 1;
		}
		if (hour == 2) {
			startDay();
		}
		else if (hour == 9) {
			startNight();
		}
	}
	updateOverlays();

	if (gameOver) {
		cameraPosition += (sf::Vector2f(worldSize / 2) * 10.0f - sf::Vector2f(120, 70) - cameraPosition) * elapsed.asSeconds() * 5.0f;
	}
	else if (selectedObject) {
		cameraPosition += (selectedObject->getPosition() - sf::Vector2f(86, 80) - cameraPosition) * elapsed.asSeconds() * 5.0f;

		if (isOwnedTree(selectedObject)) {
			rangeFinder.setRadius(std::dynamic_pointer_cast<Tree>(selectedObject)->stats.range * 10 - 2);
			rangeFinder.setOrigin(rangeFinder.getRadius(), rangeFinder.getRadius());
			rangeFinder.setPosition(selectedObject->getPosition() - cameraPosition);
		}
	}
	else {
		cameraPosition += (player.getPosition() - sf::Vector2f(120, 70) - cameraPosition) * elapsed.asSeconds() * 5.0f;
	}

	updateParticles(elapsed);

	if (weather == rainy && hour >= 2 && hour <= 8) {
		sf::Vector2f position = cameraPosition + sf::Vector2f(std::rand() % 240, std::rand() % 135 - 60);
		createParticle(position, sf::Vector2f(-20, 200), sf::Color(119, 198, 255));
		position = cameraPosition + sf::Vector2f(std::rand() % 240, std::rand() % 135 - 60);
		createParticle(position, sf::Vector2f(-20, 200), sf::Color(119, 198, 255));
		position = cameraPosition + sf::Vector2f(std::rand() % 240, std::rand() % 135 - 60);
		createParticle(position, sf::Vector2f(-20, 200), sf::Color(119, 198, 255));
	}

	if (!isCursorOnHud() && !selectedObject && !ignoreThisClick) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i gridLocation = getCursorGridLocation();
			if (!getGridObject(gridLocation.x, gridLocation.y) && getGridTile(gridLocation.x, gridLocation.y)) {
				if (getDistanceToMother(gridLocation.x, gridLocation.y) < 1000000) {
					bool inOcean = getGridTile(gridLocation.x, gridLocation.y)->getType() == "Ocean";
					if (!inOcean || isResearched("Seaweed")) {
						if (spendNutrients(1, sf::Vector2f(gridLocation * 10))) {
							setGridObject(gridLocation.x, gridLocation.y, std::make_shared<Tree>(inOcean ? "Seaweed" : "Root"));
							revealMap(gridLocation, 8);
						}
					}
				}
			}
		}
		else {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				sf::Vector2i gridLocation = getCursorGridLocation();
				std::shared_ptr<GridObject> object = getGridObject(gridLocation.x, gridLocation.y);
				if (isOwnedTree(object) && (std::dynamic_pointer_cast<Tree>(object)->getType() == "Root" || std::dynamic_pointer_cast<Tree>(object)->getType() == "Seaweed")) {
					object->kill();
				}
			}
		}
	}
	if (ignoreThisClick && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		ignoreThisClick = false;
	}

	for (std::shared_ptr<GridTile> &object : tileGrid) {
		if (object) {
			object->update(adjustedElapsed);
		}
	}
	bool motherPresent = false;
	bool towersCharged = true;
	for (std::shared_ptr<GridObject> &object : objectGrid) {
		if (object) {
			if (isOwnedTree(object) && std::dynamic_pointer_cast<Tree>(object)->getType().find("Mother") != -1) {
				motherPresent = true;
			}
			else if (std::dynamic_pointer_cast<Ruin>(object) && std::dynamic_pointer_cast<Ruin>(object)->getType() == "Large" && !std::dynamic_pointer_cast<Ruin>(object)->isCharged()) {
				towersCharged = false;
			}

			if (object->dead) {
				object = std::shared_ptr<GridObject>();
			}
			else {
				object->update(adjustedElapsed);
			}
		}
	}
	if (!gameOver && motherPresent == false) {
		gameOver = true;
		gameText.setText("The mother tree has\nfallen on Day " + std::to_string(day) + ".");
	}
	else if (!gameOver && towersCharged == true) {
		gameOver = true;
		gameWon = true;
		gameText.setText("The grove is safe.\nDays taken: " + std::to_string(day));
	}
	if (!gameOver) {
		gameOverlayAlpha += (0 - gameOverlayAlpha) * elapsed.asSeconds() * 0.5;
		gameOverlay.setFillColor(sf::Color(0, 0, 0, gameOverlayAlpha));
	}
	else {
		gameOverlayAlpha += (255 - gameOverlayAlpha) * elapsed.asSeconds() * 0.5;
		gameOverlay.setFillColor(sf::Color(0, 0, 0, gameOverlayAlpha));
		dayMusic.setVolume(std::max((255 - gameOverlayAlpha) / 255.0f * 100.0f, 0.0f));
		rainMusic.setVolume(std::max((255 - gameOverlayAlpha) / 255.0f * 100.0f, 0.0f));
		nightMusic.setVolume(std::max((255 - gameOverlayAlpha) / 255.0f * 100.0f, 0.0f));
	}
	gameText.setColor(sf::Color(255, 255, 255, std::min(255.0f, gameOverlayAlpha * 2)));

	calculateMaxResources();

	for (std::shared_ptr<Spirit> &spirit : spirits) {
		spirit->update(adjustedElapsed);
	}

	if (selectedObject && selectedObject->dead) {
		selectedObject = std::shared_ptr<GridObject>();
	}

	player.update(elapsed);
	hud.update(elapsed);
	map.update(elapsed);

	oceanOverlay.setTextureRect(sf::IntRect(std::round(totalTime * 5 + cameraPosition.x), std::round(0 - totalTime * 3 + cameraPosition.y), 240, 135));
	oceanUnderlay.setTextureRect(sf::IntRect(std::round(totalTime * 4 - cameraPosition.x), std::round(0 - totalTime * 6 + cameraPosition.y), 240, 135));

	cursor.setPosition(getCursorGridLocation().x * 10 - cameraPosition.x, getCursorGridLocation().y * 10 - cameraPosition.y);
}

std::string PlayState::getTimeOfDay(int hour) {
	if (hour == 0 || hour == 1 || hour == 9 || hour == 10) {
		return "Night";
	}
	else if (hour == 2 || hour == 8) {
		return "Transition";
	}
	else {
		return "Day";
	}
}

sf::Color PlayState::getResourceColor(std::string resource) {
	if (resource == "Light") {
		return sf::Color(255, 240, 132);
	}
	else if (resource == "Water") {
		return sf::Color(0, 148, 255);
	}
	else if (resource == "Nutrients") {
		return sf::Color(204, 106, 106);
	}
	else {
		return sf::Color::White;
	}
}

void PlayState::calculateMaxResources() {
	maxLight = 0;
	maxWater = 0;
	maxNutrients = 0;
	for (std::shared_ptr<GridObject> &object : objectGrid) {
		if (isOwnedTree(object)) {
			maxLight += std::dynamic_pointer_cast<Tree>(object)->stats.maxLight;
			maxWater += std::dynamic_pointer_cast<Tree>(object)->stats.maxWater;
			maxNutrients += std::dynamic_pointer_cast<Tree>(object)->stats.maxNutrients;
		}
	}
}

void PlayState::gainLight(float gained, sf::Vector2f position) {
	light += gained;
	if (light > maxLight) {
		light = maxLight;
	}
	if (position.x >= 0) {
		for (int i = 0; i < std::floor(gained); i++) {
			createParticle(position + sf::Vector2f(-4, -4 * i), sf::Vector2f(0, -20), getResourceColor("Light"), Particle::plus, true);
		}
	}
}

bool PlayState::spendLight(float spent, sf::Vector2f position) {
	if (light >= spent) {
		light -= spent;
		if (position.x >= 0) {
			for (int i = 0; i < std::floor(spent); i++) {
				createParticle(position + sf::Vector2f(-4, -4 * i), sf::Vector2f(0, -20), getResourceColor("Light"), Particle::minus, true);
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void PlayState::gainWater(float gained, sf::Vector2f position) {
	water += gained;
	if (water > maxWater && weather != rainy) {
		water = maxWater;
	}
	if (position.x >= 0) {
		for (int i = 0; i < std::floor(gained); i++) {
			createParticle(position + sf::Vector2f(0, -4 * i), sf::Vector2f(0, -20), getResourceColor("Water"), Particle::plus, true);
		}
	}
}

bool PlayState::spendWater(float spent, sf::Vector2f position) {
	if (water >= spent) {
		water -= spent;
		if (position.x >= 0) {
			for (int i = 0; i < std::floor(spent); i++) {
				createParticle(position + sf::Vector2f(0, -4 * i), sf::Vector2f(0, -20), getResourceColor("Water"), Particle::minus, true);
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void PlayState::gainNutrients(float gained, sf::Vector2f position) {
	nutrients += gained;
	if (nutrients > maxNutrients) {
		nutrients = maxNutrients;
	}
	if (position.x >= 0) {
		for (int i = 0; i < std::floor(gained); i++) {
			createParticle(position + sf::Vector2f(4, -4 * i), sf::Vector2f(0, -20), getResourceColor("Nutrients"), Particle::plus, true);
		}
	}
}

bool PlayState::spendNutrients(float spent, sf::Vector2f position) {
	if (nutrients >= spent) {
		nutrients -= spent;
		if (position.x >= 0) {
			for (int i = 0; i < std::floor(spent); i++) {
				createParticle(position + sf::Vector2f(4, -4 * i), sf::Vector2f(0, -20), getResourceColor("Nutrients"), Particle::minus, true);
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void PlayState::createParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color, Particle::ParticleType type, bool onHud) {
	Particle particle;
	particle.type = type;
	particle.position = position;
	particle.velocity = velocity;
	particle.color = color;
	particle.onHud = onHud;
	particles.push_back(particle);
}

void PlayState::updateParticles(sf::Time elapsed) {
	auto particle = particles.begin();
	while (particle != particles.end()) {
		particle->lifetime -= elapsed.asSeconds();
		particle->velocity *= std::powf(0.2, elapsed.asSeconds());
		particle->position += particle->velocity * elapsed.asSeconds();
		if (particle->lifetime <= 0) {
			particle = particles.erase(particle);
		}
		else {
			particle++;
		}
	}
}

void PlayState::render(sf::RenderWindow &window) {
	window.draw(oceanBase);
	window.draw(oceanUnderlay);
	window.draw(oceanOverlay);

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

	sf::Sprite particleSprite(loadTexture("Resource/Image/Particles.png"));
	particleSprite.setOrigin(1, 1);
	for (Particle &particle : particles) {
		if (!particle.onHud) {
			particleSprite.setTextureRect(sf::IntRect((int)particle.type * 3, 0, 3, 3));
			particleSprite.setPosition(particle.position - cameraPosition);
			particleSprite.setColor(particle.color);
			window.draw(particleSprite);
		}
	}

	for (std::shared_ptr<Spirit> &spirit : spirits) {
		window.draw(*spirit);
	}

	window.draw(nightOverlay);
	window.draw(rainOverlay);
	window.draw(transitionOverlay);

	if (isOwnedTree(selectedObject) && std::dynamic_pointer_cast<Tree>(selectedObject)->stats.range > 0) {
		window.draw(rangeFinder);
	}

	if (!isCursorOnHud()) {
		window.draw(cursor);
	}

	window.draw(player);

	window.draw(hud);
	for (Particle &particle : particles) {
		if (particle.onHud) {
			particleSprite.setTextureRect(sf::IntRect((int)particle.type * 3, 0, 3, 3));
			particleSprite.setPosition(particle.position - cameraPosition);
			particleSprite.setColor(particle.color);
			window.draw(particleSprite);
		}
	}
	window.draw(map);

	window.draw(gameOverlay);
	window.draw(gameText);
}

void PlayState::buildWorld(int worldWidth, int worldHeight) {
	worldSize.x = worldWidth;
	worldSize.y = worldHeight;
	tileGrid.resize(worldSize.x * worldSize.y);
	objectGrid.resize(worldSize.x * worldSize.y);
	for (int y = 0; y < worldSize.y; y++) {
		for (int x = 0; x < worldSize.x; x++) {
			std::shared_ptr<GridTile> newTile = std::make_shared<GridTile>();
			newTile->setState(this);
			newTile->gridPosition = sf::Vector2i(x, y);
			newTile->setPosition(x * 10, y * 10);
			newTile->init();
			tileGrid[y * worldSize.x + x] = newTile;
			if (x > worldSize.x / 2 + 4 || x < worldSize.x / 2 - 4 || y > worldSize.y / 2 + 4 || y < worldSize.y / 2 - 4) {
				if (std::rand() % 100 == 0) {
					setGridTile(x, y, "Water");
				}
				else if (std::rand() % 100 == 0) {
					setGridTile(x, y, "Nutrients");
				}
			}
			else {
				if (x == worldSize.x / 2 - 2 && y == worldSize.y / 2 + 2) {
					setGridTile(x, y, "Water");
				}
				else if (x == worldSize.x / 2 + 2 && y == worldSize.y / 2 + 2) {
					setGridTile(x, y, "Nutrients");
				}
			}

			if (x == worldSize.x / 2 && y == worldSize.y / 2) {
				if (godMode) {
					setGridObject(x, y, std::make_shared<Tree>("Grand Mother"));
				}
				else {
					setGridObject(x, y, std::make_shared<Tree>("Mother Tree"));
				}
			}
		}
	}

	// Populate shore
	for (int i = 0; i < 20; i++) {
		sf::Vector2i location = getRandomLocation(false);
		setGridTile(location.x, location.y, "Ocean");
	}

	// Chip away at shoreline
	int totalPasses = 20;
	std::vector<int> nextWorld;
	nextWorld.resize(worldSize.x * worldSize.y);
	for (int pass = 0; pass < totalPasses; pass++) {
		for (int y = 0; y < worldSize.y; y++) {
			for (int x = 0; x < worldSize.x; x++) {
				if (pass < totalPasses - 2 && std::rand() % 9 > getSurroundingLand(x, y)) {
					nextWorld[y * worldSize.x + x] = 0;
				}
				else if (pass >= totalPasses - 2 && 5 > getSurroundingLand(x, y)) {
					nextWorld[y * worldSize.x + x] = 0;
				}
				else {
					nextWorld[y * worldSize.x + x] = 1;
				}
			}
		}
		for (int y = 0; y < worldSize.y; y++) {
			for (int x = 0; x < worldSize.x; x++) {
				if (nextWorld[y * worldSize.x + x] == 0) {
					setGridTile(x, y, "Ocean");
				}
			}
		}
	}

	createRuin("Large", "Light");
	createRuin("Large", "Water");
	createRuin("Large", "Nutrients");
	createRuin("Small", "Seaweed");
	createRuin("Small", "Willow");
	createRuin("Small", "Cactus");
	createRuin("Small", "Soybean");
	createRuin("Small", "Waterlily");
	createRuin("Small", "Glowshroom");
	createRuin("Small", "Kelp");
	createRuin("Small", "Seagrass");
	createRuin("Small", "Coral");
	createRuin("Small", "Grand Mother");

	// Add shoreline proper
	for (int y = 0; y < worldSize.y; y++) {
		for (int x = 0; x < worldSize.x; x++) {
			if (getGridTile(x, y)->getType() == "Ocean" && getSurroundingLand(x, y) > 0) {
				setGridTile(x, y, "Shore");
			}
		}
	}

	// Reveal starting area
	revealMap(worldSize / 2, 10);
}

sf::Vector2i PlayState::getRandomLocation(bool close, bool acceptWater) {
	int x = worldSize.x / 2;
	int y = worldSize.y / 2;
	if (close) {
		while (getGridObject(x, y) || (!acceptWater && (getGridTile(x, y) && getGridTile(x, y)->getType() == "Ocean"))) {
			x = worldSize.x / 4 + std::rand() % (worldSize.x / 2);
			y = worldSize.y / 4 + std::rand() % (worldSize.y / 2);
		}
	}
	else {
		while (getGridObject(x, y) || (!acceptWater && (getGridTile(x, y) && getGridTile(x, y)->getType() == "Ocean"))) {
			if (std::rand() % 2 == 0) {
				if (std::rand() % 2 == 0) {
					x = std::rand() % (worldSize.x / 4);
					y = std::rand() % worldSize.y;
				}
				else {
					x = worldSize.x / 4 * 3 + std::rand() % (worldSize.x / 4);
					y = std::rand() % worldSize.y;
				}
			}
			else {
				if (std::rand() % 2 == 0) {
					x = std::rand() % worldSize.x;
					y = std::rand() % (worldSize.y / 4);
				}
				else {
					x = std::rand() % worldSize.x;
					y = worldSize.y / 4 * 3 + std::rand() % (worldSize.y / 4);
				}
			}
		}
	}
	return sf::Vector2i(x, y);
}

void PlayState::createRuin(std::string type, std::string subType) {
	sf::Vector2i location = getRandomLocation(type == "Small" && getTreeTier(subType) == 2, type == "Small" && getTreeTier(subType) == 3);
	setGridObject(location.x, location.y, std::make_shared<Ruin>(type, subType));
}

void PlayState::spawnSpirits() {
	for (int i = 0; i < day * 2; i++) {
		std::shared_ptr<Spirit> spirit = std::make_shared<Spirit>();
		spirit->setState(this);
		if (std::rand() % 2) {
			spirit->setPosition(std::rand() % 2 ? 0 : worldSize.x * 10, std::rand() % worldSize.y * 10);
		}
		else {
			spirit->setPosition(std::rand() % worldSize.x * 10, std::rand() % 2 ? 0 : worldSize.y * 10);
		}
		spirit->init();
		spirits.push_back(spirit);
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

void PlayState::setGridTile(int x, int y, std::string newType) {
	if (x >= 0 && x <= worldSize.x - 1 && y >= 0 || y <= worldSize.y - 1) {
		tileGrid[y * worldSize.x + x]->setType(newType);
	}
}

int PlayState::getSurroundingLand(int x, int y) {
	int surroundings = 0;
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if ((dx != 0 || dy != 0) && getGridTile(x + dx, y + dy)) {
				if (getGridTile(x + dx, y + dy)->getType() != "Ocean" && getGridTile(x + dx, y + dy)->getType() != "Shore") {
					surroundings += 1;
				}
			}
		}
	}
	return surroundings;
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
		newObject->gridPosition = sf::Vector2i(x, y);
		newObject->setPosition(x * 10, y * 10);
		newObject->init();
		objectGrid[y * worldSize.x + x] = newObject;
	}
}

int PlayState::getDistanceToMother(int x, int y) {
	int distance = 1000000;
	if (isOwnedTree(getGridObject(x - 1, y))) {
		distance = std::min(distance, std::dynamic_pointer_cast<Tree>(getGridObject(x - 1, y))->distanceToMother + 1);
	}
	if (isOwnedTree(getGridObject(x + 1, y))) {
		distance = std::min(distance, std::dynamic_pointer_cast<Tree>(getGridObject(x + 1, y))->distanceToMother + 1);
	}
	if (isOwnedTree(getGridObject(x, y - 1))) {
		distance = std::min(distance, std::dynamic_pointer_cast<Tree>(getGridObject(x, y - 1))->distanceToMother + 1);
	}
	if (isOwnedTree(getGridObject(x, y + 1))) {
		distance = std::min(distance, std::dynamic_pointer_cast<Tree>(getGridObject(x, y + 1))->distanceToMother + 1);
	}
	return distance;
}

std::shared_ptr<GridObject> PlayState::getNearestOwned(sf::Vector2f position) {
	std::shared_ptr<GridObject> closest;
	float closestDistance = 1000000;
	for (std::shared_ptr<GridObject> &object : objectGrid) {
		if (isOwnedTree(object)) {
			float distance = std::sqrt(std::pow(object->getPosition().x - position.x, 2) + std::pow(object->getPosition().y - position.y, 2));
			if (distance < closestDistance) {
				closest = object;
				closestDistance = distance;
			}
		}
	}
	return closest;
}

bool PlayState::isOwnedTree(std::shared_ptr<GridObject> object) {
	return object && !object->dead && object->playerOwned && std::dynamic_pointer_cast<Tree>(object);
}

void PlayState::revealMap(sf::Vector2i location, int radius) {
	for (int y = 0; y < worldSize.y; y++) {
		for (int x = 0; x < worldSize.x; x++) {
			if (!getGridTile(x, y)->visible && sqrt(std::pow(location.x - x, 2) + std::pow(location.y - y, 2)) <= radius - 0.5) {
				getGridTile(x, y)->visible = true;
			}
		}
	}
}

std::shared_ptr<Spirit> PlayState::getClosestSpirit(sf::Vector2f position) {
	std::shared_ptr<Spirit> closest;
	float closestDistance = 1000000;
	for (std::shared_ptr<Spirit> &spirit : spirits) {
		if (!spirit->dead) {
			float distance = std::sqrt(std::pow(spirit->getPosition().x - position.x, 2) + std::pow(spirit->getPosition().y - position.y, 2));
			if (distance < closestDistance) {
				closest = spirit;
				closestDistance = distance;
			}
		}
	}
	return closest;
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

bool PlayState::isCursorOnHud() {
	return map.isCursorOnMap() || hud.isCursorOnHud();
}

sf::Vector2f PlayState::getPlayerLocation() {
	return player.getPosition();
}

bool PlayState::isResearched(std::string type) {
	if (godMode) {
		return true;
	}
	bool output = true;
	for (std::shared_ptr<GridObject> &object : objectGrid) {
		if (object) {
			if (std::dynamic_pointer_cast<Ruin>(object) && std::dynamic_pointer_cast<Ruin>(object)->getSubType() == type && !std::dynamic_pointer_cast<Ruin>(object)->isCharged()) {
				output = false;
			}
		}
	}
	return output;
}

void PlayState::startDay() {
	if (weather == rainy) {
		rainMusic.play();
	}
	else if (weather == sunny) {
		dayMusic.play();
	}
	nightMusic.stop();
	spirits.clear();
}

void PlayState::startNight() {
	dayMusic.stop();
	rainMusic.stop();
	nightMusic.play();
	spawnSpirits();
}

void PlayState::updateOverlays() {
	if (hour == 2) {
		nightOverlay.setFillColor(sf::Color(0, 0, 0, 140 * (1 - time / secondsPerDay)));
		if (weather == sunny) {
			transitionOverlay.setFillColor(sf::Color(255, 119, 56, 60 * (time / secondsPerDay)));
		}
		else {
			rainOverlay.setFillColor(sf::Color(35, 43, 90, 60 * (time / secondsPerDay)));
		}
	}
	else if (hour == 3) {
		if (weather == sunny) {
			transitionOverlay.setFillColor(sf::Color(255, 119, 56, 60 * (1 - time / secondsPerDay)));
		}
	}
	else if (hour == 7) {
		if (weather == sunny) {
			transitionOverlay.setFillColor(sf::Color(255, 119, 56, 60 * (time / secondsPerDay)));
		}
	}
	else if (hour == 8) {
		if (weather == sunny) {
			transitionOverlay.setFillColor(sf::Color(255, 119, 56, 60 * (1 - time / secondsPerDay)));
		}
		else {
			rainOverlay.setFillColor(sf::Color(35, 43, 90, 60 * (1 - time / secondsPerDay)));
		}
		nightOverlay.setFillColor(sf::Color(0, 0, 0, 140 * (time / secondsPerDay)));
	}
}
