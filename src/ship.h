#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "PathFindingDisplayObject.h"
#include "TextureManager.h"

class Ship final : public PathFindingDisplayObject
{
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	/*void turnRight();
	void turnLeft();*/
	void move();

	Tile* getTile();
	void setTile(Tile* newTile);
	Tile* getNextTile();
	void setNextTile(Tile* newTile);

	glm::vec2 getTargetPosition();
	void setTargetPosition();

	float getMaxSpeed();
	void setMaxSpeed(float newSpeed);

private:


	void m_checkState();
	void m_checkBounds();
	void applyForce(glm::vec2 force);
	void m_computeTargetDirection();

	void m_reset();

	// steering behaviours
	void m_seek();
	glm::vec2 m_findNextPathSpot();
	float m_maxSpeed;
	float m_turnRate;
	float m_steerForce;
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;
	glm::vec2 m_targetDirection;
	
	Tile* m_nextTile;
	Tile* m_currentTile;
};


#endif /* defined (__SHIP__) */

