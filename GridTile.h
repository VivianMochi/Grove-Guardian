#pragma once

#include "Object.h"

class GridTile : public Object {
public:
	void init() override;
	void update(sf::Time elapsed) override;

	void setType(std::string type);
	std::string getType();

	sf::Vector2i gridPosition;
	int quantity = 0;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Internal data
	std::string type = "Grass";

	// Resources
	sf::Sprite sprite;
};

