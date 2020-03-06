#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"

// Game Objects
#include "ship.h"
#include "Tile.h"
#include "Heuristic.h"

#include <memory>
#include<vector>
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	// GameObjects
	Ship* m_ship;
	void m_spawnShip();

	SDL_Texture* backGround;

	//Tile/grid members
	std::vector<Tile*> tileGrid;

	void m_buildGrid();
	void computeTileVals();
	void m_resetImpassableTiles();
	void m_resetGrid();
	void m_mapTiles();

	Tile* m_findLowestCostTile(Tile* current_tile);
	void m_findShortestPath(Tile* start_tile);
	std::vector<Tile*> m_openList;
	std::vector<Tile*> m_closedList;
	Heuristic m_heuristic;
	void m_selectHeuristic(Heuristic heuristic);

	glm::vec2 m_mousePosition;

	// ImGui utility functions
	void m_ImGuiKeyMap();
	void m_ImGuiSetStyle();
	void m_updateUI();

	// ImGui menu variables
	bool m_exitApp = false;
	bool m_displayAbout = false;
	bool m_displayUI = true;
	
	void m_resetAll();

	int m_spawnObject(PFDispObj* obj);
	int valArray[Config::ROW_NUM][Config::COL_NUM];
};

#endif /* defined (__PLAY_SCENE__) */