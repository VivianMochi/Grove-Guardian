#pragma once

#include "State.h"
#include "BitmapText.h"

class PlayState : public State {
public:
	PlayState();
	~PlayState();

	virtual void init();
	virtual void gotEvent(sf::Event event);
	virtual void update(sf::Time elapsed);
	virtual void render(sf::RenderWindow &window);

private:
	BitmapText testText;
};

