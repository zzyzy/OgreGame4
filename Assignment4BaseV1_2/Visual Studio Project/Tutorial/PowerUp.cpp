#include "PowerUp.h"


PowerUp::PowerUp(Ogre::SceneManager *sceneManager, PowerUpType type, Ogre::String name)
{
	this->type = type;

	Ogre::String powerUpMaterialName;
	Ogre::String powerUpMeshName = "PowerUp.mesh";

	// Attach appropiate entity
	switch (type) {
	case PowerUpTypeHealth:
		powerUpMaterialName = "HealthPowerUp";
		break;
	case PowerUpTypeFirePower:
		powerUpMaterialName = "FirePowerUp";
		break;
	case PowerUpTypeRateOfFire:
		powerUpMaterialName = "RatePowerUp";
		break;
	case PowerUpTypeSpeed:
		powerUpMaterialName = "SpeedPowerUp";
		break;
	}

	Ogre::Entity *powerUpEntity = sceneManager->createEntity(name, "PowerUp.mesh");
	node = sceneManager->getRootSceneNode()->createChildSceneNode();
	powerUpEntity->setCastShadows(true);
	node->attachObject(powerUpEntity);
	powerUpEntity->setMaterialName(powerUpMaterialName);

	// Create Rotate Animation
	Ogre::Real duration = 1.0;

	Ogre::Animation *rotateAnimation = sceneManager->createAnimation("PowerUpRotateAnimation" + name, duration);
	rotateAnimation->setInterpolationMode(Ogre::Animation::InterpolationMode::IM_LINEAR);
	Ogre::NodeAnimationTrack *track = rotateAnimation->createNodeTrack(0, node);

	Ogre::TransformKeyFrame *key = track->createNodeKeyFrame(0.0);
	key->setRotation(Ogre::Quaternion(1, 0, 1, 0));
	
	key = track->createNodeKeyFrame(1.0);
	key->setRotation(Ogre::Quaternion(0, 0, 1, 0));

	// Create Animation State
	mRotateAnimationState = sceneManager->createAnimationState("PowerUpRotateAnimation" + name);
	mRotateAnimationState->setEnabled(true);
	mRotateAnimationState->setLoop(true);

}


PowerUp::~PowerUp(void)
{
}

void PowerUp::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	
	mRotateAnimationState->addTime(evt.timeSinceLastFrame);

}