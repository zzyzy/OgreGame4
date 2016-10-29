/*
-----------------------------------------------------------------------------
CSCI356: Game Engine Essentials - Assignment 3

Name: Ivana Ozakovic
Student No.: 4790339
Email: io447@uow.edu.au

Filename:   DemoApp.h
			This source file is based on Lab files supplied and has been modified and code was added for requirements of this assignment.
-----------------------------------------------------------------------------
*/

#ifndef __DemoApp_h_
#define __DemoApp_h_
 
#include "BaseApplication.h"
#include "PathFinding.h"
#include "PhysicsEngine.h"

#include "stdafx.h"
#include <deque>
#include "PowerUp.h"
#include "Tank.h"

class DemoApp : public BaseApplication
{
public:
    DemoApp(void);
    virtual ~DemoApp(void);
 
protected:
	virtual bool setup(void);
    virtual void createScene(void);

	//processing
	bool processUnbufferedInput(const Ogre::FrameEvent& evt);

	// Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


	// Convenience function for creating a power up in the scene
	PowerUp* createPowerUp(PowerUpType type, Ogre::String name);

	// Simple test function that creates one of each power up and adds to scene
	void createPowerUps();

	Ogre::SceneNode *node;			//scene node
	Ogre::Entity* entGround;		//ground entity
	
	// for physics
	PhysicsEngine*	mPhysicsEngine;
	std::vector<GameObject*> *objects;


	/***********		CAMERA		*************/
	void setCamera();	
	Ogre::SceneNode *mCamNode;			// The SceneNode the camera is currently attached to
	Ogre::SceneNode* mTarget;			// Camera target
	bool isOrbiting;					// Bool to check if camera is orbiting
	Ogre::Real dist;					// Distance from camera to target	
	Ogre::Vector3 mDirectionCam;		// Value to move camera in the correct direction
	Ogre::Real mMove;					// The camera movement constant

	

	/***********		WALK		*************/
	// WALK Tutorial Section from:
	//http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Intermediate+Tutorial+1
	/////////////////////////////////////////////
	virtual bool nextLocation(void);
    virtual void createFrameListener(void);
	bool shouldAnimate;						//if object selected, animation should start
	Ogre::Real mDistance;                  // The distance the object has left to travel
    Ogre::Vector3 mDirection;              // The direction the object is moving
    Ogre::Vector3 mDestination;            // The destination the object is moving towards
 
    Ogre::AnimationState *mAnimationState; // The current animation state of the object
 
    Ogre::Entity *mEntity;                 // The Entity we are animating
    Ogre::SceneNode *mNode;                // The -SceneNode that the Entity is attached to
    std::deque<Ogre::Vector3> mWalkList;   // The list of points we are walking to
 
    Ogre::Real mWalkSpeed;                 // The speed at which the object is moving


private:
	//PATH FINDING
	int mCurrentState;
	int startNode;
	int goalNode;

	Graph pathFindingGraph;
	PathFinding mPathFinder;
	Ogre::ManualObject* path1;
	Ogre::ManualObject* path2;

	void createPath(Ogre::ManualObject* line, float height, std::vector<int>& path, Ogre::ColourValue& colour);

	//SELECTION
	void clickSelectObject();		//single click handling
	bool multipleSelection;

	// Converts a 3D world position to a 2D relative screen coordinate (i.e. between 0 and 1 for x and y respectively)
	//Ogre::Vector2 worldToScreenPosition(const Ogre::Vector3& position);

    Ogre::SceneNode* mWorldGridNode;
};
 
#endif // #ifndef __DemoApp_h_