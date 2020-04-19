#include "Tree.h"

#include "PlayState.h"

Tree::Tree(std::string type) : type(type) {

}

void Tree::init() {
	playerOwned = true;
	setType(type);

	color = sf::Color(234, 136, 155);
}

void Tree::update(sf::Time elapsed) {
	attackCooldown -= elapsed.asSeconds() * 1.01;

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
				state->gainWater(1, getPosition());
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

	if (getType() == "Tree") {
		if (state->getTimeOfDay(hour) == "Day") {
			state->gainLight(3, getPosition());
			//state->gainWater(1, getPosition());
			//state->gainNutrients(1, getPosition());
		}
		else if (state->getTimeOfDay(hour) == "Transition") {
			state->gainLight(1, getPosition());
		}
	}
}

void Tree::onDay() {

}

void Tree::setType(std::string type) {
	this->type = type;
	if (type == "Root") {
		sprite.setTexture(state->loadTexture("Resource/Image/Tiles.png"));
		sprite.setTextureRect(sf::IntRect(std::rand() % 6 * 10, 10, 10, 10));
		sprite.setOrigin(5, 5);
	}
	else if (type == "Tree") {
		sprite.setTexture(state->loadTexture("Resource/Image/Trunk.png"));
		sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height - 5);
		generateLeaves();

		maxLight = 15;
		maxWater = 10;
		maxNutrients = 20;
		range = 5;
		attackRate = 0.5;
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

void Tree::generateLeaves() {
	leaves.clear();
	sf::Image leafScanner;
	leafScanner.loadFromFile("Resource/Image/Trunk.png");
	for (int y = 0; y < leafScanner.getSize().y; y++) {
		for (int x = 0; x < leafScanner.getSize().x; x++) {
			if (leafScanner.getPixel(x, y) == sf::Color(0, 0, 255)) {
				createLeafCluster(getPosition().x + x - sprite.getOrigin().x, getPosition().y + y - sprite.getOrigin().y);
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
