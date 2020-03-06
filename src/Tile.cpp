#include "Tile.h"
#include "Game.h"
#include "Util.h"
#include <iomanip>
#include <sstream>

Tile::Tile(glm::vec2 position, glm::vec2 gridPosition, int value):
	m_gridPosition(gridPosition)
{
	m_val = value;

	switch (value)
	{
	case 0:
		setTileState(UNDEFINED);
		TheTextureManager::Instance()->load("../Assets/textures/Floor.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 1:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/TopLeftIn.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 2:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/TopLeftOut.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 3:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/LeftWall.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 4:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/BotleftIn.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 5:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/BotLeftOut.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 6:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/BotWall.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 7:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/BotRightIn.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 8:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/BotRightOut.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 9:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/RightWall.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 10:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/TopRightIn.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 11:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/TopRightOut.png",
			"thisTile", TheGame::Instance()->getRenderer());
		break;
	case 12:
		setTileState(IMPASSABLE);
		TheTextureManager::Instance()->load("../Assets/textures/TopWall.png",
			"thisTile", TheGame::Instance()->getRenderer());
	case 13:
		setTileState(START);
		TheTextureManager::Instance()->load("../Assets/textures/LeftDoor.png",
			"thisTile", TheGame::Instance()->getRenderer());
	case 14:
		setTileState(GOAL);
		TheTextureManager::Instance()->load("../Assets/textures/RightDoor.png",
			"thisTile", TheGame::Instance()->getRenderer());
	}

	glm::vec2 size = glm::vec2(Config::TILE_SIZE, Config::TILE_SIZE);
	setWidth(Config::TILE_SIZE);
	setHeight(Config::TILE_SIZE);
	setPosition(position);

	std::ostringstream tempLabel;
	tempLabel << std::fixed << std::setprecision(1) <<  m_tileValue;
	std::string labelstring = tempLabel.str();

	SDL_Color black{ 0, 0, 0, 255 };
	glm::vec2 closedOpenLabelPosition = glm::vec2(getPosition().x, getPosition().y - 5);
	m_pClosedOpenLabel = new Label("-", "Consolas", 11, black, closedOpenLabelPosition);

	glm::vec2 valueLabelPosition = glm::vec2(getPosition().x, getPosition().y + 10);
	m_pValueLabel = new Label(labelstring, "Consolas", 12, black, valueLabelPosition, true);
}

Tile::~Tile()
{
	delete m_pValueLabel;
	delete m_pClosedOpenLabel;
	m_pNeighbours.clear();
	m_pNeighbours.resize(0);
	m_pNeighbours.shrink_to_fit();
}

void Tile::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("tile", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);

	m_pClosedOpenLabel->draw();
	m_pValueLabel->draw();
}

void Tile::update()
{
}

void Tile::clean()
{
	
}

Tile * Tile::up()
{
	return m_pNeighbours[TileNeighbour::UP];
}

Tile * Tile::down()
{
	return m_pNeighbours[TileNeighbour::DOWN];
}

Tile * Tile::right()
{
	return m_pNeighbours[TileNeighbour::RIGHT];
}

Tile * Tile::left()
{
	return m_pNeighbours[TileNeighbour::LEFT];
}

void Tile::setUp(Tile * tile)
{
	m_pNeighbours.push_back(tile);
	//m_pNeighbours[TileNeighbour::UP] = tile;
}

void Tile::setDown(Tile * tile)
{
	m_pNeighbours.push_back(tile);
	//m_pNeighbours[TileNeighbour::DOWN] = tile;
}

void Tile::setRight(Tile * tile)
{
	m_pNeighbours.push_back(tile);
	//m_pNeighbours[TileNeighbour::RIGHT] = tile;
}

void Tile::setLeft(Tile * tile)
{
	m_pNeighbours.push_back(tile);
	//m_pNeighbours[TileNeighbour::LEFT] = tile;
}

void Tile::setTileState(TileState state)
{
	m_tileState = state;

	switch (state) {
	case OPEN:
		setTileStateLabel("O");
		break;
	case CLOSED:
		setTileStateLabel("C");
		break;
	case START:
		setTileStateLabel("S");
		break;
	case GOAL:
		setTileStateLabel("G");
		break;
	case UNDEFINED:
		setTileStateLabel("-");
		break;
	}

	if (state == TileState::GOAL)
	{
		m_tileValue = 0;
	}
}

TileState Tile::getTileState()
{
	return m_tileState;
}

void Tile::setTargetDistance(glm::vec2 goalLocation)
{
		m_goalLocation = goalLocation;

		m_tileValue = Util::distance(getPosition(), goalLocation) * 0.1;

		std::ostringstream tempLabel;
		tempLabel << std::fixed << std::setprecision(1) << m_tileValue;
		std::string labelstring = tempLabel.str();
		m_pValueLabel->setText(labelstring);
	
}

glm::vec2 Tile::getGridPosition()
{
	return m_gridPosition;
}

float Tile::getTileValue()
{
	return m_tileValue;
}

void Tile::setTileStateLabel(std::string closedOpen)
{
	m_pClosedOpenLabel->setText(closedOpen);

	SDL_Color blue = { 0, 0, 255, 255 };
	m_pClosedOpenLabel->setColour(blue);
}