#include "DemoApp.h"
#include <utility>
#include "Tank.h"

//-------------------------------------------------------------------------------------
Tank::Tank(std::string name, TankType type, Ogre::Vector3 spawnPosition, Ogre::SceneManager* mSceneMgr)
{
	idName = name;
	mType = type;
	tankSpawnPosition = spawnPosition;
	tankSceneManager = mSceneMgr;

	mHealth = 1.0;
	mMove = 0;
	
	mTurretRotate = 0;
	mBarrelRotate = 0;
	mBarrelPitch = 0;

	switch (type)
	{
	case CHALLENGER:
		mBodyRotate = 180;
		break;
	case LEOPARD:
		mBodyRotate = 0;
		break;
	default:
		break;
	}

	SetupTank();
}
//-------------------------------------------------------------------------------------
Tank::~Tank(void)
{

}
 
bool Tank::SetupTank(void)
{

	switch (mType)
	{
	case CHALLENGER:
		{
			idName += "Ch";

			std::string bodyName = idName + "Body";

			// Create tank body entity
			Ogre::Entity* tankBody = tankSceneManager->createEntity(bodyName, "chbody.mesh");
			tankBody->setCastShadows(true);
			tankBody->setMaterialName("ch_tank_material");
			tankBody->setQueryFlags(TANK_MASK);

			std::string turretName = idName + "Turret";
			// Create tank turret entity
			Ogre::Entity* tankTurret = tankSceneManager->createEntity(turretName, "chturret.mesh");
			tankTurret->setCastShadows(true);
			tankTurret->setMaterialName("ch_tank_material");
			tankTurret->setQueryFlags(TANK_MASK);

			std::string barrelName = idName + "Barrel";
			// Create tank barrel entity
			Ogre::Entity* tankBarrel = tankSceneManager->createEntity(barrelName, "chbarrel.mesh");
			tankBarrel->setCastShadows(true);
			tankBarrel->setMaterialName("ch_tank_material");
			tankBarrel->setQueryFlags(TANK_MASK);

			// Create a child scene node and attach tank body to it
			mTankBodyNode = tankSceneManager->getRootSceneNode()->createChildSceneNode();
			mTankBodyNode->attachObject(tankBody);
			// Move it above the ground
			mTankBodyNode->translate(tankSpawnPosition);
			mTankBodyNode->scale(0.05, 0.05, 0.05);
			//rotate
			mTankBodyNode->yaw(Ogre::Degree(mBodyRotate));

			// Create a child scene node from tank body's scene node and attach the tank turret to it
			mTankTurretNode = mTankBodyNode->createChildSceneNode();
			mTankTurretNode->attachObject(tankTurret);
			// Move it above tank body
			mTankTurretNode->translate(0, 3, 0);

			// Create a child scene node from tank turret's scene node and attach the tank barrel to it
			mTankBarrelNode = mTankTurretNode->createChildSceneNode();
			mTankBarrelNode->attachObject(tankBarrel);
			// Move it to the appropriate position on the turret
			mTankBarrelNode->translate(-30, 10, 0);

			createBillboards();
		}
		break;
	case LEOPARD:
		{
			idName += "Lp";

			std::string bodyName = idName + "Body";
			// Create tank body entity
			Ogre::Entity* tankBody = tankSceneManager->createEntity(bodyName, "lpbody.mesh");
			tankBody->setCastShadows(true);
			tankBody->setMaterialName("lp_tank_material");
			tankBody->setQueryFlags(TANK_MASK);

			std::string turretName = idName + "Turret";
			// Create tank turret entity
			Ogre::Entity* tankTurret = tankSceneManager->createEntity(turretName, "lpturret.mesh");
			tankTurret->setCastShadows(true);
			tankTurret->setMaterialName("lp_tank_material");
			tankTurret->setQueryFlags(TANK_MASK);

			std::string barrelName = idName + "Barrel";
			// Create tank barrel entity
			Ogre::Entity* tankBarrel = tankSceneManager->createEntity(barrelName, "lpbarrel.mesh");
			tankBarrel->setCastShadows(true);
			tankBarrel->setMaterialName("lp_tank_material");
			tankBarrel->setQueryFlags(TANK_MASK);

			// Create a child scene node and attach tank body to it
			mTankBodyNode = tankSceneManager->getRootSceneNode()->createChildSceneNode();
			mTankBodyNode->attachObject(tankBody);
			// Move it above the ground
			mTankBodyNode->translate(tankSpawnPosition);
			mTankBodyNode->scale(0.05, 0.05, 0.05);

			// Create a child scene node from tank body's scene node and attach the tank turret to it
			mTankTurretNode = mTankBodyNode->createChildSceneNode();
			mTankTurretNode->attachObject(tankTurret);
			// Move it above tank body
			mTankTurretNode->translate(0, 3, 0);

			// Create a child scene node from tank turret's scene node and attach the tank barrel to it
			mTankBarrelNode = mTankTurretNode->createChildSceneNode();
			mTankBarrelNode->attachObject(tankBarrel);
			// Move it to the appropriate position on the turret
			mTankBarrelNode->translate(-30, 10, 0);

			createBillboards();
		}
		break;
	default:
		break;
	}


	return true;
};

void Tank::createBillboards()
{

		// Create a BillboardSet to represent a health bar and set its properties
		Ogre::BillboardSet* mHealthBar = tankSceneManager->createBillboardSet();
		mHealthBar->setCastShadows(false);
		mHealthBar->setDefaultDimensions(50, 2.0);
		mHealthBar->setMaterialName("myMaterial/HealthBar");

		// Create a billboard for the health bar BillboardSet
		Ogre::Billboard* mHealthBarBB = mHealthBar->createBillboard(Ogre::Vector3(0, 70, 0));
		// Calculate the health bar adjustments
		float healthBarAdjuster = (1.0 - mHealth)/2;	// This must range from 0.0 to 0.5
		// Set the health bar to the appropriate level
		mHealthBarBB->setTexcoordRect(0.0 + healthBarAdjuster, 0.0, 0.5 + healthBarAdjuster, 1.0);

		// Set it to always draw on top of other objects
		mHealthBar->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

		// Create a BillboardSet for a selection circle and set its properties
		Ogre::BillboardSet* mSelectionCircle = tankSceneManager->createBillboardSet();
		mSelectionCircle->setCastShadows(false);
		mSelectionCircle->setDefaultDimensions(200, 200);
		mSelectionCircle->setMaterialName("myMaterial/SelectionCircle");
		mSelectionCircle->setBillboardType(Ogre::BillboardType::BBT_PERPENDICULAR_COMMON);
		mSelectionCircle->setCommonDirection(Ogre::Vector3(0, 1, 0));
		mSelectionCircle->setCommonUpVector(Ogre::Vector3(0, 0, -1));

		// Create a billboard for the selection circle BillboardSet
		Ogre::Billboard* mSelectionCircleBB = mSelectionCircle->createBillboard(Ogre::Vector3(0, -19, 0));
		mSelectionCircleBB->setTexcoordRect(0.0, 0.0, 1.0, 1.0);

		std::string healthName = idName + "health";
		std::string circleName = idName + "circle";
		//attach billboards to the tank node
		healthNode = mTankTurretNode->createChildSceneNode(healthName);
		healthNode->attachObject(mHealthBar);
		healthNode->setVisible(false);
		selectionNode = mTankTurretNode->createChildSceneNode(circleName);
		selectionNode->attachObject(mSelectionCircle);
		selectionNode->setVisible(false);


}

void Tank::moveTank(float time) {

	mMove = time;
	// Move the tank
	mTankBodyNode->translate(mMove, 0, 0, Ogre::Node::TransformSpace::TS_LOCAL);

}

void Tank::rotateTank(float degree) {

	mBodyRotate = degree;
	// Rotate the tank
	mTankBodyNode->yaw(Ogre::Degree(mBodyRotate));

}

void Tank::rotateBarrel(float degree) {

	mBarrelRotate = degree;
	// Clamp tank barrel rotation between 0 and 30 degrees
	if(mBarrelPitch > 30)
		mBarrelPitch = 30;
	else if(mBarrelPitch < 0)
		mBarrelPitch = 0;
	else
		mTankBarrelNode->roll(Ogre::Degree(-mBarrelRotate));
}

void Tank::pitchBarrel(float degree) {

	mBarrelPitch = degree;
	// Calculate the tank barrel's current pitch
	mBarrelPitch += mBarrelRotate;

}

void Tank::rotateTurret(float degree) {

	mTurretRotate = degree;
	// Rotate the tank turret
	mTankTurretNode->yaw(Ogre::Degree(mTurretRotate));

}


bool Tank::isTankSelected() {

	if(selectionNode->getAttachedObject(0)->isVisible())
		return true;
	
	return false;

}

void Tank::setBillboardsVisible(bool isVisible)
{
	if(isVisible)
	{
		selectionNode->setVisible(true);
		healthNode->setVisible(true);
	}
	else
	{
		selectionNode->setVisible(false);
		healthNode->setVisible(false);
	}
}

void Tank::updateHealthBar(float health)
{
	mHealth = health;

	// Calculate the health bar adjustments
	float healthBarAdjuster = (1.0 - mHealth)/2;	// This must range from 0.0 to 0.5

	Ogre::BillboardSet * healthBar = static_cast<Ogre::BillboardSet*>(healthNode->getAttachedObject(0));
	Ogre::Billboard * healthBarBB = healthBar->getBillboard(0);
	// Set the health bar to the appropriate level
	healthBarBB->setTexcoordRect(0.0 + healthBarAdjuster, 0.0, 0.5 + healthBarAdjuster, 1.0);


}


