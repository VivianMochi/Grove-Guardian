#pragma once

#include "GridTile.h"
#include <SFML/Graphics.hpp>

class Grass : public GridTile {
public:
	void init() override;
	void update(sf::Time elapsed) override;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Resources
	sf::Sprite sprite;
};
