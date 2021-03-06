#pragma once
#ifndef __Tile__
#define __Tile__

#include <vector>

#include "DisplayObject.h"
#include "TextureManager.h"
#include "Config.h"
#include "Label.h"
#include "Scene.h"

enum TileState {
	OPEN,
	CLOSED,
	START,
	GOAL,
	UNDEFINED,
	UNVISITED,
	IMPASSABLE,
	NUM_OF_TILE_STATES
};

enum TileType {
	FLOOR,
	RIGHT_DOOR,
	LEFT_DOOR,
	TOP_LEFT_OUT,
	TOP_LEFT_IN,
	LEFT_WALL,
	BOTTOM_LEFT_OUT,
	BOTTOM_LEFT_IN,
	BOTTOM_WALL,
	BOTTOM_RIGHT_IN,
	BOTTOM_RIGHT_OUT,
	RIGHT_WALL,
	TOP_RIGHT_IN,
	TOP_RIGHT_OUT,
	TOP_WALL,
	NUM_OF_TILE_TYPES
};

enum TileNeighbour
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NUM_OF_NEIGHBOURS
};

class Tile : public DisplayObject
{
public:
	Tile(glm::vec2 position = glm::vec2(), glm::vec2 gridPosition = glm::vec2(), int value = 0);
	~Tile();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

	// get neighbours
	Tile* up();
	Tile* down();
	Tile* right();
	Tile* left();

	// set neighbours
	void setUp(Tile* tile);
	void setDown(Tile* tile);
	void setRight(Tile* tile);
	void setLeft(Tile* tile);

	void setTileState(TileState state);
	TileState getTileState();

	void setTargetDistance(glm::vec2 goalLocation);

	glm::vec2 getGridPosition();

	float getTileValue();

	void setTileStateLabel(std::string closedOpen);

	int val;

private:
	float m_cost = Config::TILE_COST;
	float m_targetDist = 0.0f;
	float m_tileValue = 0.0f;
	TileState m_tileState;
	glm::vec2 m_gridPosition;
	Label* m_pValueLabel;
	Label* m_pClosedOpenLabel;

	glm::vec2 m_goalLocation;

	//Tile* m_pNeighbours[4];

	std::vector<Tile*> m_pNeighbours;
};


#endif /* defined (__Tile__) */