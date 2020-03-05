#pragma once
#ifndef __Planet__
#define __Planet__


#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"
#include "PFDispObj.h"


class Planet : public PFDispObj
{
public:
	Planet();
	~Planet();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

};


#endif /* defined (__Planet__) */