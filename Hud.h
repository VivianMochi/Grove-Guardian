#pragma once

#include "Object.h"
#include "BitmapText.h"
#include <SFML/Graphics.hpp>

class Hud : public Object {
public:
	void init() override;
	void update(sf::Time elapsed) override;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Resources
	sf::Sprite dayBarSprite;
	sf::RectangleShape dayBar;
	sf::Sprite dayBarBg;
	sf::Sprite sunSprite;
};

