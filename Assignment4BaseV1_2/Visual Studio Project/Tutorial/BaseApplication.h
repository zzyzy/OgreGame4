/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
-----------------------------------------------------------------------------
 
This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
	  Tutorial Framework
	  http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __BaseApplication_h_
#define __BaseApplication_h_
 
#include "stdafx.h"
#include "SelectionBox.h"
#include "Tank.h"
#include <vector>

enum QueryFlags
	{
		GROUND_MASK = 1 << 0,
		TANK_MASK = 1 << 1,
		OBSTACLES_MASK = 1 << 2,
	};


class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
	BaseApplication(void);
	virtual ~BaseApplication(void);

	virtual void go(void);
 
	
protected:
	virtual bool setup();
	virtual bool configure(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createFrameListener(void);
	virtual void createScene(void) = 0; // Override me!
	virtual void destroyScene(void);
	virtual void createViewports(void);
	virtual void setupResources(void);
	virtual void createResourceListener(void);
	virtual void loadResources(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
 
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );

	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
 
	//Adjust mouse clipping area
	virtual void windowResized(Ogre::RenderWindow* rw);
	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(Ogre::RenderWindow* rw);
 
	Ogre::Root *mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;


	/***********		TANKS		*************/
	//std::vector<Tank> challengerTanks;
	//std::vector<Tank> leopardTanks;
	std::vector<Tank> tanks;			// vector containing tanks added on the scene

	bool editSelection;
	//overlay system
	Ogre::OverlaySystem *mOverlaySystem;
 
	// OgreBites
	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager*	mTrayMgr;
	OgreBites::SdkCameraMan* mCameraMan;     	// basic camera controller
	OgreBites::ParamsPanel* mDetailsPanel;   	// sample details panel
	bool mCursorWasVisible;						// was cursor visible before dialog appeared
	bool mShutDown;
 
	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;

	/////////////////////////////
	// Tutorial SELECTION BOX //
	//from http://www.ogre3d.org/tikiwiki/Intermediate+Tutorial+4
	///////////////////////////
	void performSelection(const Ogre::Vector2& first, const Ogre::Vector2& second);
	void deselectObjects();																//deselect all objects
	void deselectObject(Ogre::MovableObject* obj);										//deselect an object
	void selectObject(Ogre::MovableObject* obj);										//select an object
	bool isObjectSelected(Ogre::MovableObject* obj);
 
	static void swap(float& x, float& y);
 
	bool mSelecting;
	bool mLMouseDown, mRMouseDown;
	float mRotSpd;
	SelectionBox* mSelectionBox;
	std::list<Ogre::MovableObject*> mSelected;
 
	Ogre::Vector2 mStart, mStop;
	Ogre::RaySceneQuery* mRayScnQuery;
	Ogre::PlaneBoundedVolumeListSceneQuery* mVolQuery;

 
	// Added for Mac compatibility
	Ogre::String                 m_ResourcePath;
 
#ifdef OGRE_STATIC_LIB
	Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif
};
 
#endif // #ifndef __BaseApplication_h_