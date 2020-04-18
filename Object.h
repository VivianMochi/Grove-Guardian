#pragma once

#include <SFML/Graphics.hpp>

class PlayState;

class Object : public sf::Drawable, public sf::Transformable {
public:
	Object();
	virtual ~Object();

	virtual void setState(PlayState *state);
	virtual void init();
	virtual void update(sf::Time elapsed);

protected:
	PlayState *state;
};

