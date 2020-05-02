#pragma once

#include "GridObject.h"
#include <SFML/Graphics.hpp>

class Ruin : public GridObject {
public:
	Ruin(std::string type = "Small", std::string subType = "");

	void init() override;
	void update(sf::Time elapsed) override;

	sf::Color getMapColor() override;

	void setType(std::string type, std::string subType);
	std::string getType();
	std::string getSubType();

	bool isCharged();

	int charge = 0;
	int maxCharge = 40;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Internal data
	std::string type;
	std::string subType;

	// Resources
	sf::Sprite sprite;
};

