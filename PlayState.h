#pragma once

#include "State.h"
#include "BitmapText.h"
#include "Fairy.h"
#include "Tree.h"
#include "Hud.h"
#include <memory>

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
	sf::Vector2i worldSize;
	std::vector<std::shared_ptr<GridObject>> baseGrid;
	std::vector<std::shared_ptr<GridObject>> objectGrid;

	void buildWorld(int worldWidth, int worldHeight);
	std::shared_ptr<GridObject> getGridObject(bool useObjectGrid, int x, int y);
	void setGridObject(bool useObjectGrid, int x, int y, std::shared_ptr<GridObject> newObject);

	BitmapText testText;
	Fairy player;
	Hud hud;
};

