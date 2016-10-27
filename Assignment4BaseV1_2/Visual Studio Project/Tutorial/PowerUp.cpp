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

}


PowerUp::~PowerUp(void)
{
}
