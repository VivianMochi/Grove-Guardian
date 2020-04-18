#pragma once

#include "State.h"
#include "BitmapText.h"
#include "Fairy.h"
#include "Tree.h"

class PlayState : public State {
public:
	PlayState();
	~PlayState();

	virtual void init();
	virtual void gotEvent(sf::Event event);
	virtual void update(sf::Time elapsed);
	virtual void render(sf::RenderWindow &window);

	sf::Vector2f cameraPosition;

private:
	BitmapText testText;
	Fairy player;
	Tree tree;
};

