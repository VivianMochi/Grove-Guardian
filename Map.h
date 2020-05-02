#pragma once

#include "Object.h"

class Map : public Object {
public:
	void init() override;
	void update(sf::Time elapsed) override;

	bool isCursorOnButton();
	bool isCursorOnMap();

	void toggleMap();
	void setMapOpen(bool open);
	bool isMapOpen();

	void renderMap(sf::RenderTarget &target) const;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	float blinkTime = 0;

	sf::Sprite tab;
	sf::Sprite map;
	bool open;
};

