#include "Tree.h"

#include "PlayState.h"
#include "TreeInfo.h"
#include <algorithm>
#include <cctype>

#include <iostream>

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

	framePeriod = std::rand() % 20 * .01 + 0.4;
}

void Tree::update(sf::Time elapsed) {
	attackCooldown -= elapsed.asSeconds() * 1.05;

	if (getType().find("Mother") == -1) {
		if (distanceToMother < state->getDistanceToMother(gridPosition.x, gridPosition.y)) {
			distanceToMother += 1;
			health -= elapsed.asSeconds();
			if (health <= 0) {
				buffs.clear();
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
				stats.range = 10;
			}
			else {
				stats.range = 5;
			}
		}
	}
	else if (type == "Bamboo") {
		stats.range = state->light / 10;
	}

	for (Leaf &leaf : leaves) {
		leaf.update(elapsed);
	}

	updateAnimation(elapsed);

	if (stats.buff && std::rand() % 4 == 0) {
		if (type != "Megashroom" || state->getTimeOfDay(state->hour) == "Night") {
			float angle = std::rand() % 360 / 2.0f / 3.14159f;
			float dist = std::rand() % (int)(stats.range * 10);
			sf::Color color(229, 190, 167);
			if (type == "Aloe") {
				color = state->getResourceColor("Light");
			}
			state->createParticle(getPosition() + sf::Vector2f(dist * std::cos(angle), dist * std::sin(angle)), sf::Vector2f(0, -6), color);
		}
	}

	sprite.setPosition(getPosition() - state->cameraPosition);
}

void Tree::onTick() {
	if (stats.range > 0 && stats.attackRate > 0 && attackCooldown <= 0) {
		target = state->getClosestSpirit(getPosition());
		if (target) {
			float distance = std::sqrt(std::pow(target->getPosition().x - getPosition().x, 2) + std::pow(target->getPosition().y - getPosition().y, 2));
			if (distance <= stats.range * 10) {
				if (state->spendWater(1, getPosition())) {
					target->kill();
					attackCooldown = 1 / stats.attackRate;
					if (!leaves.empty()) {
						attackOrigin = leaves[std::rand() % leaves.size()].getPosition();
					}
					else {
						attackOrigin = getPosition();
					}
					if (target->dead) {
						if (type == "Pitcher Plant") {
							state->gainNutrients(10, getPosition());
						}
					}
				}
			}
		}
	}
	if (stats.buff) {
		if (type != "Megashroom" || state->getTimeOfDay(state->hour) == "Night") {
			state->emitBuff(type, getPosition(), stats.range);
		}
	}

	// Propagate Creeping Ivy
	if (type == "Creeping Ivy" && state->getTimeOfDay(state->hour) != "Night") {
		if (std::rand() % 50 == 0) {
			int direction = std::rand() % 4;
			sf::Vector2i newPosition = gridPosition;
			bool poison = state->isResearched("Poison Ivy") && std::rand() % 20 == 0;
			if (direction == 0) {
				newPosition.x -= 1;
			}
			else if (direction == 1) {
				newPosition.x += 1;
			}
			else if (direction == 2) {
				newPosition.y -= 1;
			}
			else if (direction == 3) {
				newPosition.y += 1;
			}
			if (state->getGridTile(newPosition.x, newPosition.y)->getType() != "Ocean" && state->getGridTile(newPosition.x, newPosition.y)->getType() != "Shore" && !state->getGridObject(newPosition.x, newPosition.y)) {
				state->setGridObject(newPosition.x, newPosition.y, std::make_shared<Tree>(poison ? "Poison Ivy" : "Creeping Ivy"));
				state->revealMap(newPosition, 8);
			}
		}
	}
}

void Tree::onHour(int hour) {
	std::shared_ptr<GridTile> tileBelow = state->getGridTile(gridPosition.x, gridPosition.y);
	if (tileBelow) {
		if (tileBelow->getType() == "Water" && tileBelow->quantity > 0 && state->getTimeOfDay(hour) != "Night") {
			if (state->water <= state->maxWater - 1 || state->weather == state->rainy) {
				state->gainWater(stats.waterMultiplier, getPosition());
				tileBelow->quantity -= 1;
			}
		}
		else if (tileBelow->getType() == "Nutrients" && tileBelow->quantity > 0) {
			if (state->nutrients <= state->maxNutrients - 1) {
				state->gainNutrients(stats.nutrientsMultiplier, getPosition());
				tileBelow->quantity -= 1;
			}
		}
	}

	if (state->getTimeOfDay(hour) != "Night") {
		state->gainWater(stats.waterIncome, getPosition());
	}
	state->gainNutrients(stats.nutrientsIncome, getPosition());

	if (getType() != "Glowshroom") {
		if (state->weather == state->sunny) {
			if (state->getTimeOfDay(hour) == "Day") {
				state->gainLight(stats.lightIncome, getPosition());
			}
			else if (state->getTimeOfDay(hour) == "Transition") {
				state->gainLight(stats.lightIncome / 2, getPosition());
			}
		}
		else if (state->weather == state->rainy) {
			if (state->getTimeOfDay(hour) != "Night") {
				state->gainLight(stats.lightIncome / 2, getPosition());
			}
		}
	}
	else {
		if (state->getTimeOfDay(hour) == "Night") {
			state->gainLight(stats.lightIncome, getPosition());
		}
	}

	
}

void Tree::onDay() {
	if (type == "Blackberry") {
		state->gainNutrients(state->nutrients * .1, getPosition());
	}
	else if (type == "Moss") {
		int total = state->light + state->water + state->nutrients;
		state->light = total / 3;
		state->water = total / 3;
		state->nutrients = total / 3;
	}
}

void Tree::kill() {
	bool safe = false;
	if (std::find(buffs.begin(), buffs.end(), "Aloe") != buffs.end()) {
		safe = state->spendLight(5);
		if (safe && state->getClosestSpirit(getPosition())) {
			state->getClosestSpirit(getPosition())->kill();
		}
	}
	if (!safe) {
		GridObject::kill();
		state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(0, -6), sf::Color(51, 30, 16));
		state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(1, -5), sf::Color(51, 30, 16));
		state->createParticle(getPosition() + sf::Vector2f(std::rand() % 7 - 3, std::rand() % 7 - 3), sf::Vector2f(-1, -5), sf::Color(51, 30, 16));
	}
}

sf::Color Tree::getMapColor() {
	if (getType().find("Mother") != -1) {
		return sf::Color(234, 136, 155);
	}
	else if (type == "Root" || type == "Seaweed") {
		return sf::Color(122, 91, 72);
	}
	else if (type == "Creeping Ivy") {
		return sf::Color(124, 175, 93);
	}
	else if (type == "Poison Ivy") {
		return sf::Color(173, 93, 150);
	}
	else {
		return sf::Color(27, 56, 9);
	}
}

void Tree::setType(std::string type) {
	this->type = type;
	leaves.clear();
	totalFrames = 1;
	if (type == "Root") {
		stats = getTreeStats(type);
		sprite.setTexture(state->loadTexture("Resource/Image/Tiles.png"));
		sprite.setTextureRect(sf::IntRect(std::rand() % 6 * 10, 20, 10, 10));
		sprite.setOrigin(5, 5);
	}
	else if (type == "Coral") {
		stats = getTreeStats(type);
		sprite.setTexture(state->loadTexture("Resource/Image/Tiles.png"));
		sprite.setTextureRect(sf::IntRect(std::rand() % 5 * 10 + 60, 20, 10, 10));
		sprite.setOrigin(5, 5);
	}
	else {
		stats = getTreeStats(type);
		buildTreeFromImage(type);
	}

	std::shared_ptr<GridTile> tileBelow = state->getGridTile(gridPosition.x, gridPosition.y);
	if (type == "Willow") {
		if (tileBelow) {
			if (tileBelow->getType() == "Water" && tileBelow->quantity > 0) {
				stats.range = 10;
			}
			else {
				stats.range = 5;
			}
		}
	}
	else if (type == "Sweet Birch") {
		if (tileBelow && tileBelow->getType() == "Nutrients") {
			stats.lightIncome = 8;
		}
		else {
			stats.lightIncome = 4;
		}
	}
	else if (type == "Bamboo") {
		stats.range = state->light / 10;
	}
	else if (type == "Cattail") {
		if (tileBelow && tileBelow->getType() == "Shore") {
			stats.waterIncome = 1;
		}
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
	if (this->target && attackCooldown > 0) {
		sf::Color attackColor = color;
		attackColor.a = 255 * (attackCooldown - 1 / stats.attackRate) / (1 / stats.attackRate);
		sf::Vertex tether[] = {
			sf::Vertex(attackOrigin - state->cameraPosition, attackColor),
			sf::Vertex(this->target->getPosition() - state->cameraPosition, attackColor)
		};
		target.draw(tether, 2, sf::Lines);
	}
}

void Tree::buildTreeFromImage(std::string filename) {
	filename.erase(std::remove_if(filename.begin(), filename.end(), std::isspace), filename.end());
	sprite.setTexture(state->loadTexture("Resource/Image/Tree/" + filename + ".png"));
	totalFrames = sprite.getTexture()->getSize().x / sprite.getTexture()->getSize().y;
	sprite.setTextureRect(sf::IntRect(0, 0, sprite.getTexture()->getSize().x / totalFrames, sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height - 5);
	if (totalFrames == 1) {
		generateLeaves(filename);
	}
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
	if (stats.color != sf::Color()) {
		leaf.color = stats.color;
	}
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

void Tree::updateAnimation(sf::Time elapsed) {
	if (totalFrames > 1) {
		frameTime += elapsed.asSeconds();
		if (frameTime > framePeriod) {
			frameTime = 0;
			frame++;
		}
		if (frame > totalFrames - 1) {
			frame = 0;
		}

		sf::Vector2u frameSize = sprite.getTexture()->getSize();
		frameSize.x = frameSize.x / totalFrames;
		sprite.setTextureRect(sf::IntRect(frame * frameSize.x, 0, frameSize.x, frameSize.y));
	}
}
