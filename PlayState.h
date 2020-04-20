#pragma once

#include "State.h"
#include "BitmapText.h"
#include "Fairy.h"
#include "Tree.h"
#include "Hud.h"
#include "GridTile.h"
#include "Spirit.h"
#include <SFML/Audio.hpp>
#include <memory>

struct Particle {
	enum ParticleType {
		dot,
		minus,
		plus
	} type = dot;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Color color;
	float lifetime = 0.7;
	bool onHud = false;
};

class PlayState : public State {
public:
	PlayState();
	~PlayState();

	virtual void init();
	virtual void gotEvent(sf::Event event);
	virtual void update(sf::Time elapsed);
	virtual void render(sf::RenderWindow &window);

	sf::Vector2f cameraPosition;

	std::string getTimeOfDay(int hour);
	sf::Color getResourceColor(std::string resource);

	void calculateMaxResources();
	void gainLight(float gained, sf::Vector2f position = sf::Vector2f());
	bool spendLight(float spent, sf::Vector2f position = sf::Vector2f());
	void gainWater(float gained, sf::Vector2f position = sf::Vector2f());
	bool spendWater(float spent, sf::Vector2f position = sf::Vector2f());
	void gainNutrients(float gained, sf::Vector2f position = sf::Vector2f());
	bool spendNutrients(float spent, sf::Vector2f position = sf::Vector2f());

	std::shared_ptr<GridTile> getGridTile(int x, int y);
	void setGridTile(int x, int y, std::string newType);
	std::shared_ptr<GridObject> getGridObject(int x, int y);
	void setGridObject(int x, int y, std::shared_ptr<GridObject> newObject);
	int getDistanceToMother(int x, int y);
	std::shared_ptr<GridObject> getNearestOwned(sf::Vector2f position);
	bool isOwnedTree(std::shared_ptr<GridObject> object);

	std::shared_ptr<Spirit> getClosestSpirit(sf::Vector2f position);

	void createParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color, Particle::ParticleType type = Particle::ParticleType::dot, bool onHud = false);
	void updateParticles(sf::Time elapsed);

	sf::Vector2i worldLocationToGrid(sf::Vector2f location);
	sf::Vector2f screenLocationToWorld(sf::Vector2f location);
	sf::Vector2f getCursorLocation();
	sf::Vector2i getCursorGridLocation();

	bool isResearched(std::string type);

	// Game Stats
	float secondsPerDay = 10;

	// Game data
	sf::Vector2i worldSize;
	std::vector<std::shared_ptr<GridTile>> tileGrid;
	std::vector<std::shared_ptr<GridObject>> objectGrid;
	std::vector< std::shared_ptr<Spirit>> spirits;

	std::shared_ptr<GridObject> selectedObject;
	sf::CircleShape rangeFinder;
	bool ignoreThisClick = false;

	int day = 1;
	int hour = 2;
	float time;

	float light = 0;
	int maxLight = 0;
	float water = 0;
	int maxWater = 0;
	float nutrients = 0;
	int maxNutrients = 0;

	bool gameOver = false;
	bool gameWon = false;

private:
	void buildWorld(int worldWidth, int worldHeight);
	void createRuin(std::string type, std::string subType);

	void spawnSpirits();

	void updateOverlays();

	// Resources
	BitmapText testText;
	Fairy player;
	Hud hud;
	sf::Sprite cursor;

	std::vector<Particle> particles;

	sf::RectangleShape transitionOverlay;
	sf::RectangleShape nightOverlay;

	sf::Music dayMusic;
	sf::Music nightMusic;
};

