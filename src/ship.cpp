#include "ship.h"
#include "Game.h"
#include "Util.h"
#include "PlayScene.h"
#include "glm/gtx/string_cast.hpp"


Ship::Ship() :
	m_maxSpeed(5.0f), m_currentDirection(0.0f), m_turnRate(2.0f), m_steerForce(0.1f)
{
	TheTextureManager::Instance()->load("../Assets/textures/ship3.png",
		"ship", TheGame::Instance()->getRenderer());

	auto size = TheTextureManager::Instance()->getTextureSize("ship");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(400.0f, 300.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(SHIP);
	setState(SEEK);
	m_currentHeading = 0.0;
}


Ship::~Ship()
= default;

void Ship::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("ship", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), m_currentHeading, 255, true);
}

void Ship::m_checkState()
{
	switch (getState())
	{
	case IDLE:
		//move();
		break;
	case SEEK:
		m_seek();
		move();
		break;
	case ARRIVE:
		break;
	case AVOID:
		break;
	case FLEE:
		break;
	default:
		std::cout << "unknown or unused case" << std::endl;
		break;
	}
}

void Ship::update()
{
	m_checkState();
}

void Ship::clean()
{
}

float Ship::getMaxSpeed()
{
	return m_maxSpeed;
}

void Ship::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}

void Ship::move()
{
	if (Util::distance(getPosition(), getTargetPosition()) > 1.0f) {
		setVelocity(getVelocity() + getAcceleration());
		setVelocity(Util::limitMagnitude(getVelocity(), getMaxSpeed()));
		setPosition(getPosition() + getVelocity());
		setAcceleration(glm::vec2(0.0f, 0.0f));
		m_currentHeading = Util::signedAngle(m_currentDirection, getVelocity());
	}
}

glm::vec2 Ship::getTargetPosition()
{
	return m_targetPosition;
}

void Ship::setTargetPosition()
{
	m_targetPosition = m_findNextPathSpot();;
}

Tile* Ship::getTile()
{
	return m_currentTile;
}

void Ship::setTile(Tile* newTile)
{
	m_currentTile = newTile;
}

Tile* Ship::getNextTile()
{
	return m_nextTile;
}

void Ship::setNextTile(Tile* newTile)
{
	m_nextTile = newTile;
}

void Ship::m_checkBounds()
{

	if (getPosition().x > Config::SCREEN_WIDTH)
	{
		setPosition(glm::vec2(0.0f, getPosition().y));
	}

	if (getPosition().x < 0)
	{
		setPosition(glm::vec2(800.0f, getPosition().y));
	}

	if (getPosition().y > Config::SCREEN_HEIGHT)
	{
		setPosition(glm::vec2(getPosition().x, 0.0f));
	}

	if (getPosition().y < 0)
	{
		setPosition(glm::vec2(getPosition().x, 600.0f));
	}

}

void Ship::applyForce(glm::vec2 force) {
	setAcceleration(getAcceleration() + force);
}

void Ship::m_computeTargetDirection()
{
	glm::vec2 steeringVelocity = getTargetPosition() - getPosition();
	m_targetDirection = Util::normalize(steeringVelocity);
}

void Ship::m_reset()
{
	setIsColliding(false);
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	setPosition(glm::vec2(xComponent, yComponent));
}

void Ship::m_seek()
{
	setTargetPosition();
	m_computeTargetDirection();
	m_targetDirection *= m_maxSpeed;
	glm::vec2 steer = m_targetDirection - getVelocity();
	steer = Util::limitMagnitude(steer, m_turnRate);
	applyForce(steer);
}

glm::vec2 Ship::m_findNextPathSpot()
{
	setNextTile(nullptr);
	int tile_num = 0;

	std::vector<Tile*> adjacent = getTile()->getNeighbours();

	for (int i = 0; i < 4; ++i)
	{
		if (adjacent[i] != nullptr)
		{
			if (adjacent[i]->getTileState() == OPEN || adjacent[i]->getTileState() == GOAL)
			{
				setNextTile(adjacent[i]);
				return getNextTile()->getPosition();
			}
		}
	}
}
