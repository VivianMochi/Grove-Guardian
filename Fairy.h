#pragma once

#include "Object.h"
#include <SFML/Graphics.hpp>

class Fairy : public Object {
public:
	void init() override;
	void update(sf::Time elapsed) override;

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void updateVelocity(sf::Time elapsed);
	void updateAnimation(sf::Time elapsed);

	// Internal data
	sf::Vector2f velocity;
	int frame;
	float frameTime;

	// Stats
	float acceleration = 100;
	float topSpeed = 40;

	// Resources
	sf::Sprite bodySprite;
	sf::Sprite dressSprite;
};

