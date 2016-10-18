/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial3.h
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
#ifndef __BasicTutorial3_h_
#define __BasicTutorial3_h_
 
#include "stdafx.h"
#include "BaseApplication.h"
 
#include "PhysicsEngine.h"

#include <fstream>
#include <string>

class BasicTutorial3 : public BaseApplication
{
private:
    Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;
    OgreBites::Label* mInfoLabel;

	// for physics
	PhysicsEngine*	mPhysicsEngine;

	int				mBoxCount;

    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);

public:
    BasicTutorial3(void);
    virtual ~BasicTutorial3(void);
 
protected:
	virtual bool setup();
    virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void destroyScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	void shootBox(const btVector3& position, const btQuaternion& orientation, const btVector3& linearVelocity);

};
 
#endif // #ifndef __BasicTutorial3_h_