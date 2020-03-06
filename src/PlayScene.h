#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"

// Game Objects
#include "ship.h"
#include "Tile.h"
#include "Planet.h"

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

	Planet* m_pPlanet;
	void m_spawnPlanet();

	SDL_Texture* backGround;

	//Tile/grid members
	std::vector<Tile*> tileGrid;

	void generateMaze();

	void generateFirstPath();

	void generateMaze();

	void findNext();
	int thisX, thisY, nextX, nextY;

	void m_buildGrid();

	void computeTileVals();


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

	int valArray[Config::COL_NUM][Config::ROW_NUM];
	const int xSize = Config::COL_NUM;
	const int ySize = Config::ROW_NUM;
	int pathLength = 0;

	void generateSmallPaths();
};

#endif /* defined (__PLAY_SCENE__) */