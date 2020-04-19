#include "GridObject.h"

#include "PlayState.h"

GridObject::GridObject() {

}

GridObject::~GridObject() {

}

void GridObject::onHour(int hour) {
	if (playerOwned) {
		std::shared_ptr<GridTile> tileBelow = state->getGridTile(gridPosition.x, gridPosition.y);
		if (tileBelow) {
			if (tileBelow->getType() == "Water" && tileBelow->quantity > 0) {
				if (state->water <= state->maxWater - 1) {
					state->gainWater(1, getPosition());
					tileBelow->quantity -= 1;
				}
			}
			else if (tileBelow->getType() == "Nutrients" && tileBelow->quantity > 0) {
				if (state->nutrients <= state->maxNutrients - 1) {
					state->gainNutrients(1, getPosition());
					tileBelow->quantity -= 1;
				}
			}
		}
	}
}

void GridObject::onDay() {

}
