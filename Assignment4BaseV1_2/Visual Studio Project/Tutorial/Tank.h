#ifndef TANK_H
#define TANK_H
 
#include "stdafx.h"
#include "Utilities.h"
 
enum TankType
{
		CHALLENGER,
		LEOPARD
};


class Tank 
{
public:
	Tank(std::string name, TankType type, Ogre::Vector3 spawnPosition, Ogre::SceneManager* mSceneMgr);
	~Tank();
	
	//tank movements
	void moveTank(float time);
	void rotateTank(float degree);
	void rotateBarrel(float degree);
	void pitchBarrel(float degree);
	void rotateTurret(float degree);

	//tank updates
	void updateHealthBar(float health);

	//helper function in case any of the nodes needed
	Ogre::SceneNode* getTankHealthNode()  { return healthNode; };
	Ogre::SceneNode* getTankSelectionNode() { return selectionNode; };
	Ogre::SceneNode* getTankBaseNode() { return mTankBodyNode; };
	Ogre::SceneNode* getTankTurretNode() { return mTankTurretNode; };
	Ogre::SceneNode* getTankBarrelNode() { return mTankBarrelNode; };

	//helper functions to get attributes
	std::string getTankName() { return idName; };
	TankType getTankType() { return mType; };

	//helper function for selection
	bool isTankSelected();
	void setBillboardsVisible(bool isVisible);


protected:
	virtual bool SetupTank(void);		//initalize tank

private:
	Ogre::Vector3 tankSpawnPosition;
	Ogre::SceneManager* tankSceneManager;
	// Scene nodes for the different tank parts
	Ogre::SceneNode* mTankBodyNode;
	Ogre::SceneNode* mTankTurretNode;
	Ogre::SceneNode* mTankBarrelNode;

	//Billboards
	void createBillboards();
	//Billboard nodes
	Ogre::SceneNode* healthNode;
	Ogre::SceneNode* selectionNode;

	// For tank movement and rotation
	float mMove;
	float mBodyRotate;
	float mTurretRotate;
	float mBarrelRotate;
	float mBarrelPitch;

	//health 
	float mHealth;

	//Tank attributes
	TankType mType;
	std::string idName;

};
 
 
#endif /* TANK_H */