#pragma once

#include "GridObject.h"
#include "Leaf.h"
#include <SFML/Graphics.hpp>

class Tree : public GridObject {
public:
	Tree();
	~Tree();

	void init() override;
	void update(sf::Time elapsed) override;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void createLeafCluster(float x, float y);

	// Internal data
	std::vector<Leaf> leaves;

	// Resources
	sf::Sprite trunk;
};

