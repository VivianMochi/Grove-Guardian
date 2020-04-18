#include "Tree.h"

#include "PlayState.h"

void Tree::init() {
	trunk.setTexture(state->loadTexture("Resource/Image/Trunk.png"));
	trunk.setOrigin(20, 35);

	// Create leaves
	createLeafCluster(0, -33);
	createLeafCluster(-11, -23);
	createLeafCluster(11, -23);
	createLeafCluster(0, -20);
}

void Tree::update(sf::Time elapsed) {
	for (Leaf &leaf : leaves) {
		leaf.update(elapsed);
	}

	trunk.setPosition(getPosition() - state->cameraPosition);
}

void Tree::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(trunk);
	for (const Leaf &leaf : leaves) {
		target.draw(leaf);
	}
}

void Tree::createLeafCluster(float x, float y) {
	Leaf leaf;
	leaf.setState(state);
	leaf.setPosition(getPosition() + sf::Vector2f(x, y - 8));
	leaf.init();
	leaves.push_back(leaf);

	leaf.setPosition(getPosition() + sf::Vector2f(x + 7, y - 4));
	leaf.generateFramePeriod();
	leaves.push_back(leaf);

	leaf.setPosition(getPosition() + sf::Vector2f(x - 7, y - 4));
	leaf.generateFramePeriod();
	leaves.push_back(leaf);

	leaf.setPosition(getPosition() + sf::Vector2f(x + 4, y + 4));
	leaf.generateFramePeriod();
	leaves.push_back(leaf);

	leaf.setPosition(getPosition() + sf::Vector2f(x - 4, y + 4));
	leaf.generateFramePeriod();
	leaves.push_back(leaf);

	leaf.setPosition(getPosition() + sf::Vector2f(x, y));
	leaf.generateFramePeriod();
	leaves.push_back(leaf);
}
