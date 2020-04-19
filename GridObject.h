#pragma once

#include "Object.h"

class GridObject : public Object {
public:
	GridObject();
	virtual ~GridObject();

	bool playerOwned = false;
	int maxLight = 0;
	int maxWater = 0;
	int maxNutrients = 0;

	virtual void onHour(int hour);
	virtual void onDay();
};

