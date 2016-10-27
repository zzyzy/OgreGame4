#pragma once
#include "stdafx.h"

typedef enum PowerUpType {
	PowerUpTypeHealth,
	PowerUpTypeSpeed,
	PowerUpTypeFirePower,
	PowerUpTypeRateOfFire
};


class PowerUp
{
public:
	PowerUpType type;
	Ogre::SceneNode *node;
	PowerUp(Ogre::SceneManager *sceneManager, PowerUpType type,  Ogre::String name);
	~PowerUp(void);
};

