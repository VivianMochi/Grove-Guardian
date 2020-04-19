#pragma once

#include "State.h"
#include "BitmapText.h"
#include "Fairy.h"
#include "Tree.h"
#include "Hud.h"
#include "GridTile.h"
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

	std::string getTimeOfDay();
	sf::Color getResourceColor(std::string resource);

	// Game Stats
	float secondsPerDay = 10;

	// Game data
	sf::Vector2i worldSize;
	std::vector<std::shared_ptr<GridTile>> tileGrid;
	std::vector<std::shared_ptr<GridObject>> objectGrid;

	int day = 1;
	int hour = 3;
	float time;

	float light = 5;
	int maxLight = 5;
	float water = 3;
	int maxWater = 10;
	float nutrients = 10;
	int maxNutrients = 20;

private:
	void buildWorld(int worldWidth, int worldHeight);

	std::shared_ptr<GridTile> getGridTile(int x, int y);
	void setGridTile(int x, int y, std::string newType);
	std::shared_ptr<GridObject> getGridObject(int x, int y);
	void setGridObject(int x, int y, std::shared_ptr<GridObject> newObject);

	sf::Vector2i worldLocationToGrid(sf::Vector2f location);
	sf::Vector2f screenLocationToWorld(sf::Vector2f location);
	sf::Vector2f getCursorLocation();
	sf::Vector2i getCursorGridLocation();

	// Resources
	BitmapText testText;
	Fairy player;
	Hud hud;
	sf::Sprite cursor;
};

