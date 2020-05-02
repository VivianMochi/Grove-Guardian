#pragma once

#include "Object.h"

class GridObject : public Object {
public:
	GridObject();
	virtual ~GridObject();

	virtual void onHalfSecond();
	virtual void onHour(int hour);
	virtual void onDay();

	virtual void kill();

	virtual sf::Color getMapColor();

	sf::Vector2i gridPosition;
	bool playerOwned = false;

	bool dead = false;
};

