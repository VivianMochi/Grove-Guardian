#pragma once

#include "GridObject.h"
#include "Leaf.h"
#include "Spirit.h"
#include <SFML/Graphics.hpp>

class Tree : public GridObject {
public:
	Tree(std::string type = "Root");

	void init() override;
	void update(sf::Time elapsed) override;

	void onHalfSecond() override;
	void onHour(int hour) override;
	void onDay() override;

	void setType(std::string type);
	std::string getType();

	// Stats
	int maxLight = 0;
	int maxWater = 0;
	int maxNutrients = 0;
	float range = 0;
	float attackRate = 0;
	sf::Color color;

	int distanceToMother = 0;
	float health;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void generateLeaves();
	void createLeaf(float x, float y);
	void createLeafCluster(float x, float y);

	// Internal data
	std::string type = "Root";
	std::vector<Leaf> leaves;
	std::shared_ptr<Spirit> target;
	sf::Vector2f attackOrigin;
	float attackCooldown;

	// Resources
	sf::Sprite sprite;
};

