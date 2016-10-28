#pragma once
#include "stdafx.h"

class GameObject
{
public:
	virtual void frameRenderingQueued(const Ogre::FrameEvent& evt) {};
	Ogre::SceneNode* node;
	GameObject(void);
	~GameObject(void);
};

