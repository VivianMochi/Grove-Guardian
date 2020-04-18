#pragma once

#include "Object.h"
#include <SFML/Graphics.hpp>

class Leaf : public Object {
public:
	Leaf();
	~Leaf();

	void init() override;
	void update(sf::Time elapsed) override;

	void generateFramePeriod();

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Internal data
	int frame;
	float frameTime;
	float framePeriod;

	// Resources
	sf::Sprite sprite;
};

