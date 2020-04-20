#include "Tree.h"

#include "PlayState.h"

Tree::Tree(std::string type) : type(type) {

}

void Tree::init() {
	playerOwned = true;
	setType(type);
	if (getType().find("Mother") != -1) {
		distanceToMother = 0;
	}
	else {
		distanceToMother = state->getDistanceToMother(gridPosition.x, gridPosition.y);
	}

	health = 3 + std::rand() % 30 * 0.1f;
	color = sf::Color(234, 136, 155);
}

void Tree::update(sf::Time elapsed) {
	attackCooldown -= elapsed.asSeconds() * 1.01;

	if (getType().find("Mother") == -1) {
		if (distanceToMother < state->getDistanceToMother(gridPosition.x, gridPosition.y)) {
			distanceToMother += 1;
			health -= elapsed.asSeconds();
			if (health <= 0) {
				kill();
			}
		}
		else {
			distanceToMother = state->getDistanceToMother(gridPosition.x, gridPosition.y);
		}
	}

	if (getType() == "Willow") {
		std::shared_ptr<GridTile> tileBelow = state->getGridTile(gridPosition.x, gridPosition.y);
		if (tileBelow) {
			if (tileBelow->getType() == "Water" && tileBelow->quantity > 0) {
				range = 10;
			}
			else {
				range = 5;
			}
		}
	}

	for (Leaf &leaf : leaves) {
		leaf.update(elapsed);
	}

	sprite.setPosition(getPosition() - state->cameraPosition);
}

void Tree::onHalfSecond() {
	if (range > 0 && attackCooldown <= 0) {
		target = state->getClosestSpirit(getPosition());
		if (target) {
			float distance = std::sqrt(std::pow(target->getPosition().x - getPosition().x, 2) + std::pow(target->getPosition().y - getPosition().y, 2));
			if (distance <= range * 10) {
				if (state->spendWater(1, getPosition())) {
					target->kill();
					attackCooldown = 1 / attackRate;
					if (!leaves.empty()) {
						attackOrigin = leaves[std::rand() % leaves.size()].getPosition();
					}
					else {
						attackOrigin = getPosition();
					}
				}
			}
		}
	}
}

void Tree::onHour(int hour) {
	std::shared_ptr<GridTile> tileBelow = state->getGridTile(gridPosition.x, gridPosition.y);
	if (tileBelow) {
		if (tileBelow->getType() == "Water" && tileBelow->quantity > 0) {
			if (state->water <= state->maxWater - 1) {
				state->gainWater(getType() == "Waterlily" ? 4 : 1, getPosition());
				tileBelow->quantity -= 1;
			}
		}
		else if (tileBelow->getType() == "Nutrients" && tileBelow->quantity > 0) {
			if (state->nutrients <= state->maxNutrients - 1) {
				state->gainNutrients(1, getPosition());
				tileBelow->quantity -= 1;
			}
		}
	}

	if (getType() == "Soybean") {
		state->gainNutrients(1, getPosition());
	}

	if (getType() != "Glowshroom") {
		if (state->getTimeOfDay(hour) == "Day") {
			state->gainLight(lightIncome, getPosition());
		}
		else if (state->getTimeOfDay(hour) == "Transition") {
			state->gainLight(lightIncome / 2, getPosition());
		}
	}
	else {
		if (state->getTimeOfDay(hour) == "Night") {
			state->gainLight(3, getPosition());
		}
	}

	
}

void Tree::onDay() {

}

void Tree::kill() {
	GridObject::kill();
	state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(0, -6), sf::Color(51, 30, 16));
	state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(1, -5), sf::Color(51, 30, 16));
	state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(-1, -5), sf::Color(51, 30, 16));
}

void Tree::setType(std::string type) {
	this->type = type;
	if (type == "Root") {
		sprite.setTexture(state->loadTexture("Resource/Image/Tiles.png"));
		sprite.setTextureRect(sf::IntRect(std::rand() % 6 * 10, 10, 10, 10));
		sprite.setOrigin(5, 5);
	}
	else if (type == "Sapling") {
		buildTreeFromImage("Sapling");
		maxLight = 2;
		maxWater = 1;
		maxNutrients = 2;
		lightIncome = 1;
		range = 3;
		attackRate = 0.25;
	}
	else if (type == "Shrub") {
		buildTreeFromImage("Shrub");
		maxLight = 5;
		maxWater = 0;
		maxNutrients = 0;
		lightIncome = 0;
		range = 0;
		attackRate = 0;
	}
	else if (type == "Weeds") {
		buildTreeFromImage("Weeds");
		maxLight = 0;
		maxWater = 0;
		maxNutrients = 2;
		lightIncome = 0;
		range = 0;
		attackRate = 0;
	}
	else if (type == "Tree") {
		buildTreeFromImage("Tree");
		maxLight = 6;
		maxWater = 3;
		maxNutrients = 4;
		lightIncome = 2;
		range = 4;
		attackRate = 0.25;
	}
	else if (type == "Willow") {
		buildTreeFromImage("Willow");
		maxLight = 5;
		maxWater = 4;
		maxNutrients = 3;
		lightIncome = 1;
		range = 5;
		attackRate = 0.5;
	}
	else if (type == "Cactus") {
		buildTreeFromImage("Cactus");
		maxLight = 0;
		maxWater = 8;
		maxNutrients = 0;
		lightIncome = 0;
		range = 6;
		attackRate = 1;
	}
	else if (type == "Soybean") {
		buildTreeFromImage("Soybean");
		maxLight = 0;
		maxWater = 0;
		maxNutrients = 2;
		lightIncome = 0;
		range = 4;
		attackRate = 0.25;
	}
	else if (type == "Waterlily") {
		buildTreeFromImage("Waterlily");
		maxLight = 1;
		maxWater = 4;
		maxNutrients = 1;
		lightIncome = 1;
		range = 0;
		attackRate = 0;
	}
	else if (type == "Glowshroom") {
		buildTreeFromImage("Glowshroom");
		maxLight = 0;
		maxWater = 0;
		maxNutrients = 5;
		lightIncome = 3;
		range = 4;
		attackRate = 0.25;
	}
	else if (type == "Mother Tree") {
		buildTreeFromImage("MotherTree");
		maxLight = 15;
		maxWater = 10;
		maxNutrients = 20;
		lightIncome = 3;
		range = 5;
		attackRate = 0.5;
	}
	else if (type == "Grand Mother") {
		buildTreeFromImage("GrandMother");
		maxLight = 50;
		maxWater = 50;
		maxNutrients = 50;
		lightIncome = 4;
		range = 7;
		attackRate = 1;
	}
}

std::string Tree::getType() {
	return type;
}

void Tree::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite);
	for (const Leaf &leaf : leaves) {
		target.draw(leaf);
	}
	if (this->target && attackCooldown > 1 / attackRate / 2.0f) {
		sf::Color attackColor = color;
		attackColor.a = 255 * (attackCooldown - (1 / attackRate / 2.0f)) / (1 / attackRate / 2.0f);
		sf::Vertex tether[] = {
			sf::Vertex(attackOrigin - state->cameraPosition, attackColor),
			sf::Vertex(this->target->getPosition() - state->cameraPosition, attackColor)
		};
		target.draw(tether, 2, sf::Lines);
	}
}

void Tree::buildTreeFromImage(std::string filename) {
	sprite.setTexture(state->loadTexture("Resource/Image/Tree/" + filename + ".png"));
	sprite.setTextureRect(sf::IntRect(0, 0, sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height - 5);
	generateLeaves(filename);
}

void Tree::generateLeaves(std::string filename) {
	leaves.clear();
	sf::Image leafScanner;
	leafScanner.loadFromFile("Resource/Image/Tree/" + filename + ".png");
	for (int y = 0; y < leafScanner.getSize().y; y++) {
		for (int x = 0; x < leafScanner.getSize().x; x++) {
			if (leafScanner.getPixel(x, y) == sf::Color(0, 0, 255)) {
				createLeafCluster(getPosition().x + x - sprite.getOrigin().x, getPosition().y + y - sprite.getOrigin().y);
			}
			else if (leafScanner.getPixel(x, y) == sf::Color(0, 255, 255)) {
				createLeaf(getPosition().x + x - sprite.getOrigin().x, getPosition().y + y - sprite.getOrigin().y);
			}
		}
	}
}

void Tree::createLeaf(float x, float y) {
	Leaf leaf;
	leaf.setState(state);
	leaf.setPosition(x, y);
	leaf.init();
	leaves.push_back(leaf);
}

void Tree::createLeafCluster(float x, float y) {
	createLeaf(x, y - 8);
	createLeaf(x + 7, y - 4);
	createLeaf(x - 7, y - 4);
	createLeaf(x + 4, y + 4);
	createLeaf(x - 4, y + 4);
	createLeaf(x, y);
}
