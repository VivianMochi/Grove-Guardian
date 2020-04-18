#pragma once

#include "SFML/Graphics.hpp"

class PlayState;

class Fairy : public sf::Drawable, public sf::Transformable {
public:
	Fairy();
	~Fairy();

	void setState(PlayState *state);
	void init();
	void update(sf::Time elapsed);

private:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void updateVelocity(sf::Time elapsed);
	void updateAnimation(sf::Time elapsed);

	PlayState *state;

	sf::Vector2f velocity;
	int frame;
	float frameTime;

	// Stats
	float acceleration = 100;
	float topSpeed = 40;

	sf::Sprite bodySprite;
	sf::Sprite dressSprite;
};

