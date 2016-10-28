#pragma once
#include "stdafx.h"

typedef enum PowerUpType {
	PowerUpTypeHealth,
	PowerUpTypeSpeed,
	PowerUpTypeFirePower,
	PowerUpTypeRateOfFire
};


class PowerUp: public GameObject
{
public:
	PowerUpType type;
	PowerUp(Ogre::SceneManager *sceneManager, PowerUpType type,  Ogre::String name);
	~PowerUp(void);
	void frameRenderingQueued(const Ogre::FrameEvent& evt) override;

private:
	Ogre::AnimationState *mRotateAnimationState;
};

