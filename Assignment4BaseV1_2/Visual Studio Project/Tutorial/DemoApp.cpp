
/*
-----------------------------------------------------------------------------
CSCI356: Game Engine Essentials - Group Project

Name: Ivana Ozakovic, Jarryd Saffery, Nacho Garrido, Benjamin Johnson, Zhen Zhi
Student No.: 4790339, 4255343, , , 
Email: io447@uow.edu.au, js073@uowmail.edu.au, , , 

Filename:   DemoApp.cpp
			This source file is based on Lab files supplied and has been modified and code was added for requirements of this assignment.
-----------------------------------------------------------------------------
*/

#include "DemoApp.h"
#include <utility>
#include "TankFactory.hpp"
#include "QueryMasks.hpp"
#include "CollisionMasks.hpp"
#include "OgreEuler.hpp"

Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
//-------------------------------------------------------------------------------------
DemoApp::DemoApp():
    mMove(150),
	mTarget(0),
    mCamNode(0),
	isOrbiting(false),
	multipleSelection(false),
    mDirectionCam(Ogre::Vector3::ZERO),
	mDirection(Ogre::Vector3::ZERO),
	mWalkSpeed(10.0f),
	shouldAnimate(false)

{
	objects = new std::vector<GameObject*>();
}
//-------------------------------------------------------------------------------------
DemoApp::~DemoApp(void)
{
	// If the physics system exists, delete it
	if(mPhysicsEngine)
		delete mPhysicsEngine;
}
 
bool DemoApp::setup(void)
{
	// Create and initialise the physics system
	mPhysicsEngine = new PhysicsEngine();
	mPhysicsEngine->initPhysics();

	// Call the base class's setup method
	BaseApplication::setup();

	mTrayMgr->showCursor();

	mCurrentState = 0;

	//set camera
	setCamera();



	return true;
};

//-------------------------------------------------------------------------------------
//camera function to set to inital state 
void DemoApp::setCamera()
{
	mCamera->setPosition(Ogre::Vector3(0, 90, 100));
	mCamera->lookAt(Ogre::Vector3(0, 0, 10));

	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("RTSCamera", Ogre::Vector3(0, 0, 0));
	//node->yaw(Ogre::Degree(90));
	mCamNode = node;
	mCamNode->attachObject(mCamera);

}
//-------------------------------------------------------------------------------------
bool DemoApp::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	return true;
}
//-------------------------------------------------------------------------------------

// Creates Power Up of type in scene
PowerUp* DemoApp::createPowerUp(PowerUpType type, Ogre::String name) {

	PowerUp *powerUp = new PowerUp(mSceneMgr, type, name);
	powerUp->node->setScale(2, 2, 2);
	objects->push_back(powerUp);

	return powerUp;
}

void DemoApp::createPowerUps() {

	// Create Powerup
	PowerUp *firePowerUp = createPowerUp(PowerUpTypeFirePower, "FirePower1");
	firePowerUp->node->setPosition(-5,0,10);

	PowerUp *healthPowerUp = createPowerUp(PowerUpTypeHealth, "HealthPowerUp1");
	healthPowerUp->node->setPosition(-0,0,10);

	PowerUp *speedPowerUp = createPowerUp(PowerUpTypeSpeed, "SpeedPowerUp1");
	speedPowerUp->node->setPosition(5,0,10);

	PowerUp *ratePowerUp = createPowerUp(PowerUpTypeRateOfFire, "RatePowerUp1");
	ratePowerUp->node->setPosition(10,0,10);

}



//-------------------------------------------------------------------------------------
void DemoApp::createScene(void)
{
	/*****************************************************************/
	mSelectionBox = new SelectionBox("SelectionBox");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(mSelectionBox);
 
	 mVolQuery = mSceneMgr->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList());
	/*****************************************************************/


	//set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.6f, 0.6f, 0.6f));
 
    // create the light
    /*Ogre::Light *light = mSceneMgr->createLight("Light1");
    light->setType(Ogre::Light::LT_POINT);
    light->setPosition(Ogre::Vector3(250, 150, 250));
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue::White);*/
 
	// Use a plane to represent the ground
	/*Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
		100, 100, 20, 20, true, 1, 2.5, 2.5, Ogre::Vector3::UNIT_Z);

	entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("sibenik/poplocenje");
	entGround->setCastShadows(false);
	entGround->setQueryFlags(GROUND_MASK);*/


	// MAP AND PATH FINDING A* ALGORITHM SETUP



	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		100, 100, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	int length = 100;

	//create ground entities
	Ogre::Entity* battleGroundEntity;
	Ogre::Entity* topMazeEntity;
	Ogre::Entity* bottomMazeEntity;
	Ogre::Entity* leftMazeEntity;
	Ogre::Entity* rightMazeEntity;
	Ogre::Entity* spawnLeftEntity;
	Ogre::Entity* spawnRightEntity;

	// Create ground entities
	battleGroundEntity = mSceneMgr->createEntity("ground");
	topMazeEntity = mSceneMgr->createEntity("ground");
	bottomMazeEntity = mSceneMgr->createEntity("ground");
	leftMazeEntity = mSceneMgr->createEntity("ground");
	rightMazeEntity = mSceneMgr->createEntity("ground");
	spawnLeftEntity = mSceneMgr->createEntity("ground");
	spawnRightEntity = mSceneMgr->createEntity("ground");

	// Set query mask for ground
	battleGroundEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::GROUND));
	topMazeEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::GROUND));
	bottomMazeEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::GROUND));
	leftMazeEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::GROUND));
	rightMazeEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::GROUND));
	spawnLeftEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::GROUND));
	spawnRightEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::GROUND));

	// Create ground sceneNodes
	Ogre::SceneNode* battleGroundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, -1, 0));
	Ogre::SceneNode* topMazeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, -1, -125));
	Ogre::SceneNode* bottomMazeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, -1, 125));
	Ogre::SceneNode* LeftMazeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-95, -1, 0));
	Ogre::SceneNode* RightMazeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(95, -1, 0));
	Ogre::SceneNode* spawnLeftNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-150, -1, 0));
	Ogre::SceneNode* spawnRightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(150, -1, 0));
    
	//change sizes of the ground entities 
	battleGroundNode->scale(1.3f, 0, 1.5f);
	topMazeNode->scale(2.5f, 0, 1);
	bottomMazeNode->scale(2.5f, 0, 1);
	LeftMazeNode->scale(0.6f, 0, 1.5f);
	RightMazeNode->scale(0.6f, 0, 1.5f);
	spawnLeftNode->scale(0.5f, 0, 3.5f);
	spawnRightNode->scale(0.5f, 0, 3.5f);

	// Attach ground entities
	battleGroundNode->attachObject(battleGroundEntity);
	topMazeNode->attachObject(topMazeEntity);
	bottomMazeNode->attachObject(bottomMazeEntity);
	LeftMazeNode->attachObject(leftMazeEntity);
	RightMazeNode->attachObject(rightMazeEntity);
	spawnLeftNode->attachObject(spawnLeftEntity);
	spawnRightNode->attachObject(spawnRightEntity);

	// Set Materials
	battleGroundEntity->setMaterialName("Examples/GrassFloor");
	topMazeEntity->setMaterialName("Examples/Rockwall");
	bottomMazeEntity->setMaterialName("Examples/Rockwall");
	leftMazeEntity->setMaterialName("Examples/Rockwall");
	rightMazeEntity->setMaterialName("Examples/Rockwall");
	spawnLeftEntity->setMaterialName("Examples/RustySteel");
	spawnRightEntity->setMaterialName("Examples/RustySteel");

	//turn off shadows
	battleGroundEntity->setCastShadows(false);
	topMazeEntity->setCastShadows(false);
	bottomMazeEntity->setCastShadows(false);
	leftMazeEntity->setCastShadows(false);
	rightMazeEntity->setCastShadows(false);
	spawnLeftEntity->setCastShadows(false);
	spawnRightEntity->setCastShadows(false);

    // Add ground rigidbody
    Ogre::SceneNode* collisionPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    collisionPlaneNode->translate(0, -5, 0);
    collisionPlaneNode->setVisible(false);

    btTransform startTrans;
    btCollisionShape* shape = new btBoxShape(btVector3(
        (GRID_DIMENSION * SQUARE_SIZE) / 2.0f,
        5,
        (GRID_DIMENSION * SQUARE_SIZE) / 2.0f));
    startTrans.setIdentity();
    startTrans.setOrigin(convert(collisionPlaneNode->getPosition()));
    mPhysicsEngine->CreateRigidBody(0.0f,
        startTrans,
        shape,
        collisionPlaneNode,
        static_cast<short>(CollisionTypes::GROUND),
        CollisionTypes::OBSTACLES |
        CollisionTypes::POWERUP |
        CollisionTypes::TANK);

	/***************************	SKY 	*********************************/
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	/***************************	OBSTACLES 	*********************************/

	for(int nodeNumber=0; nodeNumber<TOTAL_NODES; nodeNumber++)
	{
		int contents = pathFindingGraph.getContent(nodeNumber);

		if(contents == 1)
		{
			// Create unique name
			std::ostringstream oss;
			oss << nodeNumber;
			std::string entityName = "Cube" + oss.str();

			// Create entity
			Ogre::Entity* cube = mSceneMgr->createEntity(entityName, "cube.mesh");
            cube->setQueryFlags(0);
			cube->setMaterialName("Examples/BumpyMetal");

			// Attach entity to scene node
			Ogre::SceneNode* myNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
			myNode->attachObject(cube);
			myNode->scale(0.1f, 0.1f, 0.1f);
			
			// Place object at appropriate position
			Ogre::Vector3 position = pathFindingGraph.getPosition(nodeNumber);
			position.y = 0.5;
			myNode->translate(position);
		}
	}

	//
	// Create Power Ups
	//
	createPowerUps();

	// create the path objects, and clear them to start off
	/*path1 = mSceneMgr->createManualObject("DijkstraPath");
	path1->clear();
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(path1);*/

	path2 = mSceneMgr->createManualObject("AStarPath");
	path2->clear();
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(path2);


	/************		TANKS		****************/
	//tanks vector declaration located in BaseApplication.h
    TankFactory tankFactory(mSceneMgr, mPhysicsEngine);
	for(int tankId = 0; tankId < TOTAL_NODES; tankId++)
	{
		int contents = pathFindingGraph.getContent(tankId);

		if(contents == 2)
		{
			// Create unique name
			std::ostringstream oss;
			oss << tankId;
			std::string tankName = "Tank" + oss.str();

			// Place object at appropriate position
			Ogre::Vector3 position = pathFindingGraph.getPosition(tankId);
			position.y = 0.5;
			//create tank
            Tank* tank = tankFactory.MakeChallengerTank(position, &pathFindingGraph, &mPathFinder);
			//Tank tank(tankName, Tank::Type::CHALLENGER, position, mSceneMgr);

			tanks.push_back(tank);
		}
		if(contents == 3)
		{
			// Create unique name
			std::ostringstream oss;
			oss << tankId;
			std::string tankName = "Tank" + oss.str();

			// Place object at appropriate position
			Ogre::Vector3 position = pathFindingGraph.getPosition(tankId);
			position.y = 0.5;
			//create tank
            Tank* tank = tankFactory.MakeLeopardTank(position, &pathFindingGraph, &mPathFinder);
			//Tank tank(tankName, Tank::Type::LEOPARD, position, mSceneMgr);

			tanks.push_back(tank);
		}
	}

	//update health bar example
	//tanks[0].updateHealthBar(0.5);
	
	/**********		PATH FINDING	**********/
	// go through the graph
	// if a node is blocked, display a cube on that grid location
	/*for(int nodeNumber=0; nodeNumber<TOTAL_NODES; nodeNumber++)
	{
		int contents = pathFindingGraph->getContent(nodeNumber);

		if(contents)
		{
			// Create unique name
			std::ostringstream oss;
			oss << nodeNumber;
			std::string entityName = "Cube" + oss.str();

			// Create entity
			Ogre::Entity* cube = mSceneMgr->createEntity(entityName, "cube.mesh");
			cube->setMaterialName("Examples/BumpyMetal");

			// Attach entity to scene node
			Ogre::SceneNode* myNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
			myNode->attachObject(cube);
			myNode->scale(0.1, 0.01, 0.1);
			
			// Place object at appropriate position
			Ogre::Vector3 position = pathFindingGraph->getPosition(nodeNumber);
			position.y = 0.5;
			myNode->translate(position);
		}
	}

	// create the path objects, and clear them to start off
	path1 = mSceneMgr->createManualObject("DijkstraPath");
	path1->clear();
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(path1);

	path2 = mSceneMgr->createManualObject("AStarPath");
	path2->clear();
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(path2);
	*/


    // Build world grid
    auto worldGridColour = Ogre::ColourValue(51 / 255.0f, 255 / 255.0f, 247 / 255.0f);
    auto worldGrid = mSceneMgr->createManualObject();
    worldGrid->clear();
    worldGrid->setQueryFlags(0);
    for (auto i = 0; i < TOTAL_NODES; ++i)
    {
        worldGrid->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
        auto position = pathFindingGraph.getPosition(i);
        position.x -= SQUARE_SIZE / 2.0f;
        position.z -= SQUARE_SIZE / 2.0f;
        position.y = 1;
        worldGrid->position(position);
        worldGrid->colour(worldGridColour);
        position.x += SQUARE_SIZE;
        worldGrid->position(position);
        worldGrid->colour(worldGridColour);
        position.z += SQUARE_SIZE;
        worldGrid->position(position);
        worldGrid->colour(worldGridColour);
        position.x -= SQUARE_SIZE;
        worldGrid->position(position);
        worldGrid->colour(worldGridColour);
        worldGrid->end();
    }
    mWorldGridNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    mWorldGridNode->attachObject(worldGrid);
    mWorldGridNode->setVisible(false);
}

bool DemoApp::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	bool ret = BaseApplication::frameRenderingQueued(evt);

	for(std::vector<GameObject*>::iterator it = objects->begin(); it != objects->end(); ++it) {
		GameObject *currentObject = *it;
		currentObject->frameRenderingQueued(evt);
	}
    for (Tank* tank : tanks)
    {
        tank->Update(evt.timeSinceLastFrame);
    }

    mPhysicsEngine->update(evt.timeSinceLastFrame);

	/*****************************************************************/
	/***********************	WALK	******************************/
	/*****************************************************************/
	//*******only moves one object
	/*if(mSelected.size() > 0)
	{


	if (mDirection == Ogre::Vector3::ZERO) 
	{

		if (nextLocation()) 
		{
			shouldAnimate = true;
			// Set walking animation
			mAnimationState = mEntity->getAnimationState("Walk");
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);	

			Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;

				if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) 
				{
					mNode->yaw(Ogre::Degree(180));
				}
				else{	
					Ogre::Quaternion quat = src.getRotationTo(mDirection);
					mNode->rotate(quat);
				} 
		}
	}
	else
	{

		Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
		mDistance -= move;

		if (mDistance <= 0.0f)
		{                 
			mNode->setPosition(mDestination);
			mDirection = Ogre::Vector3::ZERO;	

			// Set animation based on if the robot has another point to walk to. 
			if (!nextLocation())
			{
				// Set Idle animation                     
				mAnimationState = mEntity->getAnimationState("Idle");
				mAnimationState->setLoop(true);
				mAnimationState->setEnabled(true);

			}
			else
			{
				// Rotation Code 
				Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
				if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) 
				{
					mNode->yaw(Ogre::Degree(180));						
				}
				else
				{
					Ogre::Quaternion quat = src.getRotationTo(mDirection);
					mNode->rotate(quat);
				} 
			}

		}
		else
		{
			// Set walking animation
			mAnimationState = mEntity->getAnimationState("Walk");
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);	
			mNode->translate(mDirection * move);
		} 
	} 

	}
	else
		shouldAnimate = false;

	if(shouldAnimate)
	{
		mAnimationState->addTime(evt.timeSinceLastFrame);
	}*/
		

	/*******************************************************************************************/

	//update camera
	mCamNode->translate(mDirectionCam * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	if(!processUnbufferedInput(evt))
		return false;

    if(mWindow->isClosed())
        return false;
 
	if(mShutDown)
		return false;
 
	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	mTrayMgr->frameRenderingQueued(evt);


	return ret;
}
 
// OIS::KeyListener
bool DemoApp::keyPressed( const OIS::KeyEvent &arg )
{
    switch (arg.key)
	{
		case OIS::KC_ESCAPE: 
			mShutDown = true;
			break;
		case OIS::KC_LSHIFT:
			{
				editSelection = true;
			}
			break;
		default:
			break;
	}

	return true;
}

bool DemoApp::keyReleased(const OIS::KeyEvent& ke)
{

	 switch (ke.key)
	{
		case OIS::KC_LSHIFT:
			{
				editSelection = false;
			}
			break;
		default:
			break;
	}
	return true;
}


// OIS::MouseListener
bool DemoApp::mouseMoved( const OIS::MouseEvent &arg )
{
	if (mTrayMgr->injectMouseMove(arg)) return true;

	/**********************************************************************************/
	/*************************		CAMERA CONTROLS		*******************************/
	/**********************************************************************************/
	//CAMERA MOVEMENT X/Y CONTROLS 
	if(arg.state.X.abs > (arg.state.width - 20)) 
	{ 
		mDirectionCam.x = mMove; 
	} 
	else if(arg.state.X.abs < (arg.state.width - (arg.state.width - 20))) 
	{ 
		mDirectionCam.x = -mMove; 
	}
	else if(arg.state.Y.abs > (arg.state.height - 20)) 
	{ 
		mDirectionCam.z = mMove; 
	} 
	else if(arg.state.Y.abs < (arg.state.height - (arg.state.height - 20))) 
	{ 
		mDirectionCam.z = -mMove; 
	}
	else
	{
		mDirectionCam.x = 0;
		mDirectionCam.z = 0;
	}

	//set camera target and distance
	mTarget = mCamera->getSceneManager()->getRootSceneNode();
	Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

	//CAMERA ZOOM - SCROLL CONTROL - based on orbit camera from Ogre's SDKCameraMan.h
	if (arg.state.Z.rel != 0)																// move the camera toward or away from the target
	{
		mCamera->moveRelative(Ogre::Vector3(0, 0, -arg.state.Z.rel * 0.0008f * dist));		// the further the camera is, the faster it moves
	}

	//ORBIT if right mouse button pressed - based on orbit camera from Ogre's SDKCameraMan.h
	if(mMouse->getMouseState().buttonDown(OIS::MouseButtonID::MB_Right) && isOrbiting)
	{
		mTrayMgr->hideCursor();																//hide cursor while rotating

		mCamNode->yaw(Ogre::Degree(-arg.state.X.rel * 0.25f ), Ogre::Node::TS_WORLD);		//set yaw rotation axis - only alow to rotate around yaw
		mCamNode->pitch(Ogre::Degree(-arg.state.Y.rel * 0.0f), Ogre::Node::TS_LOCAL);		//set fixed pitch axis
	}

	/**********************************************************************************/
	/**********************************************************************************/

	/**********************************************************************************/
	/***********************		SELECTION CONTROLS		***************************/
	/**********************************************************************************/

	//if left button down and selecting with selection box
	if (mMouse->getMouseState().buttonDown(OIS::MouseButtonID::MB_Left) && mSelecting)
	{
		multipleSelection = true;
		mSelectionBox->clear();
		mSelectionBox->setVisible(true);

		mStop.x = mMouse->getMouseState().X.abs / (float)arg.state.width;
		mStop.y = mMouse->getMouseState().Y.abs / (float)arg.state.height;
 
		mSelectionBox->setCorners(mStart, mStop);
	}
	else
		multipleSelection = false;


	/**********************************************************************************/
	/**********************************************************************************/

	return true;
}

bool DemoApp::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (mTrayMgr->injectMouseDown(arg, id)) return true;



	switch (id)
	{
		/*case OIS::MB_Left:
			{
				// if path already exists
				if(mCurrentState > 1)
				{
					// reset
					mCurrentState = 0;
					path1->clear();
					path2->clear();
				}
				// if no path yet
				else
				{
					// Create RaySceneQuery
					Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(
						static_cast<float>(mMouse->getMouseState().X.abs)/mMouse->getMouseState().width, 
						static_cast<float>(mMouse->getMouseState().Y.abs)/mMouse->getMouseState().height);

					Ogre::RaySceneQuery * mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

					// Set ray
					mRaySceneQuery->setRay(mouseRay);

					// Ray-cast and get first hit
					Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
					Ogre::RaySceneQueryResult::iterator itr = result.begin();

					// if hit an object
					if(itr != result.end())
					{
						// Get hit location
						Ogre::Vector3 location = mouseRay.getPoint(itr->distance);

						// if hit the floor
						if(location.y < 0.001)
						{
							// if no start node yet
							if(mCurrentState == 0)
							{
								// set start node
								startNode = pathFindingGraph->getNode(location);
								// set state to goal node state
								mCurrentState++;
							}
							// if start node already assigned
							else if(mCurrentState == 1)
							{
								// set goal node
								goalNode = pathFindingGraph->getNode(location);

								// check that goal node is not the same as start node
								if(goalNode != startNode)
								{
									// try to find path from start to goal node
									std::vector<int> path;

									// if path exists
									if(mPathFinder.Dijkstra(startNode, goalNode, *pathFindingGraph, path))
									{
										// draw path
										createPath(path1, 0.5, path, Ogre::ColourValue(1, 0, 0));
						
										mPathFinder.AStar(startNode, goalNode, *pathFindingGraph, path);
										createPath(path2, 1.0, path, Ogre::ColourValue(0, 0, 1));

										// set state to path found
										mCurrentState++;
									}
									else
									{
										// no path so set state to no start node
										mCurrentState = 0;
									}
								}
							}
						}
					}
				}
			}
			break;*/
		//SELECTION
		case OIS::MB_Left:
			{
				mStart.x = mMouse->getMouseState().X.abs / (float)arg.state.width;
				mStart.y = mMouse->getMouseState().Y.abs / (float)arg.state.height;
				mStop = mStart;
 
				mSelecting = true;

			}
			break;
		case OIS::MB_Right:
			{
				isOrbiting = true;
			}
			break;
		default:
			break;
	}

	return true;
}

bool DemoApp::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (mTrayMgr->injectMouseUp(arg, id)) return true;



	switch (id)
	{
		case OIS::MB_Left:
			{
				clickSelectObject();
				if(multipleSelection)
				{
					performSelection(mStart, mStop);
					mSelecting = false;
					mSelectionBox->setVisible(false);
					multipleSelection = false;
				}
				
			}
			break;
		case OIS::MB_Right:
			{
				isOrbiting = false;
				mTrayMgr->showCursor();
			}
			break;
		default:
			break;
	}

	return true;
}



void DemoApp::createPath(Ogre::ManualObject* line, float height, std::vector<int>& path, Ogre::ColourValue& colour)
{
	line->clear();

	// Specify the material and rendering type
	line->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);

	// Specify the vertices and vertex colour for the line
	Ogre::Vector3 position;

	for(std::vector<int>::iterator it=path.begin(); it!=path.end(); it++)
	{
		position = pathFindingGraph.getPosition(*it);
		line->position(Ogre::Vector3(position.x, height, position.z));
		line->colour(colour);
	}

	// Finished defining line
	line->end();
}
//function for single click selection
void DemoApp::clickSelectObject()
{
				/*SINGLE CLICK SELECTION*/
				// Get the mouse ray, i.e. ray from the mouse cursor 'into' the screen 
				Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(
					static_cast<float>(mMouse->getMouseState().X.abs)/mMouse->getMouseState().width, 
					static_cast<float>(mMouse->getMouseState().Y.abs)/mMouse->getMouseState().height);

				Ogre::RaySceneQuery * mRaySceneQuery = mSceneMgr->createRayQuery(mouseRay);
				// Set type of objects to query				
				mRaySceneQuery->setQueryTypeMask(Ogre::SceneManager::ENTITY_TYPE_MASK);
				mRaySceneQuery->setSortByDistance(true);

				// Ray-cast and get first hit
				Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
				Ogre::RaySceneQueryResult::iterator itr = result.begin();

				// If hit an entity
				if(itr != result.end())
				{
					//if robot hit
					if(itr->movable->getQueryFlags() == static_cast<Ogre::uint32>(QueryTypes::TANK))
					{
						Ogre::MovableObject *hitObject = static_cast<Ogre::MovableObject*>(itr->movable);

						//if user not editing selection (shift not held down)
						if(!editSelection)
						{
							//if there is multiple selected objects
							if(mSelected.size() > 1)
							{
									deselectObjects();				//deselect all objects
									selectObject(hitObject);		//select hit object
							}
							//if there is only one object selected
							else
							{
								//if object already selected
								if(isObjectSelected(hitObject))
									deselectObject(hitObject);		//deselect hit object 
								//if object not selected
								else
								{
									deselectObjects();				//deselect all objects
									selectObject(hitObject);		//select hit object
								}
							}
							
							
						}
						//if user editing selection (shift held down)
						else{

							//if object already selected
							if(isObjectSelected(hitObject))
								deselectObject(hitObject);		//deselect hit object 
							//if object not selected
							else
								selectObject(hitObject);		//select hit object
						}
					}
					//if ground hit
					else if(itr->movable->getQueryFlags() == static_cast<Ogre::uint32>(QueryTypes::GROUND))
					{
						//if user not selecting with selection box and not editing selection
						/*if(!multipleSelection && !editSelection)
						{
							//get coordinates where ray intersects the plane
							std::pair <bool, Ogre::Real> intersection = mouseRay.intersects(plane);
							
							//if there is an intersection
							if(intersection.first && !mSelected.empty()) 
							{
								// get the point where the intersection is
								Ogre::Vector3 point = mouseRay.getPoint(intersection.second);
								//put coordinates on walk list
								mWalkList.push_back(point);
							}
						}
						//otherwise, deselect all objects
						else*/
							deselectObjects();

					}
				}
				//if no entity hit (outside ground), deselect objects
				else{

					deselectObjects();
				}
				
}

/*************************		WALKING		************************/
void DemoApp::createFrameListener(void){

    BaseApplication::createFrameListener();
	
	
}   
bool DemoApp::nextLocation(void){

	//if there is no destination
    if (mWalkList.empty()) 
		return false;
	//if there is no selected object
	if(mSelected.size() == 0)
		return false;

	//set destination
    mDestination = mWalkList.front();  // this gets the front of the deque
    mWalkList.pop_front();             // this removes the front of the deque

	//get selected object
	std::list<Ogre::MovableObject*>::iterator it;
		
	for (it = mSelected.begin(); it != mSelected.end(); ++it)
	{
		Ogre::SceneNode *tempNode = (*it)->getParentSceneNode();
		mNode = tempNode;
		Ogre::Entity* tempEntity = static_cast<Ogre::Entity*>(tempNode->getAttachedObject(0));
		mEntity = tempEntity;

		mDirection = mDestination - mNode->getPosition();
		mDistance = mDirection.normalise();


	}


    

    return true;
}

/*************************		SELECTION		************************/

/*
Ogre::Vector2 DemoApp::worldToScreenPosition(const Ogre::Vector3& position)
{
	// The origin of the screen position here is at the centre of screen
	Ogre::Vector3 screenPosition = mCamera->getProjectionMatrix() * mCamera->getViewMatrix() * position;

	// Compute the 2D screen position with the origin at the top left of screen
	return Ogre::Vector2(0.5 + 0.5 * screenPosition.x, 0.5 - 0.5 *screenPosition.y);
}
*/


 
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//#define WIN32_LEAN_AND_MEAN
//#include "windows.h"
//#endif
// 
//#ifdef __cplusplus
//extern "C" {
//#endif
// 
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
//#else
//    int main(int argc, char *argv[])
//#endif
//    {
//        // Create application object
//        DemoApp app;
// 
//        try {
//            app.go();
//        } catch( Ogre::Exception& e ) {
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
//#else
//            std::cerr << "An exception has occured: " <<
//                e.getFullDescription().c_str() << std::endl;
//#endif
//        }
// 
//        return 0;
//    }
// 
//#ifdef __cplusplus
//}
//#endif
//
