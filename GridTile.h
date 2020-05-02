#pragma once

#include "Object.h"

class GridTile : public Object {
public:
	void init() override;
	void update(sf::Time elapsed) override;

	void setType(std::string type);
	std::string getType();
	sf::Color getMapColor();

	sf::Vector2i gridPosition;
	int quantity = 0;

	bool visible = false;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setShoreTexture();
	bool useExtraSprite = false;

	// Internal data
	std::string type = "Grass";

	// Resources
	sf::Sprite sprite;
	sf::Sprite extraSprite;
};

