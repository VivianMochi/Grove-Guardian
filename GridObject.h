#pragma once

#include "Object.h"

class GridObject : public Object {
public:
	GridObject();
	virtual ~GridObject();

	virtual void onHalfSecond();
	virtual void onHour(int hour);
	virtual void onDay();

	sf::Vector2i gridPosition;
	bool playerOwned = false;
};

