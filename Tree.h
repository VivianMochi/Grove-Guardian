#pragma once

#include "GridObject.h"
#include "Leaf.h"
#include "Spirit.h"
#include "TreeInfo.h"
#include <SFML/Graphics.hpp>

class Tree : public GridObject {
public:
	Tree(std::string type = "Root");

	void init() override;
	void update(sf::Time elapsed) override;

	void onTick() override;
	void onHour(int hour) override;
	void onDay() override;

	void kill() override;

	sf::Color getMapColor() override;

	void setType(std::string type);
	std::string getType();

	// Stats
	TreeStats stats;
	sf::Color color;

	int distanceToMother = 0;
	float health;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void buildTreeFromImage(std::string filename);
	void generateLeaves(std::string filename);
	void createLeaf(float x, float y);
	void createLeafCluster(float x, float y);

	void updateAnimation(sf::Time elapsed);

	// Internal data
	std::string type = "Root";
	std::vector<Leaf> leaves;
	std::shared_ptr<Spirit> target;
	sf::Vector2f attackOrigin;
	float attackCooldown = 0;
	int totalFrames = 1;
	int frame = 0;
	float frameTime = 0;
	float framePeriod;

	// Resources
	sf::Sprite sprite;
};

