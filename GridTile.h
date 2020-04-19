#pragma once

#include "Object.h"

class GridTile : public Object {
public:
	void init() override;
	void update(sf::Time elapsed) override;

	void setType(std::string type);

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Resources
	std::string type = "Grass";
	sf::Sprite sprite;
};

